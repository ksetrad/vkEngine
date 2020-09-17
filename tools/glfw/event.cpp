//
// Created by Владимир on 14.09.2020.
//

#include "event.h"

using namespace glfw;

MouseEvent::MouseEvent (
		MouseEvent::MouseButtons mButton,
		const glm::vec2 &mPos,
		const Event::Mods &mMod
) :
		Event ( mMod ),
		m_button ( mButton ), m_pos ( mPos )
{
}

Event::Event ( const Event::Mods &m_mod ) :
		m_mod ( m_mod )
{
}
