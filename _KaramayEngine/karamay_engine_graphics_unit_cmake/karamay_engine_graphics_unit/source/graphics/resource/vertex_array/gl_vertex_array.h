#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/resource/glo/gl_object.h"
#include "graphics/glsl/interface_block/glsl_in_block.h"
#include "graphics/resource/buffers/common_buffer/gl_array_buffer.h"

class gl_attribute_component
{
public:
    enum class type : GLenum
    {
        UNKNOWN = 0,
        INT = GL_INT,
        UINT = GL_UNSIGNED_INT,
        FLOAT = GL_FLOAT,
        DOUBLE = GL_DOUBLE
    };

    static std::string to_string(type component_type)
    {
        switch(component_type)
        {
            case type::INT: return "INT";
            case type::UINT: return "UINT";
            case type::FLOAT: return "FLOAT";
            case type::DOUBLE: return "DOUBLE";
            default: return "UNKNOWN";
        }
    }

    static type to_enum(const std::string& component_type)
    {
        if(component_type == "INT") return type::INT;
        if(component_type == "UINT") return type::UINT;
        if(component_type == "FLOAT") return type::FLOAT;
        if(component_type == "DOUBLE") return type::DOUBLE;
        return type::UNKNOWN;
    }

    static GLenum to_GLenum(type component_type)
    {
        return static_cast<GLenum>(component_type);
    }

    static std::uint32_t get_size(type component_type)
    {
        switch (component_type) {
            case type::INT: return sizeof(std::int32_t);
            case type::UINT: return sizeof(std::uint32_t);
            case type::FLOAT: return sizeof(std::float_t);
            case type::DOUBLE: return sizeof(std::double_t);
            default: return 0;
        }
    }
};

class gl_attribute
{
    enum class type
    {
        UINT,UVEC2,UVEC3,UVEC4,
        INT,IVEC2,IVEC3,IVEC4,
        FLOAT,VEC2,VEC3,VEC4,
        DOUBLE,DVEC2,DVEC3,DVEC4,

        MAT2X2,MAT2X3,MAT2X4,MAT3X2,MAT3X3,MAT3X4,MAT4X2,MAT4X3,MAT4X4,
        DMAT2X2,DMAT2X3,DMAT2X4,DMAT3X2,DMAT3X3,DMAT3X4,DMAT4X2,DMAT4X3,DMAT4X4,
    };

    static std::pair<gl_attribute_component::type, std::uint32_t> get_component_layout(gl_attribute::type attribute_type)
    {
        switch (attribute_type) {

            case type::UINT:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::UVEC2:
                return std::make_pair(gl_attribute_component::type::UINT, 2);
            case type::UVEC3:
                return std::make_pair(gl_attribute_component::type::UINT, 3);
            case type::UVEC4:
                return std::make_pair(gl_attribute_component::type::UINT, 4);
            case type::INT:
                return std::make_pair(gl_attribute_component::type::INT, 1);
            case type::IVEC2:
                return std::make_pair(gl_attribute_component::type::INT, 2);
            case type::IVEC3:
                return std::make_pair(gl_attribute_component::type::INT, 3);
            case type::IVEC4:
                return std::make_pair(gl_attribute_component::type::INT, 4);
            case type::FLOAT:
                return std::make_pair(gl_attribute_component::type::FLOAT, 1);
            case type::VEC2:
                return std::make_pair(gl_attribute_component::type::FLOAT, 2);
            case type::VEC3:
                return std::make_pair(gl_attribute_component::type::FLOAT, 3);
            case type::VEC4:
                return std::make_pair(gl_attribute_component::type::FLOAT, 4);
            case type::DOUBLE:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 1);
            case type::DVEC2:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 2);
            case type::DVEC3:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 3);
            case type::DVEC4:
                return std::make_pair(gl_attribute_component::type::DOUBLE, 4);
            case type::MAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::MAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT2X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT3X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X2:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X3:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
            case type::DMAT4X4:
                return std::make_pair(gl_attribute_component::type::UINT, 1);
        }
    }
};

enum class AttributeComponentType
{
    UINT,
    INT,
    FLOAT,
    UINT_TO_FLOAT,
    DOUBLE,
};

struct VertexAttributeDescriptor 
{
    UInt32 Index;
    std::string Name;
    UInt64 Size;
    UInt32 ComponentsNum;
    AttributeComponentType ComponentType;
};

struct VertexDescriptor
{
    std::vector<VertexAttributeDescriptor> AttributeDescriptors;
};

struct InstanceAttributeDescriptor
{
    UInt32 Index;
    std::string Name;
    UInt32 Size;
    UInt32 ComponentsNum;
    UInt32 ComponentType;
    UInt32 Divisor;
};

struct VertexArrayDescriptor
{
    UInt32 VerticesNum;
    VertexDescriptor VertexDesc;
    UInt32 InstancesNum;
    std::vector<InstanceAttributeDescriptor> InstanceAttributeDescs;
};

