#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <renderer/VulkanEngine.h>

static VulkanEngine vulkanEngine;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    vulkanEngine.init();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    ImGui_ImplSDL3_ProcessEvent(event);

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	// Start the Dear ImGui frame
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

    if (ImGui::Begin("background")) {
		ComputeEffect& selected = vulkanEngine.backgroundEffects[vulkanEngine.currentBackgroundEffect];
		
		ImGui::Text("Selected effect: ", selected.name);
	
		ImGui::SliderInt("Effect Index", &vulkanEngine.currentBackgroundEffect,0, vulkanEngine.backgroundEffects.size() - 1);
	
		ImGui::InputFloat4("data1",(float*)& selected.data.data1);
		ImGui::InputFloat4("data2",(float*)& selected.data.data2);
		ImGui::InputFloat4("data3",(float*)& selected.data.data3);
		ImGui::InputFloat4("data4",(float*)& selected.data.data4);
	}
	ImGui::End();

    ImGui::Render();

    vulkanEngine.render();
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    vulkanEngine.cleanup();
}
