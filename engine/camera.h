//
// Created by Владимир on 15.09.2020.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace engine
{
	class Camera
	{
		public:
			Camera ();

			void
			setShift ( const glm::vec3 &new_shift );

			void
			setDirection ( const glm::vec3 &new_dir );

			[[nodiscard]] const glm::vec3 &
			getShift () const;

			[[nodiscard]] const glm::vec3 &
			getDirection () const;

			[[nodiscard]] const glm::mat4 &
			getView () const;

			void
			setDefault ();

		private:
			void
			calcView ();

			glm::vec3 shift;

			glm::vec3 direction;

			glm::mat4 view;
	};
}// namespace engine
#endif//ENGINE_CAMERA_H
