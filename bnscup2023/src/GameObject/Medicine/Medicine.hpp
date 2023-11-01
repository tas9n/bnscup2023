#pragma once
#include "../GameObject.hpp"

struct Medicine : public GameObject {
	static constexpr int32 TextureSize = 32;
	static constexpr char32 AssetName[] = U"Object.Medicine";

	static constexpr double Lifetime = 4.0;

	static constexpr int32 DamageValue = -25;

	double direction = Random<double>(0_deg, 360_deg);

	double elapsed = .0;

	bool isPickuped = false;

	static constexpr double FixScalingTime = .5;

	Medicine(const Vec2&);

	void update() override;
	void draw() const override;

	void pick();
};
