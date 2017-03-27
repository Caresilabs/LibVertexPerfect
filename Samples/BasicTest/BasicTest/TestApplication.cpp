#include "DXApplication.h"
#include "MyTestGame.h"

static DXApplication* app;

int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow ) {
	app = new DXApplication();

	DXApplicationConfig config;
	config.hInstance = hInstance;
	config.hPrevInstance = hPrevInstance;
	config.lpCmdLine = lpCmdLine;
	config.nCmdShow = nCmdShow;

	config.className = "Assignment2";
	config.title = "LVP Tech-Demo #DevMode";
	config.width = 1280;
	config.height = 720;
	config.app = new MyTestGame();

	int code = app->Play( config );

	delete app;
	return code;
}