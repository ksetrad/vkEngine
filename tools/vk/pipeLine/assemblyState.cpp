//
// Created by Владимир on 06.09.2020.
//

#include "assemblyState.h"

using namespace vk::pipeline;

AssemblyState::AssemblyState ( const Types &types )
{

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	/// Устанавливаем тип того что рисуем по вершинам
	switch ( types )
	{
		case POINTS:
			createInfo.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
			break;
		case LINES:
			createInfo.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
			break;
		case TRIANGLES:
			createInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			break;
	}
	/// Флаг специального индекса сброса
	createInfo.primitiveRestartEnable = VK_FALSE;
}

VkPipelineInputAssemblyStateCreateInfo *
AssemblyState::getInfo ()
{
	return &createInfo;
}
