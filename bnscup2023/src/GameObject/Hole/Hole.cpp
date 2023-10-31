#include "Hole.hpp"

Hole::Hole(const Vec2& position) : GameObject(position, AssetName, U"⚫"_emoji, TextureSize, TextureSize * 2.5) {
	scale = .0;
}

void Hole::update() {
	double dt = Scene::DeltaTime();
	elapsed += dt;

	if (elapsed <= FixScalingTime) {
		scale = Periodic::Sine0_1(FixScalingTime * 2, elapsed - FixScalingTime / 2);
	}
	else if (elapsed <= Lifetime - FixScalingTime) {
		scale = 1.0;
	}
	else {
		scale = Periodic::Sine0_1(FixScalingTime * 2, elapsed - (Lifetime - FixScalingTime) + FixScalingTime / 2);
	}

	collision.setPos(pos);
}

void Hole::draw() const {
	texture.scaled(scale).drawAt(pos);
	collision.scaled(scale).draw(Palette::Black, ColorF{ Palette::Black, 0 });
}
