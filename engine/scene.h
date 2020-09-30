//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

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
#include <mutex>

namespace engine
{
	class Scene : public glfw::Handler
	{
		public:
			Scene ();

			virtual ~Scene ();

			void
			mainLoop ();

			uint32_t
			getImage ( vk::Semaphore * pWaitSemaphore );

			void
			updateUniform ( const int & id );

			void
			switchMouseEvent (
					const glfw::MouseEvent & event,
					const engine::StateType & state
			);

			void
			selectState ( const StateType & type );

			/// Мьютекс обновления глобальных данных
			std::mutex update;

			/// Камера
			engine::Camera camera;

			/// Текущее разрешение экрана
			glm::i32vec2 resolution;

		protected:
			void
			mouseMoveEvent ( const glfw::MouseEvent & event ) override;

			void
			mousePressEvent ( const glfw::MouseEvent & event ) override;

			void
			mouseReleaseEvent ( const glfw::MouseEvent & event ) override;

			void
			keyPressEvent ( const glfw::KeyEvent & event ) override;

			void
			keyRepeatEvent ( const glfw::KeyEvent & event ) override;

			void
			mouseWheelEvent ( const glfw::MouseWheelEvent& event ) override;

		private:
			vk::Core * core;

			MainRenderPass * mainRenderPass;

			vk::PipeLine * mainPipeLine;

			CommandPool * commandPool;

			vk::DescriptorsPool * descriptorsPool;

			vk::FrameBuffer * frameBuffers;

			ModelFactory * modelFactory;

			Environment * environment;

			/// Набор глобальных буферов
			vk::UniformBufferSet * bufferSet;

			/// Заборы кадров буферизации
			std::vector <vk::Fence *> inFlightFences;

			/// Указатели на заборы кадров буферизации для используемых в данных момент изображений цепочки
			std::vector <vk::Fence *> imagesInFlight;

			/// Семафоры
			std::vector <vk::Semaphore *> renderFinishedSemaphores;

			std::vector <vk::Semaphore *> imageAvailableSemaphores;

			/// Максимальное число кадров в полете
			int frame_number { 3 };

			/// Номер текущего кадра
			int currentFrameId { 0 };

			/// Uniforms
			engine::Uniform uniform;


			/// Текущее состояние сцены
			State * currentState;

			/// Массив состояний
			std::map <StateType, std::unique_ptr <State> > states;



	};
}// namespace engine
#endif//ENGINE_SCENE_H
