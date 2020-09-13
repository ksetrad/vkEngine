//
// Created by Владимир on 10.09.2020.
//

#include "tools/vk/commandsPool.h"
#include "renderPass.h"

using namespace vk;

CommandPool::CommandPool ( Core * core )
        : core ( core )
{
        VkCommandPoolCreateInfo poolInfo { };
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = core->getPhysicalDevice ()->getIndices ().graphicsFamily.value ();
        poolInfo.flags = 0;

        if ( vkCreateCommandPool ( core->getLogicalDevice ()->getDevice () , & poolInfo , nullptr , & commandPool ) !=
             VK_SUCCESS )
        {
                throw vulkan_exception( "failed to create command pool!" );
        }
}


CommandPool::~CommandPool ()
{
        vkDestroyCommandPool ( core->getLogicalDevice ()->getDevice () , commandPool , nullptr );
}

void
CommandPool::cmdTransferBuffer ( const BufferObject & buffer )
{
        /// Инициализируем структуру создания нового командрого буфера
        VkCommandBufferAllocateInfo allocInfo { };
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandPool;
        allocInfo.commandBufferCount = 1;

        /// Выделяем под буффер память
        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers ( core->getLogicalDevice ()->getDevice () , & allocInfo , & commandBuffer );

        /// Настраиваем командный буфер
        VkCommandBufferBeginInfo beginInfo { };
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        /// Сообщаем что буфер будет вызван только один раз
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        /// Формируем команды в буфере
        vkBeginCommandBuffer ( commandBuffer , & beginInfo );

        VkBufferCopy copyRegion { };
        copyRegion.size = buffer.size ();
        vkCmdCopyBuffer ( commandBuffer , buffer.getStagingBuffer () , buffer.getBuffer () , 1 , & copyRegion );

        vkEndCommandBuffer ( commandBuffer );

        /// Готовим информацию к отправке в очередь
        VkSubmitInfo submitInfo { };
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = & commandBuffer;

        /// Отправляем информацию в очередь
        vkQueueSubmit ( core->getGraphicsQueue ()->getQueue () , 1 , & submitInfo , VK_NULL_HANDLE );
        /// Ждем выполнения
        vkQueueWaitIdle ( core->getGraphicsQueue ()->getQueue () );

        /// Освобождаем буфер
        vkFreeCommandBuffers ( core->getLogicalDevice ()->getDevice () , commandPool , 1 , & commandBuffer );
}

void
CommandPool::createCommandBuffer (
        SwapChain * swapChain ,
        RenderPass * renderPass ,
        FrameBuffer * frameBuffer ,
        DescriptorsPool * pool
                                 )
{
        /// Инициализируем массив командных буферов
        commandBuffers.resize ( core->getSwapChain ()->getImagesView ().size () );

        /// Заполняем структуру для выделения памяти под командные буферы
        VkCommandBufferAllocateInfo allocInfo { };
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        /// Задаем размер буферов
        allocInfo.commandBufferCount = ( uint32_t ) commandBuffers.size ();
        /// Инициализируем буферы
        if ( vkAllocateCommandBuffers ( core->getLogicalDevice ()->getDevice () , & allocInfo ,
                                        commandBuffers.data () ) != VK_SUCCESS )
        {
                vulkan_exception( "failed to allocate command buffers!" );
        }
        for ( size_t i = 0 ;
              i < commandBuffers.size () ;
              i++ )
        {
                /// Начинаем заполнять буфер
                VkCommandBufferBeginInfo beginInfo { };
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

                if ( vkBeginCommandBuffer ( commandBuffers[ i ] , & beginInfo ) != VK_SUCCESS )
                {
                        throw vulkan_exception( "failed to begin recording command buffer!" );
                }

                VkRenderPassBeginInfo renderPassInfo { };
                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                renderPassInfo.renderPass = renderPass->getRenderPass ();
                /// Используемые буферы в проходе рендеринга
                renderPassInfo.framebuffer = frameBuffer->getFrameBuffers ()[ i ];
                renderPassInfo.renderArea.offset = { 0 , 0 };
                /// размеры изображений в проходе рендеринга
                renderPassInfo.renderArea.extent = swapChain->getExtent ();
                /// Цвет очистки
                VkClearValue clearColor = { 0.0f , 0.0f , 0.0f , 1.0f };
                renderPassInfo.clearValueCount = 1;
                renderPassInfo.pClearValues = & clearColor;
                /// Заполняем командный буфер
                vkCmdBeginRenderPass ( commandBuffers[ i ] , & renderPassInfo , VK_SUBPASS_CONTENTS_INLINE );
                setCommandBufferContent ( commandBuffers[ i ] , & pool->getDescriptorSets ()[ i ] );
                vkCmdEndRenderPass ( commandBuffers[ i ] );

                // Завершаем заполнение
                if ( vkEndCommandBuffer ( commandBuffers[ i ] ) != VK_SUCCESS )
                {
                        throw vulkan_exception( "failed to record command buffer!" );
                }
        }
}

