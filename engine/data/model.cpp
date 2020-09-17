//
// Created by Владимир on 12.09.2020.
//

#include "engine/data/model.h"

using namespace engine;

Model::Model (
		vk::Core *core,
		const std::vector < vk::Vertex > &vertexes,
		const std::vector < uint32_t > &indices
) :
		vbo ( vk::BufferObject::VERTEX, core ),
		ibo ( vk::BufferObject::INDEX, core )
{
	vbo.allocate ( vertexes.size () * sizeof ( vk::Vertex ), vertexes.data (), vertexes.size () );
	ibo.allocate ( indices.size () * sizeof ( uint32_t ), indices.data (), indices.size () );
}

Model::~Model ()
{
}
