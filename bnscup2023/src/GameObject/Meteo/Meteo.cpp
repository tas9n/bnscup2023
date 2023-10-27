#include "Meteo.hpp"

Meteo::Meteo(const Vec2& pos) : GameObject(pos, AssetName, U"🪨"_emoji, TextureSize) {
	direction = Random<double>(0_deg, 360_deg);
}

void Meteo::update() {
	double dt = Scene::DeltaTime();
	elapsed += dt;

	pos += Vec2::Up().rotated(direction) * MoveSpeed * dt;


	collision.setPos(pos);
}

void Meteo::draw() const {
	texture.drawAt(pos);
}
