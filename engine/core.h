//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

#include "camera.h"
#include "commandPool.h"
#include "engine/common/uniform.h"
#include "mainRenderPass.h"
#include "modelFactory.h"
#include "tools/glfw/handler.h"
#include "tools/vk/core.h"
#include "tools/vk/frameBuffer.h"
#include "tools/vk/pipeLine.h"
#include "tools/vk/synchronization/fence.h"
#include "tools/vk/synchronization/semaphore.h"
#include "tools/vk/uniformBufferSet.h"
#include <engine/states/state.h>
#include <map>
#include <memory>
namespace engine
{
	class Core : public glfw::Handler
	{
		public:
		Core ();

		virtual ~Core ();

		void
		mainLoop ();

		uint32_t
		getImage ( vk::Semaphore *pWaitSemaphore );

		void
		updateUniform ( const int &id );

		void
		switchMouseEvent (
		        const glfw::MouseEvent &event,
		        const engine::StateType &state );

		void
		selectState ( const StateType &type );

		protected:
		void
		mouseMoveEvent ( const glfw::MouseEvent &event ) override;

		void
		mousePressEvent ( const glfw::MouseEvent &event ) override;

		void
		mouseReleaseEvent ( const glfw::MouseEvent &event ) override;

		private:
		vk::Core *core;

		MainRenderPass *mainRenderPass;

		vk::PipeLine *mainPipeLine;

		CommandPool *commandPool;

		vk::DescriptorsPool *descriptorsPool;

		vk::FrameBuffer *frameBuffers;

		ModelFactory *modelFactory;

		Environment *environment;

		/// Набор глобальных буферов
		vk::UniformBufferSet *bufferSet;

		/// Заборы кадров буферизации
		std::vector< vk::Fence * > inFlightFences;

		/// Указатели на заборы кадров буферизации для используемых в данных момент изображений цепочки
		std::vector< vk::Fence * > imagesInFlight;

		/// Семафоры
		std::vector< vk::Semaphore * > renderFinishedSemaphores;

		std::vector< vk::Semaphore * > imageAvailableSemaphores;

		/// Максимальное число кадров в полете
		int frame_number { 3 };

		/// Номер текущего кадра
		int currentFrameId { 0 };

		/// Uniforms
		engine::Uniform uniform;

		engine::Camera camera;

        State* currentState;

		std::map< StateType,  std::unique_ptr < State > > states;
	};
}// namespace engine
#endif//ENGINE_CORE_H
