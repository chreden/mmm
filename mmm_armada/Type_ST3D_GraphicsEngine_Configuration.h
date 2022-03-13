#pragma once

namespace mmm
{
	namespace types
	{
		struct ST3D_GraphicsEngine_Configuration
		{
			bool m_use_second_display;
			bool m_fullscreen;
			bool m_fullscreen_synchronous_cursor;
			bool m_windowed_synchronous_cursor;
			bool m_reopen;
			bool m_disable_bump;
			bool m_disable_hwtnl;
			float m_geometry_detail;
			float m_background_brightness;
			int m_gamma_correction;
			int m_effects_detail;
			int m_background_detail;
			const class ST3D_DisplayDevice* m_display_device[0x2];
			const class ST3D_DisplayMode* m_display_mode[0x2];
			enum ST3D_DeviceType m_platform;
			float m_lod_distances[0x4];
			int m_graphics_detail_level;
		};
	}
}