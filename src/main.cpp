#include "pch.hpp"
#include "ion/Engine.hpp"
#include "ion/Maybe.hpp"
#include "ion/Debug.hpp"
#include "game/DarkDescent.hpp"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	return ion::Engine::run<DarkDescent>();
}
