#pragma once
#include "../Item.hpp"

struct Junk : public Item {
	static constexpr int32 TextureSize = 32;
	static constexpr char32 AssetName[] = U"Object.Junk";

	double direction = Random<double>(0_deg, 360_deg);

	Junk(const Vec2&);

	void update() override;
	void draw() const override;

	constexpr double getMaxLifetime() const override;
};
