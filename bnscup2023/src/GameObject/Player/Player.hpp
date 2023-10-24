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
	double direction = .0;
	double rotationSpeed = 120_deg;

	HPBar hpBar{ 100, 100 };

	Player(const Vec2&);

	void update() override;
	void draw() const override;

	void damage(int32);

	bool isGameover() const;
};
