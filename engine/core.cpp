//
// Created by Владимир on 09.09.2020.
//
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "tools/vk/uniformBufferSet.h"

#include "engine/core.h"
#include "engine/common/uniform.h"

using namespace engine;
using namespace vk::pipeline;

Core::Core ()
        : core ( new vk::Core () ) ,
          mainRenderPass ( new MainRenderPass ( core ) ) ,
          mainPipeLine ( new vk::PipeLine ( core->getLogicalDevice () ) )
{
        /// Формируем конвеер
        std::vector < ShaderModule * > stages;
        stages.emplace_back (
                new ShaderModule ( "./shaders/shader.vert.spv" , core->getLogicalDevice () , ShaderModule::Vertex ) );
        stages.emplace_back (
                new ShaderModule ( "./shaders/shader.frag.spv" , core->getLogicalDevice () , ShaderModule::Fragment ) );
        mainPipeLine->setShaderStages ( stages );
        mainPipeLine->setAssemblyState ( AssemblyState ( AssemblyState::TRIANGLES ) );
        mainPipeLine->setViewPortState ( new ViewPortState ( core->getSwapChain () ) );
        mainPipeLine->setRasterizationState ( RasterizationState () );
        mainPipeLine->setMultisampling ( Multisampling ( false ) );
        mainPipeLine->setBlending ( Blending ( false ) );
        mainPipeLine->setPipeLineLayout ( new PipeLineLayout ( core->getLogicalDevice () ) );

        mainPipeLine->initialize ( mainRenderPass->getRenderPass () );

        bufferSet = new vk::UniformBufferSet ( core , sizeof ( engine::Uniform ) );
        /// Формируем кадровые буферы
        frameBuffers = new vk::FrameBuffer ( core , mainRenderPass );
        /// Формируем окружение
        environment = new Environment ();
        /// Создаем командный пул
        commandPool = new CommandPool ( core , mainPipeLine , environment );
        /// Инициализируем пул дескрипторов
        descriptorsPool = new vk::DescriptorsPool ( core );
        descriptorsPool->createDescritorSets ( bufferSet->getBuffers () , mainPipeLine->getLayout () ,
                                               sizeof ( engine::Uniform ) );
        /// Инициаилизируем фабрику моделей
        modelFactory = new ModelFactory ( core , commandPool );
        /// Заполняем окружение
        environment->models.emplace_back ( modelFactory->openModel ( "cube.corobj" ) );
        commandPool->createCommandBuffer ( core->getSwapChain () , mainRenderPass , frameBuffers , descriptorsPool );

        /// Инициализируем объекты синхронизации
        renderFinishedSemaphores.resize ( frame_number );
        imageAvailableSemaphores.resize ( frame_number );
        inFlightFences.resize ( frame_number );
        for ( int i = 0 ;
              i < frame_number ;
              i++ )
        {
                renderFinishedSemaphores[ i ] = new vk::Semaphore ( core );
                imageAvailableSemaphores[ i ] = new vk::Semaphore ( core );
                inFlightFences[ i ] = new vk::Fence ( core );
        }
        /// Размер выбирается равным числу кадров в цепочке, значенияя не устанаавливаются
        imagesInFlight.resize ( core->getSwapChain ()->getImagesView ().size () , nullptr );
}

Core::~Core ()
{
        delete frameBuffers;
        delete commandPool;
        delete bufferSet;
        delete environment;
        delete modelFactory;

        delete mainPipeLine;
        delete descriptorsPool;
        delete mainRenderPass;

        for ( int i = 0 ;
              i < frame_number ;
              i++ )
        {
                delete renderFinishedSemaphores[ i ];
                delete imageAvailableSemaphores[ i ];
                delete inFlightFences[ i ];
        }
        renderFinishedSemaphores.clear ();
        imageAvailableSemaphores.clear ();
        inFlightFences.clear ();
        delete core;
}

