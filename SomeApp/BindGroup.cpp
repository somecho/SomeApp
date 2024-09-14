#include "BindGroup.h"

#include "log.h"

auto some::BindGroup::groupId(
    const uint32_t groupId) -> BindGroup & {
    this->groupId_ = groupId;
    return *this;
}

auto some::BindGroup::newEntry(const uint32_t bindingId,
                               const wgpu::Buffer &buffer,
                               const uint32_t offset,
                               const uint64_t size)
    -> BindGroup & {
    this->entries.push_back({
        .binding = bindingId,
        .buffer = buffer,
        .offset = offset,
        .size = size
    });
    this->entryLayouts.push_back({
        .binding = bindingId,
        .visibility = wgpu::ShaderStage::Vertex | wgpu::ShaderStage::Fragment,
        .buffer = {.type = wgpu::BufferBindingType::Uniform}
    });
    return *this;
}

auto some::BindGroup::bind(
    const wgpu::Device &device) -> BindGroup & {
    wgpu::BindGroupLayoutDescriptor layoutDesc{
        .entryCount = this->entryLayouts.size(),
        .entries = this->entryLayouts.data(),
    };
    this->layout = device.CreateBindGroupLayout(&layoutDesc);
    const wgpu::BindGroupDescriptor groupDesc{
        .label = this->label_.c_str(),
        .layout = this->layout,
        .entryCount = this->entries.size(),
        .entries = this->entries.data()
    };
    this->bindGroup = device.CreateBindGroup(&groupDesc);
    log(std::format("Created BindGroup \"{}\" with {} entries",
                    this->label_, this->entries.size()));
    return *this;
}

auto some::BindGroup::setVisibility(const uint32_t bindingId,
                                    const wgpu::ShaderStage visibility)
    -> BindGroup & {
    this->entryLayouts[bindingId].visibility = visibility;
    return *this;
}

auto some::BindGroup::setType(const uint32_t bindingId,
                              const wgpu::BufferBindingType type)
    -> BindGroup & {
    this->entryLayouts[bindingId].buffer.type = type;
    return *this;
}

auto some::BindGroup::label(const std::string &label)
    -> BindGroup & {
    this->label_ = label;
    return *this;
}
