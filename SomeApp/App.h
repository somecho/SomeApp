#ifndef SOMEAPP_H
#define SOMEAPP_H

#include <memory>
#include <GLFW/glfw3.h>
#include <webgpu/webgpu_cpp.h>

namespace some {
    struct GLFWwindowDeleter {
        void operator()(GLFWwindow *ptr) const {
            if (ptr) glfwDestroyWindow(ptr);
        }
    };

    struct AppSettings {
        int width = 800;
        int height = 600;
        std::string title = "SomeApp";
    };

    class App {
    public:
        App();

        explicit App(const AppSettings &settings);

        auto pollEvents() const -> void;

        [[nodiscard]]
        auto shouldClose() const -> bool;

        [[nodiscard]]
        auto getCurrentTextureView() const -> wgpu::TextureView;

        wgpu::Surface surface;
        wgpu::SurfaceCapabilities capabilities;
        wgpu::Device device;

        [[nodiscard]]
        auto getWidth() const -> int { return width; }

        [[nodiscard]]
        auto getHeight() const -> int { return height; }

    private:
        auto setupGlfw() -> void;

        auto createInstance() -> void;

        auto requestAdapter() -> void;

        auto requestDevice() -> void;

        auto createAndConfigureSurface() -> void;

        std::unique_ptr<GLFWwindow, GLFWwindowDeleter> window;
        int width = 800;
        int height = 600;
        std::string title = "WebGPUApp";
        wgpu::Instance instance;
        wgpu::Adapter adapter;
    };
}

#endif
