//
// Created by Владимир on 15.09.2020.
//
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

void
Camera::setShift ( const glm::vec3 & new_shift )
{
	shift.x += new_shift.x * std::cos ( phi ) + new_shift.y * cos ( phi + M_PI_2 );
	shift.z += new_shift.x * std::sin ( phi ) + new_shift.y * sin ( phi + M_PI_2 );
	calcView ();
}

void
Camera::setDirection ( const glm::vec3 & new_dir )
{

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

	worldTranspose[ 3 ][ 0 ] = shift[ 0 ];
	worldTranspose[ 3 ][ 1 ] = -shift[ 1 ];
	worldTranspose[ 3 ][ 2 ] = shift[ 2 ];

	cameraTranspose[ 3 ][ 0 ] = 0;
	cameraTranspose[ 3 ][ 1 ] = 0;
	cameraTranspose[ 3 ][ 2 ] = -scale;

	view = cameraTranspose * cameraRotation * worldTranspose;
}

void
Camera::setDefault ()
{
	direction = glm::normalize ( glm::vec3 ( -1, 1.5, 0 ) );
	theta = 0.89;
	setPhi ( 0 );
	cameraTranspose = glm::mat4 ( 1 );
	worldTranspose = glm::mat4 ( 1 );
	cameraTranspose[ 3 ][ 0 ] = 0;
	cameraTranspose[ 3 ][ 1 ] = 0;
	cameraTranspose[ 3 ][ 2 ] = -scale;

	calcView ();
}

Camera::Camera () : worldTranspose ( 1 ), cameraTranspose ( 1 ) { setDefault (); }

void
Camera::setPhi ( const float & value )
{
	phi += value;
	direction = { std::cos ( phi ), std::sin ( phi ) * std::cos ( theta ), std::sin ( theta ) };
	direction = normalize ( direction );
	cameraRotation = glm::mat4 ( 1 );

	cameraRotation = glm::rotate ( cameraRotation, theta, glm::vec3 { 1, 0, 0 } );
	cameraRotation = glm::rotate ( cameraRotation, phi, glm::vec3 { 0, 1, 0 } );
	calcView ();
}

void
Camera::setScale ( const float & delta_scale )
{

	if ( delta_scale > 0 )
	{
		if ( scale + delta_scale <= 80 )
		{
			scale += delta_scale;
		}
		else
		{
			scale = 80;
		}
	}
	else
	{
		if ( scale + delta_scale >= 10 )
		{
			scale += delta_scale;
		}
		else
		{
			scale = 10;
		}
	}
	calcView();
}

