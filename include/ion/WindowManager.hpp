#pragma once

#include "ion/SubSystem.hpp"
#include "ion/Window.hpp"
#include "ion/Hash.hpp"

namespace ion
{
	struct WindowEvent
	{
		Window& window;
	};

	class WindowManager : public SubSystem<WindowManager, WindowEvent>
	{
	public:
		static const wchar_t* CLASS_NAME;
		
	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		struct Events
		{
			static const std::size_t CREATE = Hasher::hash("CREATE");
			static const std::size_t SHOW = Hasher::hash("SHOW");
			static const std::size_t CLOSE = Hasher::hash("CLOSE");
		};

		SUB_SYSTEM_CTORS(WindowManager, WindowEvent);

		virtual void onInitialize(const Config& config) override;
		virtual void onTerminate() override;

		void closeWindow(Window& window);

		void run();

		Window& create(std::string_view title);

	private:
		WNDCLASS wc_;
		std::vector<Window*> windows_;
	};
}
