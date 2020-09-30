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
			setShift ( const glm::vec3 & new_shift );

			void
			setDirection ( const glm::vec3 & new_dir );

			[[nodiscard]] const glm::vec3 &
			getShift () const;

			[[nodiscard]] const glm::vec3 &
			getDirection () const;

			[[nodiscard]] const glm::mat4 &
			getView () const;

			void
			setPhi ( const float & value );

			void
			setDefault ();

			void
			setScale(const float& delta_scale);

		private:
			void
			calcView ();

			glm::mat4 worldTranspose;

			glm::mat4 cameraTranspose;

			glm::mat4 cameraRotation;

			glm::vec3 shift;

			glm::vec3 direction;

			glm::mat4 view;

			float phi { 0 };

			float theta { 0 };

			float scale { 40 };
	};
}// namespace engine
#endif//ENGINE_CAMERA_H
