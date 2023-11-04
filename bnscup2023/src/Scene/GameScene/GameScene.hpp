#pragma once
#include "../Common.hpp"

#include "../../Utility/Theme.hpp"
#include "../../Utility/Config.hpp"
#include "../../Utility/Spawner.hpp"

#include "../../GameObject/Player/Player.hpp"
#include "../../GameObject/DamageObject/Meteo/Meteo.hpp"
#include "../../GameObject/Item/Junk/Junk.hpp"
#include "../../GameObject/DamageObject/Hole/Hole.hpp"
#include "../../GameObject/Item/Medicine/Medicine.hpp"

#include "../../Effect/TwinkleStar/TwinkleStar.hpp"

class GameScene : public App::Scene {
	BasicCamera2D m_camera;
	Player m_player;

	Array<std::shared_ptr<GameObject>> m_objects;

	static constexpr int32 JunkScoreAmmount = 100;

	Stopwatch m_timer{ StartImmediately::No };

	// 連続ヒットしないように時間を置く
	Spawner m_interactInterval{ .5s, StartImmediately::No };

	// Spawner
	int32 m_gameLevel = 1;
	double m_spawnerScale = 1.0;
	Spawner m_spawnerScaleIncreaceTimer{ 10.0s, StartImmediately::No };

	static constexpr double LevelUpAnimTime = 2.5;
	Stopwatch m_levelUpAnimTimer{ StartImmediately::No };

	Spawner m_meteoSpawner{ 0.75s, StartImmediately::No };
	Spawner m_junkSpawner{ 1.25s, StartImmediately::No };
	Spawner m_holeSpawner{ 6.5s, StartImmediately::No };
	Spawner m_medicineSpawner{ 5.0s, StartImmediately::No };
	Spawner m_injectorSpawner{ 6.0s, StartImmediately::No };

	// Effect
	Effect m_effect;
	Spawner m_twinkleStarSpawner{ 0.05s, StartImmediately::No };

	Spawner m_applyInjectorTimer{ 5.0s, StartImmediately::No };

	static constexpr double InjectorSpeedMultiplier = 1.25;
	static constexpr double InjectorScaleMultiplier = 1.5;

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