struct gl_attribute_list_anchor
{
    std::string attribute_name;
    std::uint32_t attributes_count;
    std::int64_t offset;
    std::int64_t size;
};


/*
 * Dynamic Storage : if required capacity is not enough,
 *
 *
 * [          ] [vertex0] [vertex1] [vertex2] [vertexN]
 * [attribute0] [       ] [       ] [      ] [.......]
 * [attribute1] [       ] [       ] [      ] [.......]
 * [attribute2] [       ] [       ] [      ] [.......]
 * [attributeN] [       ] [       ] [      ] [.......]
 *
 * Store Vertex Attributes & Instance Attributes
 *
 * */
class VertexArray final : public gl_object {
public:
    VertexArray() : gl_object(gl_object_type::VERTEX_ARRAY_OBJ) {}
    VertexArray(const VertexArrayDescriptor& Descriptor) : 
        gl_object(gl_object_type::VERTEX_ARRAY_OBJ)
    {
        glCreateVertexArrays(1, &_handle);
    }

    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    ~VertexArray() override
    {
        glDeleteVertexArrays(1, &_handle);
    }

private:

    VertexArrayDescriptor _Descriptor;

    ArrayBuffer _VertexBuffer;
    std::vector<ArrayBuffer> _InstanceAttributeBuffers;

    std::unordered_map<std::string, gl_attribute_list_anchor> _vertex_attribute_layout;
    std::unordered_map<std::string, gl_attribute_list_anchor> _instance_attribute_layout;

public:

    void ReallocateVertices(UInt32 VerticesNum)
    {
        if (VerticesNum == _Descriptor.VerticesNum) return;
        
        _Descriptor.VerticesNum = VerticesNum;

    }

    void FillVertices(UInt32 Offset, UInt8* Data, UInt32 VerticesNum)
    {

    }

public:

    void ResetInstancesNum(UInt32 InstancesNum) 
    {}

    void ReallocateInstanceAttributes(UInt32 InstanceAttributesNum, UInt32 Divisor) 
    {}

    void FillInstanceAttributes() 
    {}

public:

    UInt32 GetVerticesNum() const
    {
        return _Descriptor.VerticesNum;
    }

    UInt32 GetInstancesNum() const 
    {
        return _Descriptor.InstancesNum;
    }


    std::uint8_t* data(std::int64_t offset, std::int64_t size)
    {
        return nullptr;
    }

    template<typename GLSL_TRANSPARENT_T>
    const GLSL_TRANSPARENT_T* attribute(std::uint32_t index)
    {
        const auto* _data = reinterpret_cast<const GLSL_TRANSPARENT_T*>(
                data(index * sizeof(GLSL_TRANSPARENT_T), sizeof(GLSL_TRANSPARENT_T))
                );
        return _data;
    }

public:

    void Bind() const noexcept
    {
        glBindVertexArray(_handle);
    }

    void Unbind() const noexcept
    {
        glBindVertexArray(0);
    }

    void EnablePointers()
    {
        UInt32 _AttributesCategoriesNum = _Descriptor.VertexDesc.AttributeDescriptors.size() + _Descriptor.InstanceAttributeDescs.size();
        for (UInt32 _Index = 0; _Index < _AttributesCategoriesNum; ++_Index)
        {
            glEnableVertexAttribArray(_Index);
        }
    }

    void DisablePointers()
    {
        UInt32 _AttributesCategoriesNum = _Descriptor.VertexDesc.AttributeDescriptors.size() + _Descriptor.InstanceAttributeDescs.size();
        for (UInt32 _Index = 0; _Index < _AttributesCategoriesNum; ++_Index)
        {
            glEnableVertexAttribArray(_Index);
        }
    }

public:
    /*
    * @Param0 attribute_name
    * @Param1 attribute_index
    * @Parma2 attribute_value
    */
    void update_instance_attributes(const std::vector<std::tuple<std::string, std::int32_t, const glsl_transparent_t_meta*>>& list)
    {
        std::int64_t _mapped_memory_offset = 0;
        std::int64_t _mapped_memory_size = 0;
        //std::vector<std::pair<std::int64_t, const glsl_transparent_class*>> _baked_list;

        for(const auto& _item : list)
        {
            /*auto _it = _instance_attribute_layout.find(std::get<0>(_item));
            if(_it == _instance_attribute_layout.cend()) return;
            std::int64_t _instance_attribute_list_offset = _it->second.offset;
            std::int64_t _instance_attribute_offset = _instance_attribute_list_offset + std::get<1>(_item) * std::get<2>(_item)->clazz()->class_size;
            _baked_list.push_back(std::make_pair(_instance_attribute_offset, std::get<2>(_item)));*/
        }

        //if(_instance_attribute_buffer)
        //{
        //    // _instance_attribute_buffer->execute_mutable_memory_handler(_mapped_memory_offset, _mapped_memory_size, 
        //    // [&_baked_list](std::uint8_t* mapped_memory, std::int64_t size)
        //    // {
        //    //     for(const auto& _item : _baked_list)
        //    //     {
        //    //         std::memcpy(mapped_memory + _item.first, _item.second->stream(), _item.second->stream_size());
        //    //     }
        //    // });
        //}
    }

private:

