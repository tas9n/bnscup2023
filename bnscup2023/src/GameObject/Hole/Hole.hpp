#pragma once
#include "../GameObject.hpp"

struct Hole : public GameObject {
	static constexpr int32 TextureSize = 90;
	static constexpr char32 AssetName[] = U"Object.Hole";

	static constexpr double Lifetime = 8.0;

	static constexpr int32 DamageValue = 5;

	double direction = Random<double>(0_deg, 360_deg);

	double elapsed = .0;

	static constexpr double FixScalingTime = .1;

	Hole(const Vec2&);

	void update() override;
	void draw() const override;
};
