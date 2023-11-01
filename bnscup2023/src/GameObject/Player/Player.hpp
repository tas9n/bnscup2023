#pragma once
#include "../GameObject.hpp"
#include "../../Utility/HPBar.hpp"

class Player : public GameObject {
public:
	static constexpr char32 AssetName[] = U"Object.Player";

	static constexpr int32 TextureSize = 64;
	static constexpr double DefaultTextureRotationOffset = -45_deg;

	static constexpr int32 DefaultMoveSpeed = 200;

	double speed = 1.0;
	double angle = .0;
	double rotationSpeed = 120_deg;

	HPBar hpBar{ 100, 100 };

	static constexpr double MaxDamagedTimer = .5;
	Stopwatch damagedTimer{ StartImmediately::No };

	Player(const Vec2&);

	void update() override;
	void draw() const override;

	void damage(int32);
	void heal(int32);

	bool isGameover() const;
};
