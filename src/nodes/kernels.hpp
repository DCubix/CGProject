#ifndef KERNELS_HPP
#define KERNELS_HPP

static const std::string K_COLOR = R"(
    __kernel void ColorNode(float4 color, __write_only image2d_t out) {
        const int2 uv = {get_global_id(0), get_global_id(1)};
        write_imagef(out, uv, color);
    }
)";

static const std::string K_IMAGE = R"(
    __constant sampler_t sampler =
          CLK_NORMALIZED_COORDS_TRUE
        | CLK_ADDRESS_CLAMP_TO_EDGE
        | CLK_FILTER_NEAREST;

    __kernel void ImageNode(__read_only image2d_t in, __write_only image2d_t out) {
        const float2 pos = (float2)((float) get_global_id(0), (float) get_global_id(1));
        const float2 sz = convert_float2(get_image_dim(out));
        const float2 uv = (float2)(pos.x / sz.x, pos.y / sz.y);
        write_imagef(out, pos, read_imagef(in, sampler, uv));
    }
)";

static const std::string K_MUL = R"(
    __constant sampler_t sampler =
          CLK_NORMALIZED_COORDS_TRUE
        | CLK_ADDRESS_CLAMP_TO_EDGE
        | CLK_FILTER_NEAREST;

    __kernel void ImageNode(__read_only image2d_t a, __read_only image2d_t b, __write_only image2d_t out) {
        const float2 pos = (float2)((float) get_global_id(0), (float) get_global_id(1));
        const float2 sz = convert_float2(get_image_dim(out));
        const float2 uv = (float2)(pos.x / sz.x, pos.y / sz.y);

        float4 mres = read_imagef(a, sampler, uv) * read_imagef(b, sampler, uv);
        write_imagef(out, pos, mres);
    }
)";

static const std::string K_ADD = R"(
    __constant sampler_t sampler =
          CLK_NORMALIZED_COORDS_TRUE
        | CLK_ADDRESS_CLAMP_TO_EDGE
        | CLK_FILTER_NEAREST;

    __kernel void ImageNode(__read_only image2d_t a, __read_only image2d_t b, __write_only image2d_t out) {
        const float2 pos = (float2)((float) get_global_id(0), (float) get_global_id(1));
        const float2 sz = convert_float2(get_image_dim(out));
        const float2 uv = (float2)(pos.x / sz.x, pos.y / sz.y);

        float4 mres = read_imagef(a, sampler, uv) + read_imagef(b, sampler, uv);
        write_imagef(out, pos, mres);
    }
)";

#endif // KERNELS_HPP