void
Core::mainLoop ()
{
        auto lastTime = glfwGetTime();
        int nbFrames = 0;
        while ( !glfwWindowShouldClose ( core->getWindow () ) )
        {
                glfwPollEvents ();
                /// Дожидаемся пока все команды относящиеся к кадру currentFrameId не будут выполнены
                inFlightFences[ currentFrameId ]->wait ();

                /// Определяем индекс следующего изображения для рендеринга
                auto index = getImage ( imageAvailableSemaphores[ currentFrameId ] );

                /// Обновляем uniform буфер для текущих проходов рендеринга
                /// TODO updateUniform

                /// Ждем освобождения изображения если для кадра с индексом установлен забор
                if ( imagesInFlight[ index ] != nullptr )
                {
                        imagesInFlight[ index ]->wait ();
                }
                updateUniform(index);

                /// Используем для данного изображения забор от нашего кадра
                imagesInFlight[index] = inFlightFences[currentFrameId];


                VkSubmitInfo submitInfo{};
                submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

                /// Этот семофор мы ждет
                VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrameId]->getSemaphore()};
                /// Это стадия на которой мы ждем
                VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
                submitInfo.waitSemaphoreCount = 1;
                submitInfo.pWaitSemaphores = waitSemaphores;
                submitInfo.pWaitDstStageMask = waitStages;

                submitInfo.commandBufferCount = 1;
                submitInfo.pCommandBuffers = &commandPool->getCommandBuffers()[index];
                /// Этот семофор сообщает о заврешении стадии
                VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrameId]->getSemaphore()};
                submitInfo.signalSemaphoreCount = 1;
                submitInfo.pSignalSemaphores = signalSemaphores;

                /// Переводим забор в несигнальное состояние
                vkResetFences(core->getLogicalDevice()->getDevice(), 1, &inFlightFences[currentFrameId]->getFence());

                /// Теперь выполняем в барьер мы запишем сигнал о завершении этапа
                if (vkQueueSubmit(core->getGraphicsQueue()->getQueue(), 1, &submitInfo, inFlightFences[currentFrameId]->getFence()) != VK_SUCCESS) {
                        throw std::runtime_error("failed to submit draw command buffer!");
                }

                VkPresentInfoKHR presentInfo{};
                presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

                presentInfo.waitSemaphoreCount = 1;
                presentInfo.pWaitSemaphores = signalSemaphores;

                VkSwapchainKHR swapChains[] = {core->getSwapChain()->getSwapChain()};
                presentInfo.swapchainCount = 1;
                presentInfo.pSwapchains = swapChains;

                presentInfo.pImageIndices = &index;

                VkResult result = vkQueuePresentKHR(core->getPresentationQueue()->getQueue(), &presentInfo);

//                if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
//                        framebufferResized = false;
//                        recreateSwapChain();
//                } else if (result != VK_SUCCESS) {
//                        throw std::runtime_error("failed to present swap chain image!");
//                }

                currentFrameId = (currentFrameId + 1) % frame_number;
                double currentTime = glfwGetTime();
                nbFrames++;
                if(currentTime-lastTime > 1.){
                    std::cout << nbFrames << std::endl;
                    lastTime = currentTime;
                    nbFrames = 0;
                }
        }
        /// Ждем выполнения
        vkQueueWaitIdle ( core->getGraphicsQueue ()->getQueue () );

}

uint32_t
Core::getImage ( vk::Semaphore * pWaitSemaphore )
{
        /// Индекс изображения в цепочке подкачки которое подует использовано для рендеринга
        uint32_t imageIndex;
        /// Функция получиния индекса в цепочке подкачки, семафор в данном случае сообщает когда можно начать рисовать на изображении
        VkResult result = vkAcquireNextImageKHR ( core->getLogicalDevice ()->getDevice () ,
                                                  core->getSwapChain ()->getSwapChain () , UINT64_MAX ,
                                                  pWaitSemaphore->getSemaphore () , VK_NULL_HANDLE , & imageIndex );
        if ( result == VK_ERROR_OUT_OF_DATE_KHR )
        {
                /// Если поверхность изменилась (ресайз) то нужно перестроить все начиная с цепочки подкачки
                ///TODO recreateSwapChain();
                throw std::runtime_error ( "swap chain recize!" );
        }
        else if ( result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR )
        {
                throw vulkan_exception( "failed to acquire swap chain image!" );
        }
        return imageIndex;
}

void
Core::updateUniform ( const int & id )
{
        Uniform m_ubo{};
        auto transpose = glm::mat4(1);
        transpose[3][2] = -2;
        m_ubo.model = transpose;
        m_ubo.view = glm::lookAt( glm::vec3( 2.0f, 2.0f, 2.0f), glm::vec3( 0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, 0.0f, 1.0f));
        m_ubo.proj = glm::perspective( glm::radians( 45.0f), core->getSwapChain()->getExtent().width / (float) core->getSwapChain()->getExtent().height, 0.1f, 10.0f);
        m_ubo.proj[1][1] *= -1;

        bufferSet->write(id,&m_ubo,sizeof(Uniform));
}

