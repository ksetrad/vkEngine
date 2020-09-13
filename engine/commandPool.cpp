//
// Created by Владимир on 10.09.2020.
//

#include "commandPool.h"

using namespace engine;

CommandPool::CommandPool (
        vk::Core * core ,
        vk::PipeLine * pipeLine ,
        Environment * environment
                         )
        : vk::CommandPool ( core ) , pipeLine ( pipeLine ) , environment ( environment )
{

}

void
CommandPool::setCommandBufferContent (  const VkCommandBuffer & commandBuffer, const VkDescriptorSet * descriptorSet  )
{
        vkCmdBindPipeline ( commandBuffer , VK_PIPELINE_BIND_POINT_GRAPHICS , pipeLine->getPipeLine () );

        vkCmdBindDescriptorSets ( commandBuffer , VK_PIPELINE_BIND_POINT_GRAPHICS , pipeLine->getLayout()->getLayout() , 0 , 1 ,
                                  descriptorSet , 0 , nullptr );

        /// Отрисовываем все модели в окружении
        for ( const auto & model: environment->models )
        {
                bindBuffer(model->vbo,commandBuffer);
                bindBuffer(model->ibo,commandBuffer);
                vkCmdDrawIndexed ( commandBuffer , model->ibo.count() , 1 , 0 , 0 , 0 );
        }
}

void
CommandPool::bindBuffer (
        const vk::BufferObject & buffer ,
        VkCommandBuffer const & commandBuffer
                        )
{
        switch ( buffer.getType () )
        {
                case vk::BufferObject::INDEX:
                        vkCmdBindIndexBuffer ( commandBuffer , buffer.getBuffer () , 0 , VK_INDEX_TYPE_UINT16 );
                        break;
                case vk::BufferObject::VERTEX:
                {
                        VkBuffer vertexBuffers[] = { buffer.getBuffer () };
                        VkDeviceSize offsets[] = { 0 };
                        vkCmdBindVertexBuffers ( commandBuffer , 0 , 1 , vertexBuffers , offsets );
                }
                        break;
        }
}

