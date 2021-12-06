#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

	IMPLEMENTATION_FUNC_BUILD()
    {
		// life time are managed by BUILDER 
		auto _albedo_map = BUILDER.create_texture_2d("albedo_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_albedo_map->build_mipmaps();
		auto _normal_map = BUILDER.create_texture_2d("normal_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_normal_map->build_mipmaps();
		auto _metalness_map = BUILDER.create_texture_2d("metalness_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_metalness_map->build_mipmaps();
		auto _roughness_map = BUILDER.create_texture_2d("roughness_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);    
		_roughness_map->build_mipmaps();
		auto _displacement_map = BUILDER.create_texture_2d("displacement_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_displacement_map->build_mipmaps();
		auto _ambient_occlusion_map = BUILDER.create_texture_2d("ambient_occlusion_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_ambient_occlusion_map->build_mipmaps();

		// construct pipeline
		//  : graphics program parameters
		//  : vertex launcher
		//  : default framebuffer
		glsl_vertex_shader* _vs = new glsl_vertex_shader({});
		glsl_tessellation_shader* _ts = new glsl_tessellation_shader({});
		glsl_geometry_shader* _gs = new glsl_geometry_shader({});
		glsl_fragment_shader* _fs = new glsl_fragment_shader({});
		auto _mesh_pipeline = BUILDER.create_graphics_pipeline("mesh_pipeline", _vs, _ts, _gs, _fs);
		
		// fill vertex stream
		_mesh_pipeline->vertex_launcher().reallocate_element_slot(10);
		_mesh_pipeline->vertex_launcher().reallocate_vertex_slot(16);


		// fill program parameters
		/*_mesh_pipeline->program().sampler2D("mat.albedo_map")->set_texture_2d(_albedo_map);
		_mesh_pipeline->program().sampler2D("mat.normal_map")->set_texture_2d(_normal_map);
		_mesh_pipeline->program().sampler2D("mat.metalness_map")->set_texture_2d(_metalness_map);
		_mesh_pipeline->program().sampler2D("mat.roughness_map")->set_texture_2d(_roughness_map);
		_mesh_pipeline->program().sampler2D("mat.displacement_map")->set_texture_2d(_displacement_map);
		_mesh_pipeline->program().sampler2D("mat.ambient_occlusion_map")->set_texture_2d(_ambient_occlusion_map);*/

		// set render target as default framebuffer
		_mesh_pipeline->render_target().set_default();
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		auto _mesh_pipeline = BUILDER.graphics_pipeline("mesh_pipeline");
		if (!_mesh_pipeline) return;

		// refresh device
		DEVICE_FRAMEBUFFER->set_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		DEVICE_FRAMEBUFFER->set_read_buffer(gl_default_framebuffer_read_buffer::LEFT);
		DEVICE_FRAMEBUFFER->set_depth_test(true);
		DEVICE_FRAMEBUFFER->set_stencil_test(true);
		DEVICE_FRAMEBUFFER->clear_color_buffer(0.5f, 0.9f, 0.8f, 1.0f);
		DEVICE_FRAMEBUFFER->clear_depth_buffer();
		DEVICE_FRAMEBUFFER->clear_stencil_buffer();

		// vertex processing pass
		_mesh_pipeline->enable();
		_mesh_pipeline->draw_arrays(0, 1024);
		_mesh_pipeline->disable();
	}

DEFINE_RENDERER_END

#endif