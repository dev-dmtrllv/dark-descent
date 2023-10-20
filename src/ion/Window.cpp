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

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC ourWindowHandleToDeviceContext = GetDC(hWnd_);

		int  letWindowsChooseThisPixelFormat;
		letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
		SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

		HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
		wglMakeCurrent(ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

		MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

		//wglMakeCurrent(ourWindowHandleToDeviceContext, NULL); Unnecessary; wglDeleteContext will make the context not current
		wglDeleteContext(ourOpenGLRenderingContext);

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
