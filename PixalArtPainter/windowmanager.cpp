#include "windowmanager.h"
#include <guielements.h>
#include <einput.h>
#include <shader.h>

/*
	[ Initialization Windiw ]
*/
#pragma region Initialization Window
UI::uiwindiwflags loginScreen() {
	UI::uiwindiwflags w = UI::uiwindiwflags();
	w.notitlebar = true;
	w.nocollapse = true;
	w.noresize = true;
	w.unsave = true;
	w.nomove = true;
	w.nobackground = true;
	return w;
}

PixalArt::initwindow::initwindow() : ewindow(600, 200, "Pxial Art Initialization", OpenGLVersion::Version4_5, getconfig()) {}

void PixalArt::initwindow::start() 
{
	ewindow::start();
}

void PixalArt::initwindow::register_events()
{
	ewindow::register_events();
}

void PixalArt::initwindow::update()
{
	ewindow::update();
	if (einput::time() > 2) close();
}

void PixalArt::initwindow::gui()
{
	UI::next_windowpos(0, 0);
	UI::next_windowsize(600, 200);
	UI::begin("YO", (bool*)0, loginScreen());
	UI::text("Initialization complete !");
	UI::progress(1, 580, 15, 0);
	UI::space();
	UI::text("Starting editor...");
	UI::end();
}

ewindowconfig PixalArt::initwindow::getconfig()
{
	ewindowconfig config = ewindowconfig();
	config.decorated = false;
	return config;
}
#pragma endregion

/*
	[ Editor Windiw ]
*/
#pragma region Editor Window
PixalArt::editorwindow::editorwindow() : ewindow(1280, 800, "Pxial Art Editor", OpenGLVersion::Version4_5, getconfig()) {}

PixalArt::editorwindow::~editorwindow()
{
}

void PixalArt::editorwindow::start()
{
	ewindow::start();
	guiwindows.push_back(new Evie::UIElement::debugwindow());
	shader *s = new shader();
	s->set_vertex_from_file("vert.glsl");
	s->set_fragment_from_file("frag.glsl");
	s->compile();
	delete s;
}

void PixalArt::editorwindow::register_events()
{
	ewindow::register_events();
}

void PixalArt::editorwindow::update()
{
	ewindow::update();
}

void PixalArt::editorwindow::gui()
{
	UI::dockspace_overviewport();
	ewindow::gui();
}

ewindowconfig PixalArt::editorwindow::getconfig()
{
	ewindowconfig config = ewindowconfig();
	config.minimum_size = new int[2]{ 800, 600 };
	return config;
}
#pragma endregion
