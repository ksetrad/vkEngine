//
// Created by Владимир on 12.09.2020.
//

#ifndef ENGINE_DATA_MODEL_H
#define ENGINE_DATA_MODEL_H

#include <vector>
#include <vulkan/vulkan.h>

#include "tools/vk/bufferObject.h"
#include "tools/vk/common/vertex.h"

namespace engine
{
	struct Model {
		/// Конструктор
		/// \param core ядро
		/// \param vertexes вершины
		/// \param indices индексы
		Model (
		        vk::Core *core,
		        const std::vector< vk::Vertex > &vertexes,
		        const std::vector< unsigned int > &indices );

		~Model ();

		/// Вершинный буффер
		vk::BufferObject vbo;

		/// Индексный буффер
		vk::BufferObject ibo;
	};
}// namespace engine
#endif//ENGINE_DATA_MODEL_H
