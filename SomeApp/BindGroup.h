#ifndef BINDINGS_H
#define BINDINGS_H

#include <vector>
#include <webgpu/webgpu_cpp.h>


namespace some {
    class BindGroup {
    public:
        auto groupId(uint32_t groupId) -> BindGroup &;

        auto newEntry(uint32_t bindingId, const wgpu::Buffer &buffer,
                      uint32_t offset, uint64_t size) -> BindGroup &;

        auto bind(const wgpu::Device &device) -> BindGroup &;

        auto setVisibility(uint32_t bindingId,
                           wgpu::ShaderStage visibility) -> BindGroup &;

        auto setType(uint32_t bindingId,
                     wgpu::BufferBindingType type) -> BindGroup &;

        auto getLayout() -> wgpu::BindGroupLayout & {
            return this->layout;
        }

        auto label(const std::string &label) -> BindGroup &;

        auto get() -> wgpu::BindGroup & {
            return this->bindGroup;
        }

    private:
        uint32_t groupId_ = 0;
        std::vector<wgpu::BindGroupEntry> entries;
        std::vector<wgpu::BindGroupLayoutEntry> entryLayouts;
        wgpu::BindGroupLayout layout;
        wgpu::BindGroup bindGroup;
        std::string label_ = "Unnamed BindGroup";
    };
}


#endif //BINDINGS_H
