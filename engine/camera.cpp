//
// Created by Владимир on 15.09.2020.
//
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace engine;

void
Camera::setShift ( const glm::vec3 & new_shift )
{

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
        glm::mat4 transpose ( 1 );
        glm::mat4 rotation ( 1 );
        transpose[ 3 ][ 0 ] = shift[ 0 ];
        transpose[ 3 ][ 1 ] = -shift[ 1 ];
        transpose[ 3 ][ 2 ] = shift[ 2 ];

        rotation = glm::rotate ( rotation , static_cast<float>(asin ( -direction[ 1 ] )  ) , glm::vec3 { 1 , 0 , 0 } );
        rotation = glm::rotate ( rotation , static_cast<float>(asin ( direction[ 0 ] )) , glm::vec3 { 0 , 1 , 0 } );
        view = transpose * rotation;
}

void
Camera::setDefault ()
{
        direction = glm::normalize(glm::vec3 ( -0.25 , -0.25 , 1 ));
        shift = glm::vec3 ( 0 , 2 , -10 );
        calcView ();
}

Camera::Camera () { setDefault (); }

