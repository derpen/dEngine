#pragma once

#include <renderer/VulkanTypes.h>
#include <renderer/VulkanDescriptors.h>
#include <VkBootstrap.h>

// Not performant for bigger projects (then why would you put it in the tutorial!!!)
struct DeletionQueue
{
	std::deque<std::function<void()>> deletors;

	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queue to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)(); //call functors
		}

		deletors.clear();
	}
};

struct FrameData {
	// Commands
	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	// Rendering synchronization shenanigans
	VkSemaphore _swapchainSemaphore, _renderSemaphore;
	VkFence _renderFence;

	DeletionQueue _deletionQueue;
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

	DeletionQueue _mainDeletionQueue;

	//draw resources
	AllocatedImage _drawImage;
	VkExtent2D _drawExtent;

	VmaAllocator _allocator;

	/////////////////////////////////////
	/// Descriptors
	/////////////////////////////////////
	DescriptorAllocator globalDescriptorAllocator;
	VkDescriptorSet _drawImageDescriptors;
	VkDescriptorSetLayout _drawImageDescriptorLayout;


	/////////////////////////////////////
	/// Pipelines
	/////////////////////////////////////
	VkPipeline _gradientPipeline;
	VkPipelineLayout _gradientPipelineLayout;

	/////////////////////////////////////
	/// Immediate submit structures (ImGUI related)
	/////////////////////////////////////
	/// @TODO: Command might not be needed
    VkFence _immFence;
    VkCommandBuffer _immCommandBuffer;
    VkCommandPool _immCommandPool;

	void init();
	void render();
	void render_background(VkCommandBuffer cmd);
	void cleanup();
	void immediate_submit(std::function<void(VkCommandBuffer cmd)>&& function);

private:
	void init_vulkan();
	void create_swapchain(uint32_t width, uint32_t height);
	void destroy_swapchain();
	void init_swapchain();
	void init_commands();
	void init_sync_structures();
	void init_descriptors();
	void init_pipelines();
	void init_background_pipelines();
	void init_imgui();
};