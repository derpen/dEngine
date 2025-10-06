#pragma once

#include <renderer/VulkanTypes.h>

class VulkanEngine {
public:
	bool _isInitialized{ false };
	int _frameNumber{ 0 };
	VkExtent2D _windowExtent{ 1700 , 900 };

	static VulkanEngine& Get();

	struct SDL_Window* _window{ nullptr };
	struct SDL_Renderer* _renderer{ nullptr };

	void Init();
	void Render();
	void CleanUp();

private:

};