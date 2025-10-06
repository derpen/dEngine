#pragma once

#include <renderer/VulkanTypes.h>
#include <VkBootstrap.h>

class VulkanEngine {
public:
	bool _isInitialized{ false };
	int _frameNumber{ 0 };
	VkExtent2D _windowExtent{ 1700 , 900 };

	static VulkanEngine& Get();

	struct SDL_Window* _window{ nullptr };
	struct SDL_Renderer* _renderer{ nullptr };

	VkInstance _instance;// Vulkan library handle
	VkDebugUtilsMessengerEXT _debug_messenger;// Vulkan debug output handle
	VkPhysicalDevice _chosenGPU;// GPU chosen as the default device
	VkDevice _device; // Vulkan device for commands
	VkSurfaceKHR _surface;// Vulkan window surface

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;
	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;

	void Init();
	void Render();
	void CleanUp();

private:
	void init_vulkan();
	void init_swapchain();
	void init_commands();
	void init_sync_structures();
};