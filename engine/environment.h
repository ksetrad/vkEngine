//
// Created by Владимир on 12.09.2020.
//

#ifndef ENGINE_ENVIRONMENT_H
#define ENGINE_ENVIRONMENT_H

#include <vector>
#include "engine/data/model.h"

namespace engine
{
    struct Environment
        {
            virtual ~Environment ();

            std::vector < Model* > models;
        };
}
#endif //ENGINE_ENVIRONMENT_H
