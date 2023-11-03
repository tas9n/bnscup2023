#pragma once
#include "../GameObject.hpp"

struct Injector : public GameObject {
	static constexpr int32 TextureSize = 32;
	static constexpr char32 AssetName[] = U"Object.Injector";

	static constexpr double Lifetime = 4.5;

	double direction = Random<double>(0_deg, 360_deg);

	double elapsed = .0;

	static constexpr double FixScalingTime = .25;

	bool isPickuped = false;

	Injector(const Vec2&);

	void update() override;
	void draw() const override;

	void pick();
};
