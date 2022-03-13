#pragma once

namespace mmm
{
	namespace types
	{
		struct ST3D_DisplayMode
		{
			int m_width;
			int m_height;
			int m_bit_depth;
			enum ST3D_PixelFormat m_pf;
			unsigned char m_render3d;
		};
	}
}
