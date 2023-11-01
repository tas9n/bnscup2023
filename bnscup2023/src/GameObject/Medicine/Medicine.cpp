#include "Medicine.hpp"

Medicine::Medicine(const Vec2& position) : GameObject(position, AssetName, U"💊"_emoji, TextureSize, TextureSize) {
	scale = .0;
}

void Medicine::update() {
	double dt = Scene::DeltaTime();
	elapsed += dt;

	if (elapsed <= FixScalingTime) {
		scale = Periodic::Sine0_1(FixScalingTime * 2, elapsed - FixScalingTime / 2);
	}
	else if (elapsed <= Lifetime - FixScalingTime) {
		scale = 1.0;
	}
	else {
		isPickuped = true;
		scale = Periodic::Sine0_1(FixScalingTime * 2, elapsed - (Lifetime - FixScalingTime) + FixScalingTime / 2);
	}

	collision.setPos(pos);
}

void Medicine::draw() const {
	texture.scaled(scale).drawAt(pos);
}

void Medicine::pick() {
	isPickuped = true;
	elapsed = Lifetime - FixScalingTime;
}
