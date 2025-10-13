#pragma once

#include <renderer/VulkanTypes.h>

namespace VulkanUtils {
bool load_shader_module(const char* filePath, VkDevice device, VkShaderModule* outShaderModule);
}
