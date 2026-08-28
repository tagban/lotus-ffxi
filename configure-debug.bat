@echo off
set VULKAN_SDK=C:\VulkanSDK\1.4.357.0
set GLM_ROOT_DIR=C:\Users\Gaming\Desktop\PortJeuno\vendor\glm
set SDL3_DIR=C:\Users\Gaming\Desktop\PortJeuno\vendor\SDL3-3.4.14\cmake
set VulkanMemoryAllocator_DIR=C:\Users\Gaming\Desktop\PortJeuno\vendor\vma-install\share\cmake\VulkanMemoryAllocator
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
"C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -S "%~dp0." -B "%~dp0build-debug" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM="C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl -DSLANGC=C:\VulkanSDK\1.4.357.0\Bin\slangc.exe -DCMAKE_CXX_MODULE_STD=1 -DCMAKE_EXPERIMENTAL_CXX_IMPORT_STD=451f2fe2-a8a2-47c3-bc32-94786d8fc91b
