//
// Created by Владимир on 26.08.2020.
//

#include "core.h"
#include <tools/configuration.h>

using namespace vk;

Core::Core ( GLFWwindow *window ) :
		window ( window )
{

	/// Конструируем экземпляр Vulkan
	instance = new Instance ( window );

	/// Конструируем и настраиваем объект используемого GPU
	physicalDevice = new PhysicalDevice ( instance );

	/// Конструируем логический интерфейс GPU
	logicalDevice = new LogicalDevice ( instance, physicalDevice );

	/// Создаем цепочку смены кадров
	swapChain = new SwapChain ( instance, physicalDevice, logicalDevice );

	/// Получаем дескрипторы очередей
	graphicsQueue = new Queue ( logicalDevice, physicalDevice, Queue::GRAPHIC );
	presentationQueue = new Queue ( logicalDevice, physicalDevice, Queue::PRESENTATION );
}

Core::~Core ()
{
	/// Удаляем объекты оболочек очередей
	delete presentationQueue;
	delete graphicsQueue;
	/// Уничтожаем цепочку смены кадров
	delete swapChain;
	/// Уничтожаем экземпляр логического устройства
	delete logicalDevice;
	/// Уничтожаем экземпляр физического устройство
	delete physicalDevice;
	/// Уничтожаем экземпляр Vulkan
	delete instance;
	/// Разрушаем окно
	glfwDestroyWindow ( window );
}

LogicalDevice *
Core::getLogicalDevice () const
{
	return logicalDevice;
}

SwapChain *
Core::getSwapChain () const
{
	return swapChain;
}

GLFWwindow *
Core::getWindow () const
{
	return window;
}

PhysicalDevice *
Core::getPhysicalDevice () const
{
	return physicalDevice;
}

Queue *
Core::getGraphicsQueue () const
{
	return graphicsQueue;
}

Queue *
Core::getPresentationQueue () const
{
	return presentationQueue;
}
