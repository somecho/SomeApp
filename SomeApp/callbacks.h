#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <webgpu/webgpu_cpp.h>
#include <iostream>

#include "log.h"

namespace some {
    inline auto adapterRequestCallback(const WGPURequestAdapterStatus status,
                                       WGPUAdapter adapter,
                                       const char *message,
                                       void *userdata) -> void {
        if (status != WGPURequestAdapterStatus_Success) {
            throw std::runtime_error(message);
        }
        *static_cast<wgpu::Adapter *>(userdata) = wgpu::Adapter::Acquire(
            adapter);
        log("Adapter acquired");
    }

    inline const wgpu::ErrorCallback uncapturedErrorCallback =
            [](const WGPUErrorType type, const char *message,
               [[maybe_unused]] void *userdata) {
        if (type != WGPUErrorType_NoError) {
            throw std::runtime_error(message);
        }
    };

    inline auto deviceRequestCallback(const WGPURequestDeviceStatus status,
                                      WGPUDevice device,
                                      const char *message,
                                      void *userdata) -> void {
        if (status != WGPURequestDeviceStatus_Success) {
            throw std::runtime_error(message);
        }
        *static_cast<wgpu::Device *>(userdata) = wgpu::Device::Acquire(device);
        log("Device acquired");
    };

    inline GLFWkeyfun defaultKeyCallback =
            [](GLFWwindow *window, const int key, [[maybe_unused]] int scancode,
               const int action, [[maybe_unused]] int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    };
}
#endif //CALLBACKS_H
