#pragma once
#include "../GameObject.hpp"

struct Meteo : public GameObject {
	static constexpr int32 TextureSize = 128;
	static constexpr char32 AssetName[] = U"Object.Meteo";

	static constexpr int32 MoveSpeed = 150;
	static constexpr double MaxLifetime = 3.0;

	double direction = Random<double>(0_deg, 360_deg);

	double elapsed = .0;

	Meteo(const Vec2&);

	void update() override;
	void draw() const override;
};
