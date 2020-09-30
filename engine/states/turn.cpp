//
// Created by Владимир on 15.09.2020.
//

#include "turn.h"
#include "engine/scene.h"

using namespace engine;

Turn::Turn ( Scene * scene ) : State ( scene )
{

}

void
Turn::mouseMoveEvent ( const glfw::MouseEvent & event )
{
	constexpr float turnStep = M_PI / 576;
	glm::i32vec2 newPoint = event.pos ();
	float delta = newPoint.x - prevPos.x;
	std::lock_guard <std::mutex> lockGuard ( scene->update );
	scene->camera.setPhi ( turnStep * delta );
	prevPos = newPoint;
}

void
Turn::mousePressEvent ( const glfw::MouseEvent & event )
{

}

void
Turn::mouseReleaseEvent ( const glfw::MouseEvent & event )
{
	switch ( event.button () )
	{
		case glfw::MouseEvent::MOUSE_LEFT_BUTTON:
			break;
		case glfw::MouseEvent::MOUSE_RIGHT_BUTTON:
			scene->selectState ( rootType );
			break;
		default:;
	}
}

void
Turn::switchMouseEvent (
		const glfw::MouseEvent & event,
		const StateType & root
)
{
	prevPos = { event.pos ().x, event.pos ().y };
	State::switchMouseEvent ( event, root );
}

