#pragma once
#include <Siv3D.hpp>
#include "Debug.hpp"
#include "LeaderBoard.hpp"

struct Config {
	FilePath path;

	JSON data;

	String title = U"Title";
	String version = U"1.0.0";

	bool initFullscreen = false;
	bool allowFullscreen = false;

	Size windowSize{ 1280, 720 };

	String username = U"";

	Config() = default;
	Config(FilePath filepath) {
		init(filepath);
	}

	void init(FilePath _path) {
		path = _path;
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

			username = data[U"username"].getString();
			if (username.isEmpty()) {
				username = LeaderBoard::MakeRandomUserName();

				saveUsername();
			}

		}
		catch (Error err) {
			Debug << err.what();
		}
	}

	void saveUsername() {
		data[U"username"] = username;
		data.save(path);
	}

	void apply() {
		Window::SetTitle(title + U" - v" + version);

		Window::SetFullscreen(initFullscreen);
		Window::SetToggleFullscreenEnabled(allowFullscreen);

		Window::Resize(windowSize);
		Scene::SetResizeMode(ResizeMode::Keep);
	}
};
