#include <renderer/VulkanEngine.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>
#include <renderer/VulkanTypes.h>
#include <chrono>
#include <thread>

constexpr bool bUseValidationLayers = false;

VulkanEngine* loadedEngine = nullptr;

VulkanEngine& VulkanEngine::Get() { return *loadedEngine; }

//////////////////////////////////
/// Start of Public 
void VulkanEngine::Init() {
	// only one engine initialization is allowed with the application.
    assert(loadedEngine == nullptr);
    loadedEngine = this;

    _window = SDL_CreateWindow(
        "dEngine", 
        _windowExtent.width, 
        _windowExtent.height, 
        SDL_WINDOW_VULKAN);

    init_vulkan();

	init_swapchain();

	init_commands();

	init_sync_structures();

    _isInitialized = true;
}


void VulkanEngine::Render() {
}


void VulkanEngine::CleanUp() {
    loadedEngine = nullptr;
    fmt::println("We are cleaned, man");
}

void VulkanEngine::init_vulkan() {
	vkb::InstanceBuilder builder;

	//make the vulkan instance, with basic debug features
	auto inst_ret = builder.set_app_name("dEngine")
		.request_validation_layers(bUseValidationLayers)
		.use_default_debug_messenger()
		.require_api_version(1, 3, 0)
		.build();

	vkb::Instance vkb_inst = inst_ret.value();

	//grab the instance 
	_instance = vkb_inst.instance;
	_debug_messenger = vkb_inst.debug_messenger;

	SDL_Vulkan_CreateSurface(_window, _instance, NULL, &_surface);

	//vulkan 1.3 features
	VkPhysicalDeviceVulkan13Features features;
	features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES;
	features.dynamicRendering = true;
	features.synchronization2 = true;

	//vulkan 1.2 features
	VkPhysicalDeviceVulkan12Features features12;
	features12.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES;
	features12.bufferDeviceAddress = true;
	features12.descriptorIndexing = true;

	//use vkbootstrap to select a gpu. 
	//We want a gpu that can write to the SDL surface and supports vulkan 1.3 with the correct features
	vkb::PhysicalDeviceSelector selector{ vkb_inst };
	vkb::PhysicalDevice physicalDevice = selector
		.set_minimum_version(1, 3)
		.set_required_features_13(features)
		.set_required_features_12(features12)
		.set_surface(_surface)
		.select()
		.value();

	//create the final vulkan device
	vkb::DeviceBuilder deviceBuilder{ physicalDevice };

	vkb::Device vkbDevice = deviceBuilder.build().value();

	// Get the VkDevice handle used in the rest of a vulkan application
	_device = vkbDevice.device;
	_chosenGPU = physicalDevice.physical_device;
}

void VulkanEngine::init_swapchain() {

}

void VulkanEngine::init_commands() {

}

void VulkanEngine::init_sync_structures() {

}
