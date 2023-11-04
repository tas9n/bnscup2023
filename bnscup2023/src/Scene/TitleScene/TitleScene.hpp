#pragma once
#include "../Common.hpp"

#include "../../Utility/Theme.hpp"
#include "../../Utility/Spawner.hpp"

#include "../../Effect/TwinkleStar/TwinkleStar.hpp"

class TitleScene : public App::Scene {
	String m_titleName;

	Effect m_effect;
	Spawner m_twinkleStarSpawner{ 0.05s, StartImmediately::No };

	Rect m_gameStartButton;
	Rect m_highscoreButton;

	Rect m_usernameField;
	Rect m_usernameEditField;

	static constexpr size_t MaxUsernameLength = 12;
	TextEditState m_usernameEditState;

public:
	TitleScene(const InitData&);

	void update() override;

	void updateFadeIn(double) override;

	void draw() const override;
};
