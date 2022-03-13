#pragma once

namespace mmm
{
	namespace types
	{
		struct ST3D_Device 
		{

			  // static data ------------------------------------
#if 0
			  // non-static data --------------------------------
			  /*<thisrel this+0x4>*/ /*|0x4|*/ float m_texel_offset;
			  /*<thisrel this+0x8>*/ /*|0x4|*/ class ST3D_ZSort_Manager* m_zsort;
			  /*<thisrel this+0xc>*/ /*|0x4|*/ int m_triangles_drawn;
			  /*<thisrel this+0x10>*/ /*|0x8|*/ class Vector2 m_cursor_texture_coordinate_offset;
			  /*<thisrel this+0x18>*/ /*|0x8|*/ class Vector2 m_cursor_scale_factor;
			  /*<thisrel this+0x20>*/ /*|0x4|*/ class ST3D_DisplayMode* m_display_mode;
			  /*<thisrel this+0x24>*/ /*|0x1|*/ unsigned char m_fullscreen;
			  /*<thisrel this+0x28>*/ /*|0x4|*/ class ST3D_Workspace* m_renderer_workspace;
			  /*<thisrel this+0x2c>*/ /*|0x4|*/ enum ST3D_DisplayType m_display_type;
			  /*<thisrel this+0x30>*/ /*|0x10|*/ class ST3D_Rect m_window_rect;
			  /*<thisrel this+0x40>*/ /*|0x10|*/ class ST3D_RenderState m_renderstate;
			  /*<thisrel this+0x50>*/ /*|0xc|*/ void  (*)(class ST3D_VertexLighting_Group*, class ST3D_Mesh*) m_vertex_lighting_function[3];
			  /*<thisrel this+0x5c>*/ /*|0x4|*/ int m_device_index;
#endif
			  char _padding_[0x60];
			  /*<thisrel this+0x60>*/ /*|0x4|*/ class ST3D_Sprite* m_cursor_sprite;
#if 0 
			  /*<thisrel this+0x64>*/ /*|0x4|*/ enum ST3D_PixelFormat m_texture_format_no_alpha;
			  /*<thisrel this+0x68>*/ /*|0x4|*/ enum ST3D_PixelFormat m_texture_format_alpha;
			  /*<thisrel this+0x6c>*/ /*|0x4|*/ enum ST3D_PixelFormat m_texture_format_chromakey;
			  /*<thisrel this+0x70>*/ /*|0x4|*/ enum ST3D_PixelFormat m_cursor_format;
			  /*<thisrel this+0x74>*/ /*|0x4|*/ enum ST3D_PixelFormat m_screen_pixel_format;
			  /*<thisrel this+0x78>*/ /*|0x4|*/ class ST3D_DisplayDevice* m_display_device;
			  /*<thisrel this+0x7c>*/ /*|0x10|*/ class ST3D_Rect m_offscreen_rect;
#endif
			};
	}
}
