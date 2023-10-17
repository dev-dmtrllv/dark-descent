#pragma once

#include "pch.hpp"

namespace ion
{
	struct DebugConsole
	{
		DebugConsole();
		~DebugConsole();

	private:
		FILE* stdInFile_ = nullptr;
		FILE* stdOutFile_ = nullptr;
		FILE* stdErrFile_ = nullptr;
	};
}
