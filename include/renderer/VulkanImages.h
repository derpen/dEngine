#pragma once

#include <vulkan/vulkan.h>

namespace VulkanUtils {
	void transition_image(VkCommandBuffer cmd, VkImage image, VkImageLayout currentLayout, VkImageLayout newLayout);
}
