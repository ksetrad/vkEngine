//
// Created by Владимир on 09.09.2020.
//

#ifndef ENGINE_MAINRENDERPASS_H
#define ENGINE_MAINRENDERPASS_H

#include "tools/vk/renderpass.h"

namespace engine
{
    class MainRenderPass
            : public vk::RenderPass
        {
        public:
            MainRenderPass (
                    vk::LogicalDevice * device ,
                    vk::SwapChain * swapChain
                           );
        };
}
#endif //ENGINE_MAINRENDERPASS_H
