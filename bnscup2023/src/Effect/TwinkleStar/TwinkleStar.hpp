#pragma once
#include <Siv3D.hpp>

struct TwinkleStar : IEffect {
	static constexpr double Lifetime = 3.0;
	static constexpr int32 BlinkingNum = 2;

	Vec2 pos;

	Color color{ 28, 36, 99 };

	double scale = Random(0.8, 2.0);

	TwinkleStar(const Vec2&);

	bool update(double t) override;
};
