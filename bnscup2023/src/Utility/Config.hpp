#pragma once
#include <Siv3D.hpp>
#include "Debug.hpp"

struct Config {
	JSON data;

	String title = U"Title";
	String version = U"1.0.0";

	bool initFullscreen = false;
	bool allowFullscreen = false;

	Size windowSize{ 1280, 720 };

	Config() = default;
	Config(FilePath path) {
		init(path);
	}

	void init(FilePath path) {
		try {
			data = JSON::Load(path);

			title = data[U"title"].getString();
			version = data[U"version"].getString();

			initFullscreen = data[U"fullscreen"][U"init"].get<bool>();
			allowFullscreen = data[U"fullscreen"][U"allow"].get<bool>();

			windowSize = Size{
				data[U"ui"][U"window_size"][U"x"].get<int>(),
				data[U"ui"][U"window_size"][U"y"].get<int>()
			};
		}
		catch (Error err) {
			Debug << err.what();
		}
	}

	void apply() {
		Window::SetTitle(title + U" - v" + version);

		Window::SetFullscreen(initFullscreen);
		Window::SetToggleFullscreenEnabled(allowFullscreen);

		Window::Resize(windowSize);
		Scene::SetResizeMode(ResizeMode::Keep);
	}
};
