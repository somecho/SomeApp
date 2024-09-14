#ifndef BUFFERBUILDER_H
#define BUFFERBUILDER_H

#include <webgpu/webgpu_cpp.h>
#include <glm/mat4x4.hpp>

#include "log.h"

namespace some {
    template<typename T, wgpu::BufferUsage U = wgpu::BufferUsage::CopyDst>
    class BufferBuilder {
    public:
        BufferBuilder() {
            desc.usage = U;
            desc.label = "No Label";
        }

        auto data(std::vector<T> data) -> BufferBuilder & {
            m_data = data;
            desc.size = data.size() * sizeof(T);
            return *this;
        }

        auto data(glm::mat4 data) -> BufferBuilder & {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    m_data.push_back(data[i][j]);
                }
            }
            desc.size = 16 * sizeof(T);
            return *this;
        }

        auto addUsage(const wgpu::BufferUsage usage) -> BufferBuilder & {
            desc.usage = desc.usage | usage;
            return *this;
        }

        auto usage(const wgpu::BufferUsage usage) -> BufferBuilder & {
            desc.usage = usage;
            return *this;
        }

        auto mappedAtCreation(const bool mappedAtCreation) -> BufferBuilder & {
            desc.mappedAtCreation = mappedAtCreation;
            return *this;
        }

        auto offset(const uint64_t offset) -> BufferBuilder & {
            m_offset = offset;
            return *this;
        }

        auto label(const char *label) -> BufferBuilder & {
            desc.label = label;
            return *this;
        }

        [[nodiscard]]
        auto build(const wgpu::Device &device) -> wgpu::Buffer {
            wgpu::Buffer buf = device.CreateBuffer(&desc);
            device.GetQueue().WriteBuffer(buf, m_offset, m_data.data(),
                                          desc.size);
            log(std::format(
                "Buffer created - Label: {}, Size: {}, NumItems: {}",
                this->desc.label, buf.GetSize(), m_data.size()));
            return buf;
        }

    private:
        wgpu::BufferDescriptor desc;
        std::vector<T> m_data;
        uint64_t m_offset = 0;
    };
}
#endif //BUFFERBUILDER_H
