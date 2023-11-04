#include <Siv3D.hpp> // Siv3D v0.6.12
#include "Utility/Config.hpp"
#include "Utility/Theme.hpp"

#include "Utility/WindowRecorder.hpp"

#include "Scene/Common.hpp"
#include "Scene/TitleScene/TitleScene.hpp"
#include "Scene/GameScene/GameScene.hpp"
#include "Scene/ScoreScene/ScoreScene.hpp"

void Main() {
	Config config{ U"space_collector.config.json" };

	config.apply();

	Scene::SetBackground(theme.background);

	auto fontPath = Resource(U"resource/font/makinas4/Makinas-4-Square.otf");

	FontAsset::Register(U"UI.Title", FontMethod::SDF, 90, fontPath);
	FontAsset::Register(U"UI.Normal", FontMethod::SDF, 48, fontPath);
	FontAsset::Register(U"UI.Small", FontMethod::SDF, 24, fontPath);

	AudioAsset::Register(U"Global.BGM", Resource(U"resource/sounds/bgm.mp3"), Loop::Yes);
	AudioAsset::Register(U"Game.PickupItem", Resource(U"resource/sounds/pickup-item.mp3"));
	AudioAsset::Register(U"Game.Hit.Blackhole", Resource(U"resource/sounds/hit-blackhole.mp3"));
	AudioAsset::Register(U"Game.Player.Damaged", Resource(U"resource/sounds/player.damaged.mp3"));
	AudioAsset::Register(U"Game.Levelup", Resource(U"resource/sounds/levelup.mp3"));

	// シーンのあれこれ
	App manager;
	manager
		.add<TitleScene>(SceneState::Title)
		.add<GameScene>(SceneState::Game)
		.add<ScoreScene>(SceneState::Score);

	// manager.init(SceneState::Game);

	WindowRecorder recorder;
	bool recoderFlag = false;

	// ゲームループ(各シーンにupdate)
	while (System::Update()) {
		if (not manager.update()) break;

		if (KeyR.down()) {
			if(not recorder.isOpen())
				recorder.open(U"../../gameplay.mp4", config.windowSize, 60);
			recoderFlag = not recoderFlag;
		}

		if(recoderFlag)
			recorder.update();

		// デバッグ用
		if (KeyP.down()) {
			ScreenCapture::SaveCurrentFrame(U"../../../gameplay.png");
		}
	}
}
