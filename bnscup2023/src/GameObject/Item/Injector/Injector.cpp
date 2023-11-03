#include "Injector.hpp"

Injector::Injector(const Vec2& position) : GameObject(position, AssetName, U"💉"_emoji, TextureSize, 32) {
	scale = .0;
}

void Injector::update() {
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

void Injector::draw() const {
	texture.scaled(scale).rotated(Periodic::Sine1_1(1s, elapsed) * 15_deg).drawAt(pos, ColorF{ Palette::White, scale });
}

void Injector::pick() {
	isPickuped = true;
	elapsed = Lifetime - FixScalingTime;
}
