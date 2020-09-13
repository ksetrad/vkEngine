//
// Created by Владимир on 12.09.2020.
//

#include "environment.h"

using namespace engine;

Environment::~Environment ()
{
        for ( const auto & model:models )
        {
                delete model;
        }
}
