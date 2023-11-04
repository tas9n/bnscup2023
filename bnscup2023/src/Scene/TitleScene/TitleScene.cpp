#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init) : IScene(init) {
	m_titleName = getData().config.title;

	m_gameStartButton = Rect{ Arg::center(getData().config.windowSize / 2 + Point{ 0, 64 }), getData().config.windowSize.x - 240, 90 };
	m_highscoreButton = Rect{ Arg::center(getData().config.windowSize / 2 + Point{ 0, 154 }), getData().config.windowSize.x - 240, 90 };
}

void TitleScene::update() {
	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(RandomVec2(getData().config.windowSize.x, getData().config.windowSize.y));
	}

	if (m_gameStartButton.leftClicked()) {
		changeScene(SceneState::Game);
	}
	if (m_highscoreButton.leftClicked()) {
		changeScene(SceneState::Score);
	}
}

void TitleScene::draw() const {
	Vec2 center = Scene::CenterF();

	m_effect.update();

	FontAsset(U"UI.Title")(m_titleName)
		.drawAt(TextStyle::Outline(.0, .5, Palette::White), center.movedBy(.0, -64.0), theme.background);

	m_gameStartButton.draw(m_gameStartButton.mouseOver() ? theme.background : Palette::White);
	m_gameStartButton.drawFrame(4.0, Palette::White);

	FontAsset(U"UI.Normal")(U"ゲームスタート")
		.drawAt(TextStyle::Outline(.0, .1, Palette::White), center.movedBy(.0, 64.0), theme.background);

	m_highscoreButton.draw(m_highscoreButton.mouseOver() ? theme.background : Palette::White);
	m_highscoreButton.drawFrame(4.0, Palette::White);

	FontAsset(U"UI.Normal")(U"ハイスコア")
		.drawAt(TextStyle::Outline(.0, .1, Palette::White), center.movedBy(.0, 154.0), theme.background);
}

void TitleScene::updateFadeIn(double) {

	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(RandomVec2(getData().config.windowSize.x, getData().config.windowSize.y));
	}
}
