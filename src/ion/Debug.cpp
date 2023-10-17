#include "ion/Debug.hpp"

namespace ion
{
	DebugConsole::DebugConsole() :
		stdInFile_(nullptr),
		stdOutFile_(nullptr),
		stdErrFile_(nullptr)
	{
#ifdef _DEBUG
		AllocConsole();

		freopen_s(&stdInFile_, "CONIN$", "r", stdin);
		freopen_s(&stdOutFile_, "CONOUT$", "w", stdout);
		freopen_s(&stdErrFile_, "CONOUT$", "w", stderr);
#endif
	}

	DebugConsole::~DebugConsole()
	{
#ifdef _DEBUG
		puts("Press a key to exit...");
		getchar();
		
		if (stdInFile_ != nullptr)
			fclose(stdInFile_);

		if (stdOutFile_ != nullptr)
			fclose(stdOutFile_);

		if (stdErrFile_ != nullptr)
			fclose(stdErrFile_);

		FreeConsole();
#endif
	}
}
