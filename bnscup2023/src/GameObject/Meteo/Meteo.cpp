#include "Meteo.hpp"

Meteo::Meteo(const Vec2& pos) : GameObject(pos, AssetName, U"🪨"_emoji, TextureSize, TextureSize - 30) {
	direction = Random<double>(0_deg, 360_deg);
}

void Meteo::update() {
	double dt = Scene::DeltaTime();
	elapsed += dt;

	pos += Vec2::Up().rotated(direction) * MoveSpeed * dt;

	if (elapsed <= FixScalingTime) {
		opacity = Periodic::Sine0_1(FixScalingTime * 2, elapsed - FixScalingTime / 2);
	}
	else if(elapsed <= Lifetime - FixScalingTime){
		opacity = 1.0;
	}
	else {
		opacity = Periodic::Sine0_1(FixScalingTime * 2, elapsed - (Lifetime - FixScalingTime) + FixScalingTime / 2);
	}

	collision.setPos(pos);
}

void Meteo::draw() const {
	texture.drawAt(pos, ColorF{ Palette::White, opacity });
}
