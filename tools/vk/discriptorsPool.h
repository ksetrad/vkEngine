//
// Created by Владимир on 12.09.2020.
//

#ifndef TOOLS_VK_DISCRIPTORSPOOL_H
#define TOOLS_VK_DISCRIPTORSPOOL_H

#include "core.h"
#include "pipeLine.h"
namespace vk
{
	class DescriptorsPool
	{
		public:
		explicit DescriptorsPool ( vk::Core *core );

		virtual ~DescriptorsPool ();

		void
		createDescritorSets (
		        const std::vector< VkBuffer > &ubo_vector,
		        const pipeline::PipeLineLayout *layout,
		        const int &size );

		const std::vector< VkDescriptorSet > &
		getDescriptorSets () const;

		private:
		Core *core;

		VkDescriptorPool descriptorPool;

		std::vector< VkDescriptorSet > descriptorSets;
	};
}// namespace vk
#endif//TOOLS_VK_DISCRIPTORSPOOL_H
