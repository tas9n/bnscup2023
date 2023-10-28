#pragma once
#include "../GameObject.hpp"

struct Meteo : public GameObject {
	static constexpr int32 TextureSize = 128;
	static constexpr char32 AssetName[] = U"Object.Meteo";

	static constexpr int32 MoveSpeed = 300;
	static constexpr double Lifetime = 4.5;

	static constexpr int32 DamageValue = 25;

	double direction = Random<double>(0_deg, 360_deg);

	double elapsed = .0;

	static constexpr double FixScalingTime = .75;
	double opacity = .0;

	Meteo(const Vec2&);

	void update() override;
	void draw() const override;
};
