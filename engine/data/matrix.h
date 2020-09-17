//
// Created by Владимир on 04.08.2020.
//

#ifndef SRC_ENGINE_RENDER_GAMESCENE_DATA_MATRIX_H
#define SRC_ENGINE_RENDER_GAMESCENE_DATA_MATRIX_H

#include <glm/mat4x4.hpp>

namespace engine::render::gameScene::data
{
	/// Абстрактный базовый класс матрицы
	class Matrix
	{
		public:
			[[nodiscard]] const glm::mat4 &
			get () const
			{
				return matrix;
			}

		protected:
			/// Матрица 4х4
			glm::mat4 matrix { 1.0 };
	};

	/// \brief Класс матрицы поворота
	class RotationMatrix : public Matrix
	{
		public:
			/// \brief Повернуть объект вокруг оси Х
			/// \param angle Угол поворота
			void
			rotateX ( const float &angle )
			{
				matrix = glm::mat4 ( 1, 0, 0, 0,
				                     0, std::cos ( angle ), -std::sin ( angle ), 0,
				                     0, std::sin ( angle ), std::cos ( angle ), 0,
				                     0, 0, 0, 1 ) *
				         matrix;
			}

			/// \briefПовернуть объект вокруг оси Y
			/// \param angle Угол поворота
			void
			rotateY ( const float &angle )
			{
				matrix = glm::mat4 ( std::cos ( angle ), 0, std::sin ( angle ), 0,
				                     0, 1, 0, 0,
				                     -std::sin ( angle ), 0, std::cos ( angle ), 0,
				                     0, 0, 0, 1 ) *
				         matrix;
			}

			/// \briefПовернуть объект вокруг оси Z
			/// \param angle Угол поворота
			void
			rotateZ ( const float &angle )
			{
				matrix = glm::mat4 ( std::cos ( angle ), -std::sin ( angle ), 0, 0,
				                     std::sin ( angle ), std::cos ( angle ), 0, 0,
				                     0, 0, 1, 0,
				                     0, 0, 0, 1 ) *
				         matrix;
			}

			void
			reset ()
			{
				matrix = glm::mat4 ( 1. );
			}
	};

	/// \brief Матрица сдвига
	class TransposeMatrix : public Matrix
	{
		public:
			/// \brief Установить сдвиг
			/// \param shift Сдвиг
			void
			setShift ( const glm::vec3 &new_shift )
			{
				shift = new_shift;
				matrix[ 3 ][ 0 ] = shift.x;
				matrix[ 3 ][ 1 ] = shift.y;
				matrix[ 3 ][ 2 ] = shift.z;
			}

			[[nodiscard]] const glm::vec3 &
			getShift () const
			{
				return shift;
			}

		private:
			/// Сдвиг
			glm::vec3 shift;
	};

	/// \brief Матрица масштабирования
	class ScaleMatrix : public Matrix
	{
		public:
			/// \brief Установить масштаб
			/// \param scale Масштаб
			void
			setScale ( const float &new_scale )
			{
				scale = new_scale;
				matrix[ 0 ][ 0 ] = scale;
				matrix[ 1 ][ 1 ] = scale;
				matrix[ 2 ][ 2 ] = scale;
			}

			/// Получить текущий масштаб
			/// \return
			[[nodiscard]] const float &
			getScale () const
			{
				return scale;
			}

		private:
			/// Фактор масштаба
			float scale { 1.f };
	};

	///Модельная матрица
	class ModelMatrix : public Matrix
	{
		public:
			void
			update ()
			{
				matrix = transposeMatrix.get () * rotationMatrix.get () * scaleMatrix.get ();
			}

			/// Матрица поворота
			RotationMatrix rotationMatrix;

			/// Матрица смещения
			TransposeMatrix transposeMatrix;

			/// Матрица поворота
			ScaleMatrix scaleMatrix;
	};


	/// Модельная матрица видовой матрицы
	class ViewModelMatrix : public Matrix
	{
		public:
			void
			update ()
			{
				matrix = rotationMatrix.get () * transposeMatrix.get () * scaleMatrix.get ();
			}

			/// Матрица поворота
			RotationMatrix rotationMatrix;

			/// Матрица смещения
			TransposeMatrix transposeMatrix;

			/// Матрица поворота
			ScaleMatrix scaleMatrix;
	};

	/// Видовая матрица
	class ViewMatrix : public Matrix
	{
		public:
			void
			update ()
			{
				modelMatrix.update ();
				matrix = transposeMatrix.get () * rotationMatrix.get () * modelMatrix.get ();
			}

			/// Матрица поворота
			RotationMatrix rotationMatrix;

			/// Матрица смещения
			TransposeMatrix transposeMatrix;

			/// Модельная матрица
			ViewModelMatrix modelMatrix;
	};

}// namespace engine::render::gameScene::data

#endif//SRC_ENGINE_RENDER_GAMESCENE_DATA_MATRIX_H
