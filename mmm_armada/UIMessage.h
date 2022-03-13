#pragma once

namespace mmm
{
	enum eMessageType
	{
		MessageType_UI = 0,
		MessageType_Title,
		MessageType_Subtitle
	};

	struct UIMessage
	{
		int			 id;
		eMessageType type;
		bool		 fade;
		float		 startTime;
		float		 displayTime;
	};
}
