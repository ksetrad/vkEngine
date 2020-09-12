//
// Created by Владимир on 10.09.2020.
//
#include "tools/vk/swapChain.h"
#include "tools/vk/frameBuffer.h"

using namespace vk;

FrameBuffer::FrameBuffer (
        Core * core ,
        RenderPass * renderPass
                         )
        : logicalDevice ( logicalDevice )
{
        swapChainFramebuffers.resize ( core->getSwapChain ()->getImagesView ().size () );
        for ( size_t i = 0 ;
              i < core->getSwapChain ()->getImagesView ().size () ;
              i++ )
        {
                VkImageView attachments[] = {
                        core->getSwapChain ()->getImagesView ()[ i ]
                };

                VkFramebufferCreateInfo framebufferInfo { };
                framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                framebufferInfo.renderPass = renderPass->getRenderPass ();
                framebufferInfo.attachmentCount = 1;
                framebufferInfo.pAttachments = attachments;
                framebufferInfo.width = core->getSwapChain ()->getExtent ().width;
                framebufferInfo.height = core->getSwapChain ()->getExtent ().height;
                framebufferInfo.layers = 1;

                if ( vkCreateFramebuffer ( logicalDevice->getDevice () , & framebufferInfo , nullptr ,
                                           & swapChainFramebuffers[ i ] ) != VK_SUCCESS )
                {
                        throw vulkan_exception( "failed to create framebuffer!" );
                }
        }
}

FrameBuffer::~FrameBuffer ()
{
        for ( auto framebuffer : swapChainFramebuffers )
        {
                vkDestroyFramebuffer ( logicalDevice->getDevice () , framebuffer , nullptr );
        }
}

