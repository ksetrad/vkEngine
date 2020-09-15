//
// Created by Владимир on 02.09.2020.
//

#include "shaderModule.h"
#include <fstream>
#include <vector>

using namespace vk::pipeline;

ShaderModule::ShaderModule (
        const std::string &filename,
        LogicalDevice *device,
        const Types &type ) :
    device ( device )
{
	/// Открываем файл шейдера
	std::ifstream file ( filename, std::ios::ate | std::ios::binary );

	if ( !file.is_open () )
	{
		throw std::runtime_error ( "failed to open file!" );
	}

	size_t fileSize = ( size_t ) file.tellg ();
	/// Создаем буфер под файл
	std::vector< char > buffer ( fileSize );

	file.seekg ( 0 );
	/// Считываем файл
	file.read ( buffer.data (), fileSize );

	/// Закрываем файл
	file.close ();

	/// Заполняем структуру создания шейдерного модуля
	VkShaderModuleCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = buffer.size ();
	createInfo.pCode = reinterpret_cast< const uint32_t * > ( buffer.data () );

	/// Создаем шейдерный модуль
	if ( vkCreateShaderModule ( device->getDevice (), &createInfo, nullptr, &shaderModule ) != VK_SUCCESS )
	{
		throw vulkan_exception ( "failed to create shader module!" );
	}

	/// Создаем структуру описания шейдерной стадии для заданного модуля
	shaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	switch ( type )
	{
		case Vertex:
			shaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
			break;
		case Geometry:
			shaderStage.stage = VK_SHADER_STAGE_GEOMETRY_BIT;
			break;
		case Fragment:
			shaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
	}
	shaderStage.module = shaderModule;
	shaderStage.pName = "main";
}

ShaderModule::~ShaderModule ()
{
	vkDestroyShaderModule ( device->getDevice (), shaderModule, nullptr );
}

const VkPipelineShaderStageCreateInfo &
ShaderModule::getShaderStage () const
{
	return shaderStage;
}
