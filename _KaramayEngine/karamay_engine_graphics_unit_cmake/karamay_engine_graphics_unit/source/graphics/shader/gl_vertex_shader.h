
#include "gl_shader.h"
#include "graphics/glsl/glsl_class.h"

struct gl_vertex_shader_descriptor
{
	std::shared_ptr<gl_shader_parameters> parameters;
};

class gl_vertex_shader : public gl_shader
{
public:

	gl_vertex_shader() = delete;
	gl_vertex_shader(const gl_vertex_shader_descriptor& descriptor) :
		descriptor(descriptor)
	{}

public:

	const std::string& get_shader_glsl_template() const override
	{
		return _glsl_template;
	}

public:

	const gl_vertex_shader_descriptor descriptor;

private:

	std::string _glsl_template;

	void _generate_glsl_template()
	{
		std::string _fixed_template = 
		"#version 460 core\n"
		"_parameters_"
		"void main(void)\n "
		"{\n"
		"}\n";


		std::string _parameters_template = "";
		for (const auto& _image : _parameters.images)
		{
			if(_image) _parameters_template += _image->generate_token() + "\n";
		}
		for (const auto& _sampler : _parameters.samplers)
		{
			if (_sampler) _parameters_template += _sampler->generate_token() + "\n";
		}
		for (const auto& _atomic_counter : _parameters.samplers)
		{
			if (_atomic_counter) _parameters_template += _atomic_counter->generate_token() + "\n";
		}
		for (const auto& _uniform_block : _parameters.uniform_blocks)
		{
			if (_uniform_block) _parameters_template += _uniform_block->generate_token() + "\n";
		}
		for (const auto& _shader_storage_block : _parameters.shader_storage_blocks)
		{
			if (_shader_storage_block) _parameters_template += _shader_storage_block->generate_token() + "\n";
		}
		
		auto _index = _fixed_template.find_first_of("_parameters_");
		_fixed_template.insert(_index, _parameters_template);
		_fixed_template.erase(_fixed_template.find_first_of("_parameters_"), 12);

	}

};