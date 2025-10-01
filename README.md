# dEngine

Reloaded, Round 2

`git clone --recurse-submodules https://github.com/derpen/dEngine.git`

or, if already cloned without submodule

```sh
git submodule init
git submodule update
```


# Compile
Required (download separately, different for each platform)
- Cmake
- Vulkan-SDK

```sh
cmake -S . -B build
cmake --build build
```

# Libraries Used
- SDL3
- Vulkan
- Vk-bootsrap
- Vulkan Memory Allocator
- glm
- ImGui
- fmt
- fastgltf
