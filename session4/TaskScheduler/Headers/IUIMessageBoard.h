#pragma once

namespace BusinessRules
{

	class IUIMessageBoard
	{

	public:
		virtual ~IUIMessageBoard() = default;
		virtual void PushMessageToMessageBoard(const std::string& message) = 0;

	};

}