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

	// 連続ヒットしないように時間を置く
	Spawner m_interactInterval{ 1.0s, StartImmediately::Yes };

	// Spawner
	Spawner m_meteoSpawner{ 0.75s, StartImmediately::Yes };
	Spawner m_junkSpawner{ 1.25s, StartImmediately::Yes };
	Spawner m_holeSpawner{ 6.5s, StartImmediately::Yes };
	Spawner m_medicineSpawner{ 5.0s, StartImmediately::Yes };
	Spawner m_injectorSpawner{ 6.0s, StartImmediately::Yes };

	// Effect
	Effect m_effect;
	Spawner m_twinkleStarSpawner{ 0.05s, StartImmediately::Yes };

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
