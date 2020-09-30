//
// Created by Владимир on 15.09.2020.
//

#include "shift.h"
#include "engine/scene.h"

using namespace engine;

Shift::Shift ( Scene * scene ) : State ( scene )
{

}

void
Shift::mouseMoveEvent ( const glfw::MouseEvent & event )
{
	glm::vec2 newPoint = event.pos ();
	std::lock_guard <std::mutex> lockGuard ( scene->update );
	auto delta_x = ( newPoint.x - prevPos.x ) * 1.f / scene->resolution.x;
	auto delta_y = ( newPoint.y - prevPos.y ) * 1.f / scene->resolution.y;
	scene->camera.setDisplayCoordShift ( { 128 * delta_x, 128 * delta_y, 0 } );
	prevPos.x = newPoint.x;
	prevPos.y = newPoint.y;
}

void
Shift::mousePressEvent ( const glfw::MouseEvent & event )
{

}

void
Shift::mouseReleaseEvent ( const glfw::MouseEvent & event )
{
	switch ( event.button () )
	{
		case glfw::MouseEvent::MOUSE_LEFT_BUTTON:
			scene->selectState ( rootType );
			break;
		case glfw::MouseEvent::MOUSE_RIGHT_BUTTON:
			break;
		default:;
	}
}

void
Shift::switchMouseEvent (
		const glfw::MouseEvent & event,
		const StateType & root
)
{
	prevPos = { event.pos ().x, event.pos ().y };
	State::switchMouseEvent ( event, root );
}
