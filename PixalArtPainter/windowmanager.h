#pragma once
#include <ewindow.h>
#include <guielements.h>

using namespace Evie;

namespace PixalArt {
	/*
		Summary:
			The initialization window,
			load resources, initialize components, after done,
			It will close automatically.
	*/
	class initwindow : public ewindow {
	public:
		/*
			Summary:
				600x200 At the center of the monitor.
		*/
		initwindow();
		/*
			Summary:
				...
		*/
		void start() override;
		/*
			Summary:
				...
		*/
		void register_events() override;
		/*
			Summary:
				Main loading processing.
		*/
		void update() override;
		/*
			Summary:
				Display loading bar, logo, loading message...
		*/
		void gui() override;

	private:
		/*
			Summary:
				Default glfw window config
		*/
		static ewindowconfig getconfig();
	};

	/*
		Summary:
			Main editor window, User workspace.
			In order to create this window, you must run through initwindow,
			to finishing the initialization first. otherwise it will throw an error.
	*/
	class editorwindow : public ewindow {
	public:
		editorwindow();
		~editorwindow();
		void start() override;
		void register_events() override;
		void update() override;
		void gui() override;
	private:
		/*
			Summary:
				Default glfw window config
		*/
		static ewindowconfig getconfig();

		bool canvas = true;
		bool properties = true;
		bool timeline = true;
		bool brush = true;
		bool fileexplorer = false;

	};
}