    void _SetVertexPointers()
    {

    }

    void _SetInstanceAttributePointers()
    {

    }


    void _SetAttributePointer(UInt32 Index, UInt32 ComponentsNum, AttributeComponentType ComponentType, UInt32 AttributeSize, UInt32 Offset)
    {
        switch (ComponentType) 
        {
            case AttributeComponentType::INT:
            {
                glVertexAttribIPointer(Index, ComponentsNum, GL_INT, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::UINT:
            {
                glVertexAttribIPointer(Index, ComponentsNum, GL_UNSIGNED_INT, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::FLOAT:
            {
                glVertexAttribPointer(Index, ComponentsNum, GL_FLOAT, GL_FALSE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::UINT_TO_FLOAT:
            {
                glVertexAttribPointer(Index, ComponentsNum, GL_UNSIGNED_INT, GL_TRUE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            case AttributeComponentType::DOUBLE:
            {
                glVertexAttribLPointer(Index, ComponentsNum, GL_DOUBLE, AttributeSize, reinterpret_cast<const void*>(Offset));
            }
            break;
            default: break;
        }
    }

    void VertexArray::_generate_attribute_layout()
    {

        const auto& _vertex_attribute_descriptors = _descriptor.get_vertex_attribute_descriptors();
        const auto& _instance_attribute_descriptors = _descriptor.get_instance_attribute_descriptors();
        const auto _vertices_count = _descriptor.get_vertices_count();

        for (const auto& _vertex_attribute_descriptor : _vertex_attribute_descriptors)
        {
            const auto _vertex_attribute_size = _vertex_attribute_descriptor.get_component_count() * gl_attribute_component::get_size(_vertex_attribute_descriptor.get_component_type());
            _memory_demand += _vertex_attribute_size * _vertices_count;
        }

        for (const auto& _instance_attribute_descriptor : _instance_attribute_descriptors)
        {
            const auto _instance_attribute_size = _instance_attribute_descriptor.get_component_count() * gl_attribute_component::get_size(_instance_attribute_descriptor.get_component_type());
            _memory_demand += _instance_attribute_size * _instance_attribute_descriptor.get_count();
        }


        std::uint32_t _index = 0;
        std::uint32_t _offset = 0;

        for (const auto& _vad : _vertex_attribute_descriptors)
        {
            const gl_attribute_component::type _component_type = _vad.get_component_type();
            const auto _components_count = static_cast<GLint>(_vad.get_component_count());
            const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));

            _set_vertex_pointers(_component_type, _index, _components_count, _attribute_size, _offset);

            for (std::uint32_t _sub_index = 0; _sub_index < _vertices_count; ++_sub_index)
            {
                _memory_layouts_map.emplace(_vad.get_name() + std::to_string(_sub_index), std::make_pair(_offset, _attribute_size));
                _offset += _attribute_size;
            }

            ++_index;
        }

        for (const auto& _iad : _instance_attribute_descriptors) {
            const auto _component_type = _iad.get_component_type();
            const auto _components_count = static_cast<GLint>(_iad.get_component_count());
            const auto _attribute_size = _components_count * static_cast<GLint>(gl_attribute_component::get_size(_component_type));
            const auto _divisor = _iad.get_divisor();
            const auto _count = _iad.get_count();

            _set_vertex_pointers(_component_type, _index, _components_count, _attribute_size, _offset);
            glVertexAttribDivisor(_index, _divisor);

            for (std::uint32_t _sub_index = 0; _sub_index < _count; ++_sub_index)
            {
                _memory_layouts_map.emplace(_iad.get_name() + std::to_string(_sub_index), std::make_pair(_offset, _attribute_size));
                _offset += _attribute_size;
            }

            ++_index;
        }

        _unbind_buffer(); unbind();
    }

    bool is_pointer_enabled(std::uint32_t index)
    {
        Bind();
        GLint _is_enabled = GL_FALSE;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
        Unbind();
        return _is_enabled;
    }

    std::uint32_t get_attribute_components_num(std::uint32_t index)
    {
        Bind();
        GLint _num = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
        Unbind();
        return _num;
    }

    std::string get_attribute_component_type(std::uint32_t index)
    {
        Bind();
        GLint _num = 0;
        glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &_num);
        Unbind();

        switch (_num)
        {
        case GL_BYTE: return "BYTE";
        case GL_UNSIGNED_BYTE: return "UNSIGNED BYTE";
        case GL_SHORT: return "SHORT";
        case GL_UNSIGNED_SHORT: return "UNSIGNED SHORT";
        case GL_INT: return "INT";
        case GL_UNSIGNED_INT: return "UNSIGNED INT";
        case GL_FLOAT: return "FLOAT";
        case GL_DOUBLE: return "DOUBLE";
        default: return "";
        }
    }

};

#endif
