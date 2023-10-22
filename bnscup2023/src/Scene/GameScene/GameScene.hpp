#pragma once
#include "../Common.hpp"
#include "../../GameObject/Player/Player.hpp"
#include "../../GameObject/Meteo/Meteo.hpp"

class GameScene : public App::Scene {
	BasicCamera2D m_camera;
	Player m_player;
	Array<Meteo> m_meteos;

public:
	GameScene(const InitData&);

	void update() override;

	void draw() const override;
};
