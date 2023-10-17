#include "ion/Window.hpp"
#include "ion/WindowManager.hpp"
#include "ion/Logger.hpp"

namespace ion
{
	const char* Window::WINDOW_PTR = "window-ptr";
	const char* Window::WINDOW_MANAGER_PTR = "window-manager-ptr";
	
	Window& Window::windowFromHwnd(HWND hwnd)
	{
		assert(hwnd != nullptr);
		return *static_cast<Window*>(GetPropA(hwnd, Window::WINDOW_PTR));
	}
	
	WindowManager& Window::windowManagerFromHwnd(HWND hwnd)
	{
		assert(hwnd != nullptr);
		return *static_cast<WindowManager*>(GetPropA(hwnd, Window::WINDOW_MANAGER_PTR));
	}

	Window::Window(WindowManager& manager, std::string_view title) :
		manager_(manager),
		hWnd_(nullptr),
		title_(title)
	{	
		HWND hwnd = CreateWindowEx(
			0,
			WindowManager::CLASS_NAME,
			L"Learn to Program Windows",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL,
			NULL,
			GetModuleHandle(NULL),
			NULL
		);

		if (hwnd == NULL)
			throw std::runtime_error("Could not create window!");

		SetPropA(hwnd, Window::WINDOW_PTR, static_cast<void*>(this));
		SetPropA(hwnd, Window::WINDOW_MANAGER_PTR, static_cast<void*>(std::addressof(manager)));

		hWnd_ = hwnd;

		ShowWindow(hWnd_, SW_NORMAL);
	}

	Window::~Window() {}

	void Window::show() {}
	
	bool Window::close() 
	{
		return DestroyWindow(hWnd_);
	}

	void Window::maximize() {}
	void Window::minimize() {}
	void Window::restore() {}
}
