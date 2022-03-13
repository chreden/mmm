#pragma once

namespace mmm
{
	namespace types
	{
		struct ST3D_Database
		{

		};

		struct ST3D_GraphicsEngine_Configuration;

		struct ST3D_GraphicsEngine
		{
			bool m_transforms_in_camera_space;
			char _padding[0x3];
			float m_sprite_colour_scaling_factor;
			char* m_app_name;
			void* m_default_lighting_material;
			void*  m_texture_material_default;
			void*  m_texture_material_additive;
			void*  m_texture_material_translucent;
			void*  m_texture_material_default_alpha;
			void*  m_texture_material_object_cloaked;
			void*  m_texture_material_wireframe;

			ST3D_Colour m_global_ambient;
			ST3D_Colour m_team_colour;

			bool m_team_colour_enabled;

			char _padding2[0x3];

			ST3D_Database* m_global_db;

			void* m_intelMRM;
			float m_polygon_budget_fps_modifier;
			char m_debug_lines[0xC]; //list<ST3D_DebugLine*>
			char m_active_lights[0xC]; //list<ST3D_LightInstances*>
			char m_global_particle_list[0xC]; //list<ST3D_Particle*>
			char m_database_list[0xC]; //list<ST3D_Database*>

			float m_totalFrameRate;
			float m_totalElapsedTime;
			float m_average_frame_rate;
			float m_time_this_frame;
			float m_time_last_frame;


			int m_cull_override; //st3d_culltype

			unsigned long m_frame_count;
			unsigned long m_totalFrameCount;
			float m_time_at_start_of_sampling_period_in_seconds;
			unsigned long m_num_triangles_drawn;
			const class ST3D_LightingMaterial* m_lighting_material;
			int m_global_lod_selection_override;
			unsigned char m_global_scaling_enabled;
			Vector3 m_global_scale_factor;
			
			int m_current_device_index;
			unsigned char m_storm3d_is_active;
			long m_user_data;
			class ST3D_Device * m_device[0x2];
			void* error_fn;	//function
			void* warning_fn;//function
			void* log_fn;//function
			unsigned long m_highest_mip_level;
			unsigned long m_global_texture_flags;
			int m_near_fade_out;
			unsigned char m_convert_to_mrm;
			float m_preference_geometry_detail;
			unsigned char m_armada_1_compatibility;
			class ST3D_MeshRenderCallback* m_meshRenderCallback;
			class ST3D_Camera* m_camera;
			class ST3D_Instance* m_current_instance;
			ST3D_GraphicsEngine_Configuration* m_gfx_config;
		};

		ST3D_GraphicsEngine* getGraphicsEngine();
	}
}