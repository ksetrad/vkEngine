//
// Created by Владимир on 15.09.2020.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glm/glm.hpp>

namespace engine
{
	/// Основная камера сцены
	class Camera
	{
		public:
			/// \brief Конструктор
			Camera ();

			/// \brief Установить сдвиг экранных координат для вычисления сдвига координат в "мире"
			/// \param new_shift
			void
			setDisplayCoordShift ( const glm::vec3 & new_shift );

			/// \brief Получить сдвиг мировых координат
			/// \return сдвиг мировых координат
			[[nodiscard]] const glm::vec3 &
			getShift () const;

			/// \brief Получить направление обзора
			/// \return Направление
			[[nodiscard]] const glm::vec3 &
			getDirection () const;

			/// \brief Получить видовую матрицу
			/// \return Видовая матрица
			[[nodiscard]] const glm::mat4 &
			getView () const;

			/// \brief Установить угол поворота вокруг оси направленной вверх относительно плоскости мира
			/// \param value Угол поворота
			void
			setPhi ( const float & value );

			/// \brief Сбросить параметры камеры на "умолчание"
			void
			setDefault ();

			/// \brief Установить масштаб
			/// \param delta_scale шаг масштаба
			void
			setScale ( const float & delta_scale );

		private:
			/// \brief Вычислить видовую матрицу
			void
			calcView ();

			/// Матрица сдвига мира
			glm::mat4 worldTranspose;

			/// Матрица сдвига камеры в координатах где ось Z сонаправлена с направлением взгляда камеры
			glm::mat4 cameraTranspose;

			/// Матрица поворота взгляда камеры
			glm::mat4 cameraRotation;

			/// Сдвиг мировых координат
			glm::vec3 shift { 0, 0, 0 };

			/// Направление обзора
			glm::vec3 direction { 0, 0, 1 };

			/// Видовая матрица
			glm::mat4 view { 1 };

			/// Поворот вокруг оси, перпендикулярной поверхности
			float phi { 0 };

			/// Наклок камеры
			float theta { 0 };

			/// Фактор масштаба (отдаление по направлению)
			float scale { 0 };

			/// 2 ПИ
			const float M_PI2 = M_PI * 2;
	};
}// namespace engine
#endif//ENGINE_CAMERA_H
