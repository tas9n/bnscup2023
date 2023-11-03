#pragma once
#include "../Item.hpp"

struct Medicine : public Item {
	static constexpr int32 TextureSize = 32;
	static constexpr char32 AssetName[] = U"Object.Medicine";

	double direction = Random<double>(0_deg, 360_deg);

	Medicine(const Vec2&);

	void update() override;
	void draw() const override;

	constexpr double getMaxLifetime() const override;
};
