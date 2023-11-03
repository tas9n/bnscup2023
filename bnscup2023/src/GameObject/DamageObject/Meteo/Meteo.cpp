#include "Meteo.hpp"

Meteo::Meteo(const Vec2& pos) :
	DamageObject(GameObject::TypeTag::Meteo, pos, AssetName, U"🌑"_emoji, TextureSize, TextureSize - 32, .75, DamageValue) {

	direction = Random<double>(0_deg, 360_deg);

	scale = Random(0.5, 1.2);
}

void Meteo::update() {
	pos += Vec2::Up().rotated(direction) * MoveSpeed * (1.2 - scale) * Scene::DeltaTime();

	GameObject::update();
}

void Meteo::draw() const {
	texture.scaled(scale).drawAt(pos, ColorF{ Palette::White, GameObject::opacity });
}

constexpr double Meteo::getMaxLifetime() const {
	return 4.5;
}
