#include <Siv3D.hpp> // Siv3D v0.6.12
#include "Utility/Config.hpp"
#include "Utility/Theme.hpp"

#include "Scene/Common.hpp"
#include "Scene/TitleScene/TitleScene.hpp"
#include "Scene/GameScene/GameScene.hpp"

void Main() {
	Config config{ U"resource/config.json" };

	config.apply();

	Scene::SetBackground(theme.background);

	FontAsset::Register(U"UI.Normal", 48);

	// シーンのあれこれ
	App manager;
	manager
		.add<TitleScene>(SceneState::Title)
		.add<GameScene>(SceneState::Game);

	manager.init(SceneState::Game);

	// lightblooom用
	const RenderTexture gaussianA1{ config.windowSize }, gaussianB1{ config.windowSize };
	const RenderTexture gaussianA4{ config.windowSize / 4 }, gaussianB4{ config.windowSize / 4 };

	// ゲームループ(各シーンにupdate)
	while (System::Update()) {
		if (not manager.update()) break;

		// デバッグ用
		if (KeyP.down()) {
			ScreenCapture::SaveCurrentFrame(U"../../../gameplay.png");
		}
	}
}
