#pragma once
#include "../Common.hpp"

#include "../../Utility/Theme.hpp"
#include "../../Utility/Config.hpp"
#include "../../Utility/Spawner.hpp"

#include "../../GameObject/Player/Player.hpp"
#include "../../GameObject/Meteo/Meteo.hpp"
#include "../../GameObject/Junk/Junk.hpp"
#include "../../GameObject/Hole/Hole.hpp"

#include "../../Effect/TwinkleStar/TwinkleStar.hpp"

class GameScene : public App::Scene {
	BasicCamera2D m_camera;
	Player m_player;

	Array<Meteo> m_meteos;
	Array<Junk> m_junks;
	Array<Hole> m_holes;

	// 連続ヒットしないように時間を置く
	Spawner m_decreasePlayerHPCountor{ 0.5s, StartImmediately::Yes };

	// Spawner
	Spawner m_meteoSpawner{ 0.75s, StartImmediately::Yes };

	static constexpr int32 JunkScoreAmmount = 100;
	Spawner m_junkSpawner{ 1.25s, StartImmediately::Yes };

	Spawner m_holeSpawner{ 6.5s, StartImmediately::Yes };

	Effect m_effect;
	Spawner m_twinkleStarSpawner{ 0.05s, StartImmediately::Yes };

	int32 m_level = 1;

public:
	GameScene(const InitData&);

	void update() override;

	void updateFadeIn(double) override;

	void draw() const override;

	template<class T>
	void removeIfPassLifetime(Array<T>&);

	void damagedPlayer(int32);

	void addScore(int32);

	Vec2 getPointOnRandomEdge(const Vec2&) const;
};
