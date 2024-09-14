#include "ColorAttachmentBuilder.h"

#include <utility>

auto some::ColorAttachmentBuilder::view(
    wgpu::TextureView view) -> ColorAttachmentBuilder & {
    view_ = std::move(view);
    return *this;
}

auto some::ColorAttachmentBuilder::build() -> wgpu::RenderPassColorAttachment {
    return wgpu::RenderPassColorAttachment{
        .view = std::move(view_),
        .loadOp = loadOp,
        .storeOp = storeOp,
        .clearValue = clearValue
    };
}
