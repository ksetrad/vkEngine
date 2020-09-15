//
// Created by Владимир on 09.09.2020.
//

#include "vertexInputInfo.h"

using namespace vk::pipeline;

VertexInputInfo::VertexInputInfo ()
{
	inputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	/// Получаем параметры привязки
	bindingDescription = Vertex::getBindingDescription ();
	/// И входящих в неё атрибутов
	attributeDescriptions = Vertex::getAttributeDescriptions ();

	/// Количество привязок
	inputInfo.vertexBindingDescriptionCount = 1;
	/// Количество привязок атрибутов
	inputInfo.vertexAttributeDescriptionCount = static_cast< uint32_t > ( attributeDescriptions.size () );

	inputInfo.pVertexBindingDescriptions = &bindingDescription;
	inputInfo.pVertexAttributeDescriptions = attributeDescriptions.data ();
}

VkPipelineVertexInputStateCreateInfo *
VertexInputInfo::getInfo ()
{
	return &inputInfo;
}
