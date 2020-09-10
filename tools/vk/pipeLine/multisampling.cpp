//
// Created by Владимир on 06.09.2020.
//

#include "multisampling.h"

using namespace vk::pipeline;

Multisampling::Multisampling ( const bool & isEnable )
{
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        createInfo.sampleShadingEnable = VK_FALSE;
        createInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        createInfo.minSampleShading = 1.0f;
        createInfo.pSampleMask = nullptr;
        createInfo.alphaToCoverageEnable = VK_FALSE;
        createInfo.alphaToOneEnable = VK_FALSE;
}

VkPipelineMultisampleStateCreateInfo *
Multisampling::getInfo ()
{
        return &createInfo;
}

