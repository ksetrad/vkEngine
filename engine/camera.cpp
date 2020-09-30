//
// Created by Владимир on 15.09.2020.
//
#include "engine/camera.h"
#include "tools/configuration.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

void
Camera::setDisplayCoordShift ( const glm::vec3 & new_shift )
{
	/// Сдвиг осуществляется с учетом направления взгляда камеры
	shift.x += new_shift.x * std::cos ( phi ) + new_shift.y * cos ( phi + M_PI_2 );
	shift.z += new_shift.x * std::sin ( phi ) + new_shift.y * sin ( phi + M_PI_2 );

	/// Задаем сдвиг
	worldTranspose[ 3 ][ 0 ] = shift[ 0 ];
	worldTranspose[ 3 ][ 1 ] = shift[ 1 ];
	worldTranspose[ 3 ][ 2 ] = shift[ 2 ];

	/// Вычисляем видовую матрицу
	calcView ();
}

const glm::vec3 &
Camera::getShift () const
{
	return shift;
}

const glm::vec3 &
Camera::getDirection () const
{
	return direction;
}

const glm::mat4 &
Camera::getView () const
{
	return view;
}

void
Camera::calcView ()
{
	/// Вычисляем новую видовую матрицу
	view = cameraTranspose * cameraRotation * worldTranspose;
}

void
Camera::setDefault ()
{
	theta = Configuration::camera ().theta;
	/// Сбрасываем значения матриц
	cameraTranspose = glm::mat4 ( 1 );
	worldTranspose = glm::mat4 ( 1 );
	/// Устанавливаем матрицу поворота в начальное положение
	setPhi ( 0 );
	/// Устанавливаем масштаб
	setScale ( ( Configuration::camera ().scale.max + Configuration::camera ().scale.min ) / 2 );
	/// Вычисляем видовую матрицу
	calcView ();
}

Camera::Camera () : worldTranspose ( 1 ), cameraTranspose ( 1 ) { setDefault (); }

void
Camera::setPhi ( const float & value )
{
	phi += value;
	/// "Удерживаем" значение phi в диапазоне от 0 до 2ПИ
	if ( phi >= M_PI2 )
	{
		phi -= M_PI2;
	}
	else if ( phi < 0 )
	{
		phi += M_PI2;
	}
	/// Устанавливаем поворот камеры
	cameraRotation = glm::mat4 ( 1 );
	cameraRotation = glm::rotate ( cameraRotation, theta, glm::vec3 { 1, 0, 0 } );
	cameraRotation = glm::rotate ( cameraRotation, phi, glm::vec3 { 0, 1, 0 } );
	/// Вычисляем новую видовую матрицу
	calcView ();
	/// Вычисляем направление "взгляда" камеры
	direction = cameraRotation * glm::vec4 ( 0, 0, 1, 1 );
}

void
Camera::setScale ( const float & delta_scale )
{
	/// Вычисляем масштаб
	if ( delta_scale > 0 )
	{
		/// Нижняя граница (отдаление)
		if ( scale + delta_scale <= Configuration::camera().scale.max )
		{
			scale += delta_scale;
		}
		else
		{
			scale = Configuration::camera().scale.max;
		}
	}
	else
	{
		/// Верхняя граница (приближение)
		if ( scale + delta_scale >= Configuration::camera().scale.min )
		{
			scale += delta_scale;
		}
		else
		{
			scale = Configuration::camera().scale.min;
		}
	}
	/// Масштабирование достигается приближением/отдалением камеры по оси Z проходящей по направлению обзора камеры (см. видовую матрицу)
	cameraTranspose[ 3 ][ 0 ] = 0;
	cameraTranspose[ 3 ][ 1 ] = 0;
	cameraTranspose[ 3 ][ 2 ] = -scale;
	/// Вычисляем новую видовую матрицу
	calcView ();
}

