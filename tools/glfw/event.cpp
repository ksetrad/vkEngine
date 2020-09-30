//
// Created by Владимир on 14.09.2020.
//

#include "event.h"

using namespace glfw;

MouseEvent::MouseEvent (
		MouseEvent::MouseButtons mButton,
		const glm::vec2 & mPos,
		const Event::Mods & mMod
) :
		Event ( mMod ),
		m_button ( mButton ), m_pos ( mPos )
{
}

Event::Event ( const Event::Mods & m_mod ) :
		m_mod ( m_mod )
{
}

KeyEvent::KeyEvent (
		KeyEvent::KeyButtons mButton,
		const Event::Mods & mMod
) : Event ( mMod ), m_button ( mButton )
{
}

MouseWheelEvent::MouseWheelEvent (
		double delta,
		const Event::Mods & mMod
) : Event ( mMod ), m_delta ( delta )
{

}

const double &
MouseWheelEvent::delta () const
{
	return m_delta;
}
