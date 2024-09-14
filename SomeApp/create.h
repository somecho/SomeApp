#ifndef CREATE_H
#define CREATE_H

#include <cstdint>
#include <webgpu/webgpu_cpp.h>

namespace some {
    auto createBufferLayout(uint64_t stride,
                      const wgpu::VertexAttribute *attributes,
                      size_t attributeCount = 1,
                      wgpu::VertexStepMode stepMode =
                              wgpu::VertexStepMode::Vertex)
        -> wgpu::VertexBufferLayout;

    auto createShaderModule(
        const std::string &shaderPath, const wgpu::Device &device) -> wgpu::ShaderModule;
}

#endif //CREATE_H
