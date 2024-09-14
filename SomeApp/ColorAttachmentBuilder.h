#ifndef COLORATTACHMENTBUILDER_H
#define COLORATTACHMENTBUILDER_H

#include <webgpu/webgpu_cpp.h>

namespace some {
    class ColorAttachmentBuilder {
    public:

        // explicit ColorAttachmentBuilder();

        auto view(wgpu::TextureView view) -> ColorAttachmentBuilder&;
        auto build() -> wgpu::RenderPassColorAttachment;

    private:
        wgpu::LoadOp loadOp = wgpu::LoadOp::Clear;
        wgpu::StoreOp storeOp = wgpu::StoreOp::Store;
        wgpu::Color clearValue = {};
        wgpu::TextureView view_ = nullptr;
    };
}
#endif //COLORATTACHMENTBUILDER_H
