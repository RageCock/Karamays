#include "gl_uniform_buffer.h"
#include "graphics/program/gl_program.h"

std::unordered_map<std::string, std::int64_t> gl_uniform_buffer::_glsl_type_size_map = {
        {"float", sizeof(glsl_float)},
        {"vec2", sizeof(glsl_vec2)},
        {"vec3", sizeof(glsl_vec3)},
        {"vec4", sizeof(glsl_vec4)},
        {"double", sizeof(glsl_double)},
        {"dvec2", sizeof(glsl_dvec2)},
        {"dvec3", sizeof(glsl_dvec3)},
        {"dvec4", sizeof(glsl_dvec4)},

        {"int", sizeof(glsl_int)},
        {"ivec2", sizeof(glsl_ivec2)},
        {"ivec3", sizeof(glsl_ivec3)},
        {"ivec4", sizeof(glsl_ivec4)},
        {"uint", sizeof(glsl_uint)},
        {"uvec2", sizeof(glsl_uvec2)},
        {"uvec3", sizeof(glsl_uvec3)},
        {"uvec4", sizeof(glsl_uvec4)},

        {"mat2", sizeof(glsl_mat2)},
        {"mat2x3", sizeof(glsl_mat2x3)},
        {"mat2x4", sizeof(glsl_mat2x4)},
        {"mat3", sizeof(glsl_mat3)},
        {"mat3x2", sizeof(glsl_mat3x2)},
        {"mat3x4", sizeof(glsl_mat3x4)},
        {"mat4", sizeof(glsl_mat4)},
        {"mat4x2", sizeof(glsl_mat4x2)},
        {"mat4x3", sizeof(glsl_mat4x3)},

        {"dmat2", sizeof(glsl_dmat2)},
        {"dmat2x3", sizeof(glsl_dmat2x3)},
        {"dmat2x4", sizeof(glsl_dmat2x4)},
        {"dmat3", sizeof(glsl_dmat3)},
        {"dmat3x2", sizeof(glsl_dmat3x2)},
        {"dmat3x4", sizeof(glsl_dmat3x4)},
        {"dmat4", sizeof(glsl_dmat4)},
        {"dmat4x2", sizeof(glsl_dmat4x2)},
        {"dmat4x3", sizeof(glsl_dmat4x3)}
};


