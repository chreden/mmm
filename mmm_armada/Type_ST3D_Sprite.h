#pragma once

#include "ListAdapter.h"

namespace mmm
{
	namespace types
	{
		struct ST3D_AnimationChannel;

		struct ST3D_Sprite 
		{
			char _padding_[0x18];
			ListAdapter<ST3D_AnimationChannel*> m_animation_channel_list;
		};
	}
}
