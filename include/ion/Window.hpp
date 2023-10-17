#pragma once

namespace ion
{
	class WindowManager;

	class Window
	{
	private:
		static const char* WINDOW_PTR;
		static const char* WINDOW_MANAGER_PTR;
	
	public:
		static Window& windowFromHwnd(HWND hwnd);
		static WindowManager& windowManagerFromHwnd(HWND hwnd);

		struct Config
		{
			bool maximized = false;
			bool minimized = false;
			std::size_t width = 640;
			std::size_t height = 480;
		};

		Window(WindowManager& manager, std::string_view title);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		~Window();

		void show();
		bool close();
		void maximize();
		void minimize();
		void restore();

		inline std::string_view title() const { return title_; }

	private:
		WindowManager& manager_;
		HWND hWnd_;
		std::string title_;
	};
}
