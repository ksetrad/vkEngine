//
// Created by Владимир on 09.09.2020.
//

#include "core.h"

using namespace engine;
using namespace vk::pipeline;

Core::Core ()
        : core ( new vk::Core () ) ,
          mainRenderPass ( new MainRenderPass ( core->getLogicalDevice () , core->getSwapChain () ) ) ,
          mainPipeLine ( new vk::PipeLine ( core->getLogicalDevice () ) ) , commandPool ( new CommandPool ( core ) )
{
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

        frameBuffers = new vk::FrameBuffer ( core->getLogicalDevice () , mainRenderPass , core->getSwapChain () );
}

Core::~Core ()
{
        delete frameBuffers;
        delete mainPipeLine;
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

