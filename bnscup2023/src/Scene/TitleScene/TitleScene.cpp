#include "TitleScene.hpp"

TitleScene::TitleScene(const InitData& init) : IScene(init) {
	m_titleName = getData().config.title;

	m_gameStartButton = Rect{ Arg::center(getData().config.windowSize / 2 + Point{ 0, 64 }), getData().config.windowSize.x - 240, 90 };
	m_highscoreButton = Rect{ Arg::center(getData().config.windowSize / 2 + Point{ 0, 154 }), getData().config.windowSize.x - 240, 90 };
	m_usernameField = Rect{ Arg::center(getData().config.windowSize / 2 + Point{ 0, 244 }), getData().config.windowSize.x - 400, 64 };
	m_usernameEditField = Rect{ Arg::rightCenter(m_usernameField.rightCenter().movedBy(-10, 0).asPoint()), m_usernameField.w / 2, 58 };

	m_usernameEditState.text = getData().config.username;
	m_usernameEditState.cursorPos = m_usernameEditState.text.length();
}

void TitleScene::update() {
	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(RandomVec2(getData().config.windowSize.x, getData().config.windowSize.y));
	}

	if (m_usernameEditState.active) {
		m_usernameEditState.cursorPos = TextInput::UpdateText(m_usernameEditState.text, m_usernameEditState.cursorPos, TextInputMode::AllowBackSpaceDelete);

		// 最大字数を超えていたら削る
		if (MaxUsernameLength < m_usernameEditState.text.size()) {
			m_usernameEditState.text.resize(MaxUsernameLength);
			m_usernameEditState.cursorPos = Min(m_usernameEditState.cursorPos, MaxUsernameLength);
		}
	}

	if (KeyEnter.down() || (MouseL.down() && not m_usernameEditField.leftClicked())) {
		m_usernameEditState.active = false;

		getData().config.username = m_usernameEditState.text;
		getData().config.saveUsername();
	}

	if (m_usernameEditField.leftClicked()) {
		m_usernameEditState.active = true;
		m_usernameEditState.cursorStopwatch.start();
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
	// title
	{
		FontAsset(U"UI.Title")(m_titleName)
			.drawAt(TextStyle::Outline(.0, .5, Palette::White), center.movedBy(.0, -64.0), theme.background);
	}

	// version
	{
		FontAsset(U"UI.Small")(U"version - {}"_fmt(getData().config.version))
			.draw(Arg::bottomRight = getData().config.windowSize.movedBy(-10, -10), theme.uiFont);
	}

	// gamestart
	{
		m_gameStartButton.draw(m_gameStartButton.mouseOver() ? theme.background : Palette::White).drawFrame(4.0, Palette::White);

		FontAsset(U"UI.Normal")(U"ゲームスタート")
			.drawAt(TextStyle::Outline(.0, .1, Palette::White), m_gameStartButton.center(), theme.background);
	}

	// highscore
	{
		m_highscoreButton.draw(m_highscoreButton.mouseOver() ? theme.background : Palette::White).drawFrame(4.0, Palette::White);

		FontAsset(U"UI.Normal")(U"ハイスコア")
			.drawAt(TextStyle::Outline(.0, .1, Palette::White), m_highscoreButton.center(), theme.background);
	}

	// username field
	{
		m_usernameField.draw(Palette::White).drawFrame(4.0, Palette::White);

		FontAsset(U"UI.Normal")(U"USERNAME")
			.drawAt(TextStyle::Outline(.0, .1, Palette::White), m_usernameField.center().movedBy(-240, .0), theme.background);

		m_usernameEditField.draw(theme.background);

		FontAsset(U"UI.Small")(m_usernameEditState.text)
			.draw(Arg::leftCenter = m_usernameEditField.leftCenter().movedBy(16, 0), Palette::White);

		// テキストボックス
		if (m_usernameEditState.active) {
			auto glyphs = FontAsset(U"UI.Small").getGlyphs(m_usernameEditState.text);

			Vec2 cursorPos = m_usernameEditField.leftCenter().movedBy(24, 0);

			for (auto&& [index, glyph] : Indexed(glyphs)) {
				cursorPos.x += glyph.xAdvance;
			}

			const bool showCursor = (m_usernameEditState.cursorStopwatch.ms() % 1200 < 600)
				|| (m_usernameEditState.leftPressStopwatch.isRunning() && (m_usernameEditState.leftPressStopwatch < SecondsF{ 0.5 }))
				|| (m_usernameEditState.rightPressStopwatch.isRunning() && (m_usernameEditState.rightPressStopwatch < SecondsF{ 0.5 }));

			if (showCursor) {
				const RectF cursor(Arg::leftCenter(cursorPos.asPoint()), 2, 26);

				cursor.draw(Palette::White);
			}
		}
	}
}

void TitleScene::updateFadeIn(double) {

	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(RandomVec2(getData().config.windowSize.x, getData().config.windowSize.y));
	}
}
