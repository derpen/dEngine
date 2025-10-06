#include <renderer/VulkanEngine.h>

#include <SDL3/SDL.h>
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

    _isInitialized = true;
}


void VulkanEngine::Render() {
}


void VulkanEngine::CleanUp() {
    loadedEngine = nullptr;
    fmt::println("We are cleaned, man");
}
