#include "ion/WindowManager.hpp"
#include "ion/Engine.hpp"

namespace ion
{
	const wchar_t* WindowManager::CLASS_NAME = L"Ion Window";

	LRESULT CALLBACK WindowManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		auto& window = Window::windowFromHwnd(hwnd);
		auto& manager = Window::windowManagerFromHwnd(hwnd);

		switch (uMsg)
		{
		case WM_CLOSE:
			manager.closeWindow(window);
			return 0;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void WindowManager::onInitialize(const Config& config)
	{
		ZeroMemory(&wc_, sizeof(WNDCLASS));

		wc_.lpfnWndProc = WindowProc;
		wc_.hInstance = GetModuleHandle(NULL);
		wc_.lpszClassName = CLASS_NAME;

		RegisterClass(&wc_);
	}

	void WindowManager::onTerminate()
	{
		UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
	}

	Window& WindowManager::create(std::string_view title)
	{
		Window* win = new Window(*this, title);

		const WindowEvent event = {
			.window = *win
		};

		events().emit(WindowManager::Events::CREATE, event);

		windows_.emplace_back(win);

		return *win;
	}

	void WindowManager::run()
	{
		MSG msg = { };

		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowManager::closeWindow(Window& window)
	{
		window.close();

		Window* ptr = std::addressof(window);

		auto it = std::find(windows_.begin(), windows_.end(), ptr);

		if (std::find(windows_.begin(), windows_.end(), ptr) != windows_.end())
			windows_.erase(std::remove(windows_.begin(), windows_.end(), ptr), windows_.end());
	
		delete ptr;
		
		Logger::get().debug("Closed window");

		if(windows_.size() == 0)
			PostQuitMessage(0);
	}
}
