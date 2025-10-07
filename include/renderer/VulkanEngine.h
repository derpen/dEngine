#pragma once

#include <renderer/VulkanTypes.h>
#include <VkBootstrap.h>

struct FrameData {
	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;
};

constexpr unsigned int FRAME_OVERLAP = 2;

class VulkanEngine {
public:
	bool _isInitialized{ false };
	int _frameNumber{ 0 };
	VkExtent2D _windowExtent{ 1700 , 900 };

	static VulkanEngine& Get();

	struct SDL_Window* _window{ nullptr };
	struct SDL_Renderer* _renderer{ nullptr };

	/////////////////////////////////////
	/// Instance, device, and all those init
	/////////////////////////////////////
	VkInstance _instance;// Vulkan library handle
	VkDebugUtilsMessengerEXT _debug_messenger;// Vulkan debug output handle
	VkPhysicalDevice _chosenGPU;// GPU chosen as the default device
	VkDevice _device; // Vulkan device for commands
	VkSurfaceKHR _surface;// Vulkan window surface

	/////////////////////////////////////
	/// Swapchains
	/////////////////////////////////////
	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat;
	std::vector<VkImage> _swapchainImages;
	std::vector<VkImageView> _swapchainImageViews;
	VkExtent2D _swapchainExtent;

	/////////////////////////////////////
	/// Command queues
	/////////////////////////////////////
	FrameData _frames[FRAME_OVERLAP];
	FrameData& get_current_frame() { return _frames[_frameNumber % FRAME_OVERLAP]; };
	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;

	void Init();
	void Render();
	void CleanUp();

private:
	void init_vulkan();
	void create_swapchain(uint32_t width, uint32_t height);
	void destroy_swapchain();
	void init_swapchain();
	void init_commands();
	void init_sync_structures();
};