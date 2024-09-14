//
// Created by somi on 9/13/24.
//

#include "create.h"

#include <fstream>
#include <sstream>

#include "log.h"

auto some::createBufferLayout(const uint64_t stride,
                              const wgpu::VertexAttribute *attributes,
                              const size_t attributeCount,
                              const wgpu::VertexStepMode stepMode)
    -> wgpu::VertexBufferLayout {
    return wgpu::VertexBufferLayout{
        .arrayStride = stride,
        .stepMode = stepMode,
        .attributeCount = attributeCount,
        .attributes = attributes
    };
}

auto some::createShaderModule(const std::string &shaderPath,
                              const wgpu::Device &device)
    -> wgpu::ShaderModule {
    log(std::format("Creating shader module from source: {}", shaderPath));
    std::stringstream ss;
    ss << std::ifstream(shaderPath).rdbuf();
    const std::string source = ss.str();
    wgpu::ShaderSourceWGSL wgsl;
    wgsl.code = source.c_str();
    const wgpu::ShaderModuleDescriptor shaderDesc = {.nextInChain = &wgsl};
    auto shaderModule = device.CreateShaderModule(&shaderDesc);
    log("Shader module created");
    return shaderModule;
}
