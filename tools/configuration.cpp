//
// Created by Владимир on 26.08.2020.
//
#include "tools/configuration.h"
#include <fstream>
#include <memory>
#include <vulkan/vulkan.h>

Configuration *
Configuration::instance ()
{
	static std::unique_ptr <Configuration> instance { nullptr };
	if ( instance == nullptr )
	{
		instance.reset ( new Configuration () );
	}
	return instance.get ();
}

const Configuration::CoreVulkan &
Configuration::vulkan ()
{
	return instance ()->m_vulkan;
}

Configuration::Configuration ()
{
	read ();
}

void
Configuration::read ()
{
	std::ifstream fin ( "./configuration.toml" );
	toml::table root = ( !fin.is_open () ) ? toml::table () : toml::parse ( fin );
	m_display.resolution.width = root[ "Display" ][ "Resolution" ][ "width" ].value_or ( 1440 );
	m_display.resolution.height = root[ "Display" ][ "Resolution" ][ "height" ].value_or ( 900 );
	m_vulkan.appName = root[ "Core" ][ "appName" ].value_or ( "Caravaner" );
	m_vulkan.engineName = root[ "Core" ][ "engineName" ].value_or ( "Vovan's Masterpiece" );
	m_engine.modelDirPath = root[ "Engine" ][ "models directory" ].value_or ( "" );
	auto node_validation_layers = root[ "Core" ][ "validation layers" ].as_array ();
	if ( node_validation_layers != nullptr )
	{
		for ( int i = 0 ;
		      i < node_validation_layers->size () ;
		      i++ )
		{
			m_vulkan.validationLayers.emplace_back (
					root[ "Core" ][ "validation layers" ][ i ].value_or ( "" ) );
		}
	}
	else
	{
		m_vulkan.validationLayers.emplace_back ( "VK_LAYER_LUNARG_standard_validation" );
	}

	auto node_device_extension = root[ "Core" ][ "device extension" ].as_array ();
	if ( node_device_extension != nullptr )
	{
		for ( int i = 0 ;
		      i < node_device_extension->size () ;
		      i++ )
		{
			m_vulkan.deviceExtension.emplace_back (
					root[ "Core" ][ "device extension" ][ i ].value_or ( "" ) );
		}
	}
	else
	{
		m_vulkan.deviceExtension.emplace_back ( VK_KHR_SWAPCHAIN_EXTENSION_NAME );
	}

	m_camera.scale.min = root[ "Camera" ][ "scale" ][ "min" ].value_or ( 10.f );
	m_camera.scale.max = root[ "Camera" ][ "scale" ][ "max" ].value_or ( 80.f );
	m_camera.theta = root[ "Camera" ][ "incline" ].value_or ( 0.89f );
}

void
Configuration::write ()
{
	toml::table root;
	toml::table core;
	toml::table display;
	toml::table resolution;
	toml::table engine;
	toml::table camera;
	toml::table scale;
	/// Записываем параметры дисплея
	resolution.insert ( "width", m_display.resolution.width );
	resolution.insert ( "height", m_display.resolution.height );
	display.insert ( "Resolution", resolution );
	root.insert_or_assign ( "Display", display );
	/// Записываем параметры движка
	engine.insert ( "models directory", m_engine.modelDirPath );
	root.insert_or_assign ( "Engine", engine );
	/// Записываем параметры ядра
	core.insert ( "appName", m_vulkan.appName );
	core.insert ( "engineName", m_vulkan.engineName );
	toml::array validationLayers;
	for ( const auto & layer : m_vulkan.validationLayers )
	{
		validationLayers.push_back ( layer );
	}
	core.insert ( "validation layers", validationLayers );
	toml::array deviceExtension;
	for ( const auto & extension : m_vulkan.deviceExtension )
	{
		deviceExtension.push_back ( extension );
	}
	core.insert ( "device extension", deviceExtension );
	root.insert_or_assign ( "Core", core );
	/// Записываем параметры камеры
	camera.insert ( "incline", m_camera.theta );
	scale.insert ( "max", m_camera.scale.max );
	scale.insert ( "min", m_camera.scale.min );
	camera.insert ( "scale", scale );
	root.insert ( "Camera", camera );

	/// Записываем в файл
	std::ofstream fout ( "./configuration.toml" );
	fout<<root<<std::endl;
	fout.close ();
}

Configuration::~Configuration ()
{
	write ();
}

const Configuration::Display &
Configuration::display ()
{
	return instance ()->m_display;
}

const Configuration::Engine &
Configuration::engine ()
{
	return instance ()->m_engine;
}

const Configuration::Camera &
Configuration::camera ()
{
	return instance ()->m_camera;
}
