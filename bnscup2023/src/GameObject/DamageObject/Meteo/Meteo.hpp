#pragma once
#include "../DamageObject.hpp"

struct Meteo : public DamageObject {
	static constexpr int32 TextureSize = 128;
	static constexpr char32 AssetName[] = U"Object.Meteo";

	static constexpr int32 MoveSpeed = 300;

	static constexpr int32 DamageValue = 25;

	double direction = Random<double>(0_deg, 360_deg);

	double opacity = .0;

	Meteo(const Vec2&);

	void update() override;
	void draw() const override;
	constexpr double getMaxLifetime() const override;
};
