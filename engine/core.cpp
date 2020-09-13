//
// Created by Владимир on 09.09.2020.
//

#include <engine/common/uniform.h>
#include <tools/vk/uniformBufferSet.h>
#include "core.h"

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

        bufferSet = new vk::UniformBufferSet(core, sizeof(engine::Uniform));
        /// Формируем кадровые буферы
        frameBuffers = new vk::FrameBuffer ( core , mainRenderPass );
        /// Формируем окружение
        environment = new Environment();
        /// Создаем командный пул
        commandPool = new CommandPool ( core , mainPipeLine , environment );
        /// Инициализируем пул дескрипторов
        descriptorsPool = new vk::DescriptorsPool ( core );
        descriptorsPool->createDescritorSets(bufferSet->getBuffers(),mainPipeLine->getLayout(),sizeof(engine::Uniform));
        /// Инициаилизируем фабрику моделей
        modelFactory = new ModelFactory ( core , commandPool );
        /// Заполняем окружение
        environment->models.emplace_back ( modelFactory->openModel ( "4.corobj" ) );
        commandPool->createCommandBuffer ( core->getSwapChain () , mainRenderPass , frameBuffers , descriptorsPool );
}

Core::~Core ()
{
        delete bufferSet;
        delete environment;
        delete modelFactory;
        delete frameBuffers;
        delete mainPipeLine;
        delete descriptorsPool;
        delete mainRenderPass;
        delete commandPool;
        delete core;
}

void
Core::mainLoop ()
{
        while ( !glfwWindowShouldClose ( core->getWindow () ) )
        {
                glfwPollEvents ();
        }
}

