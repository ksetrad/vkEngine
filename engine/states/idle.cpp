//
// Created by Владимир on 15.09.2020.
//

#include "engine/states/idle.h"
#include "engine/scene.h"

using namespace engine;

void
Idle::mouseMoveEvent ( const glfw::MouseEvent &event )
{
	State::mouseMoveEvent ( event );
}

void
Idle::mousePressEvent ( const glfw::MouseEvent &event )
{
	switch ( event.button () )
	{
		case glfw::MouseEvent::MOUSE_LEFT_BUTTON:
			scene->selectState ( SHIFT );
			scene->switchMouseEvent ( event, IDLE );
			break;
		case glfw::MouseEvent::MOUSE_RIGHT_BUTTON:
			scene->selectState ( TURN );
			scene->switchMouseEvent ( event, IDLE );
			break;
		default:;
	}
}

void
Idle::mouseReleaseEvent ( const glfw::MouseEvent &event )
{
}

Idle::Idle ( Scene * scene ) : State ( scene ) {}
