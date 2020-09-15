//
// Created by Владимир on 02.09.2020.
//

#include "tools/vk/pipeLine.h"
#include "tools/vk/pipeLine/vertexInputInfo.h"

using namespace vk;

PipeLine::PipeLine ( vk::LogicalDevice *device ) :
    device ( device )
{
}

void
PipeLine::setShaderStages ( std::vector< pipeline::ShaderModule * > new_stages )
{
	stages = std::move ( new_stages );
}

void
PipeLine::initialize ( VkRenderPass const &renderPass )
{
	std::vector< VkPipelineShaderStageCreateInfo > stagesInfo;
	/// Формируем массив структур описания шейдерных стадий
	for ( const auto &stage : stages )
	{
		stagesInfo.push_back ( stage->getShaderStage () );
	}

	VkGraphicsPipelineCreateInfo pipelineInfo {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	/// Количество шейдерных стадий в массиве
	pipelineInfo.stageCount = stagesInfo.size ();
	/// Массив шейдерных стадий
	pipelineInfo.pStages = stagesInfo.data ();
	/// Параметры вершин
	pipelineInfo.pVertexInputState = vertexInfo.getInfo ();
	/// Параметры преобразования вершин в примитивы GPU
	pipelineInfo.pInputAssemblyState = assemblyState.getInfo ();
	/// Параметры выхода конвера
	pipelineInfo.pViewportState = viewPortState->getInfo ();
	/// Параметры растеризации
	pipelineInfo.pRasterizationState = rasterizationState.getInfo ();
	/// Параметры мультисемплинга
	pipelineInfo.pMultisampleState = multisampling.getInfo ();
	/// Параметры смешивания (блендинга)
	pipelineInfo.pColorBlendState = blendingInfo.getInfo ();
	/// Параметры макета (uniform descriptors)
	pipelineInfo.layout = layout->getLayout ();
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

	if ( vkCreateGraphicsPipelines ( device->getDevice (), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr,
	                                 &pipeLine ) != VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to create graphics pipeline!" );
	}

	/// Удаляем не используемые шейдерные модули
	for ( auto &stage : stages )
	{
		delete stage;
	}
}

void
PipeLine::setBlending ( const pipeline::Blending &blending )
{
	blendingInfo = blending;
}

void
PipeLine::setPipeLineLayout ( const pipeline::PipeLineLayout *pipeLineLayout )
{
	layout = pipeLineLayout;
}

void
PipeLine::setViewPortState ( const pipeline::ViewPortState *viewPortState )
{
	PipeLine::viewPortState = viewPortState;
}

void
PipeLine::setMultisampling ( const pipeline::Multisampling &multisampling )
{
	PipeLine::multisampling = multisampling;
}

void
PipeLine::setRasterizationState ( const pipeline::RasterizationState &rasterizationState )
{
	PipeLine::rasterizationState = rasterizationState;
}

void
PipeLine::setAssemblyState ( const pipeline::AssemblyState &assemblyState )
{
	PipeLine::assemblyState = assemblyState;
}

PipeLine::~PipeLine ()
{
	delete layout;
	vkDestroyPipeline ( device->getDevice (), pipeLine, nullptr );
}

const VkPipeline &
PipeLine::getPipeLine () const
{
	return pipeLine;
}

const pipeline::PipeLineLayout *
PipeLine::getLayout () const
{
	return layout;
}
