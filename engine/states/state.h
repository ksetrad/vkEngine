//
// Created by Владимир on 15.09.2020.
//

#ifndef ENGINE_STATES_STATE_H
#define ENGINE_STATES_STATE_H

#include <tools/glfw/event.h>

namespace engine
{

    enum StateType
        {
            IDLE ,
            TURN ,
            SHIFT
        };

    class Core;

    class State
        {
        public:
            explicit
            State ( Core * scene )
                    : scene ( scene ) { }

            /// Событие сдвига мыши в сцене
            /// \param event Событие
            virtual
            void
            mouseMoveEvent ( const glfw::MouseEvent & event )
            {
            }

            /// Событие нажатия клавиши мыши в сцене
            /// \param event Событие
            virtual
            void
            mousePressEvent ( const glfw::MouseEvent & event ) = 0;

            /// Событие отжатия клавиши мыши в сцене
            /// \param event Событие
            virtual
            void
            mouseReleaseEvent ( const glfw::MouseEvent & event ) = 0;

            /// Событие кручения колеса мыши в сцене
            /// \param event Событие
            virtual
            void
            mouseWheelEvent ( const glfw::MouseEvent & event ) { }


            /// Переключение при событии мыши
            /// \param event
            virtual
            void
            switchMouseEvent (
                    const glfw::MouseEvent & event ,
                    const StateType & root
                             )
            {
                    rootType = root;
            }

        protected:
            /// Игровая сцена
            Core * scene;

            /// Тип вызвавшего состояния
            StateType rootType { IDLE };
        };
}
#endif //ENGINE_STATES_STATE_H
