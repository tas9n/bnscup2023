#pragma once
#include "../DamageObject.hpp"

struct Hole : public DamageObject {
	static constexpr int32 TextureSize = 128;
	static constexpr char32 AssetName[] = U"Object.Hole";

	Hole(const Vec2&);

	void update() override;
	void draw() const override;
	constexpr double getMaxLifetime() const override;
};
