#ifdef linux
#define GLFW_EXPOSE_NATIVE_X11
#endif

#include "App.h"
#include "callbacks.h"

#include <stdexcept>
#include <GLFW/glfw3native.h>

#include "log.h"

some::App::App() : App(AppSettings{}) {
}

some::App::App(const AppSettings &settings): width(settings.width),
                                             height(settings.height),
                                             title(settings.title) {
    setupGlfw();
    createInstance();
    requestAdapter();
    requestDevice();
    createAndConfigureSurface();
    log("App initialized, ready to render");
}

auto some::App::pollEvents() const -> void {
    glfwPollEvents();
    instance.ProcessEvents();
}

auto some::App::shouldClose() const -> bool {
    return glfwWindowShouldClose(window.get());
}

auto some::App::getCurrentTextureView() const -> wgpu::TextureView {
    wgpu::SurfaceTexture tex;
    surface.GetCurrentTexture(&tex);
    return tex.texture.CreateView();
}

auto some::App::setupGlfw() -> void {
    log("Initializing GLFW");
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW3");
    }
    log("GLFW Initialized");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    log(std::format("Creating window: {}x{}", this->width, this->height));
    window.reset(glfwCreateWindow(this->width, this->height,
                                  this->title.c_str(),
                                  nullptr, nullptr));
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window.get());
    glfwSetKeyCallback(window.get(), defaultKeyCallback);
}

auto some::App::createInstance() -> void {
    log("Creating instance");
    instance = wgpu::CreateInstance();
    if (!instance) {
        throw std::runtime_error("Failed to create instance");
    }
    log("Instance created");
}

auto some::App::requestAdapter() -> void {
    log("Requesting adapter");
    instance.RequestAdapter(nullptr, adapterRequestCallback, &this->adapter);
}

auto some::App::requestDevice() -> void {
    wgpu::DeviceDescriptor deviceDesc;
    deviceDesc.uncapturedErrorCallbackInfo = {
        .callback = uncapturedErrorCallback
    };
    log("Requesting device");
    adapter.RequestDevice(&deviceDesc, deviceRequestCallback, &this->device);
}

auto some::App::createAndConfigureSurface() -> void {
#ifdef linux
    wgpu::SurfaceDescriptorFromXlibWindow osWindow;
    osWindow.display = glfwGetX11Display();
    osWindow.window = glfwGetX11Window(window.get());
#endif
    const wgpu::SurfaceDescriptor surfaceDesc{.nextInChain = &osWindow};


    log("Creating surface");
    surface = instance.CreateSurface(&surfaceDesc);
    if (!surface) {
        throw std::runtime_error("Failed to create surface");
    }
    log("Surface created");
    surface.GetCapabilities(this->adapter, &this->capabilities);

    const wgpu::SurfaceConfiguration config{
        .device = this->device,
        .format = this->capabilities.formats[0],
        .width = static_cast<uint32_t>(this->width),
        .height = static_cast<uint32_t>(this->height),
    };

    log("Configuring surface");
    surface.Configure(&config);
    log("Surface configured");
}
