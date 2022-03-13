#ifndef _MMM_MMM_TYPE_ST3D_ANIMATIONCHANNEL_H_INCLUDED
#define _MMM_MMM_TYPE_ST3D_ANIMATIONCHANNEL_H_INCLUDED

#ifndef _MMM_ARMADA_VECTORADAPTER_H_INCLUDED
	#include "VectorAdapter.h"
#endif

namespace mmm
{
	namespace types
	{
		struct ST3D_AnimationChannel
		{
			char _padding_[0x18];
			  /*<thisrel this+0x18>*/ /*|0x1|*/ unsigned char m_class;
			  /*<thisrel this+0x1c>*/ /*|0x10|*/ VectorAdapter<float> m_keyframe_times; //class std::vector<float,std::allocator<float> > m_keyframe_times;
			  /*<thisrel this+0x2c>*/ /*|0x4|*/ float m_duration;
			  /*<thisrel this+0x30>*/ /*|0x4|*/ int m_current_keyframe;
			  /*<thisrel this+0x34>*/ /*|0x4|*/ int m_nkeyframes;
			  /*<thisrel this+0x38>*/ /*|0x4|*/ float m_playback_offset;
			  /*<thisrel this+0x3c>*/ /*|0x4|*/ void* m_destination_object;
			  /*<thisrel this+0x40>*/ /*|0x4|*/ unsigned long m_destination_offset;
		};

		template<typename T>
		struct AnimationChannel : public ST3D_AnimationChannel  
		{

			  // static data ------------------------------------

			  // non-static data --------------------------------
			  /*<thisrel this+0x44>*/ /*|0x4|*/ enum ST3D_Interpolation m_interpolation;
			  /*<thisrel this+0x48>*/ /*|0x10|*/ VectorAdapter<T> m_keyframe_data; //class std::vector<Vector2,std::allocator<Vector2> > m_keyframe_data;
		};
	}
}


#endif