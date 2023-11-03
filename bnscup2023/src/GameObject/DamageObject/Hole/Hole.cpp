#include "Hole.hpp"

Hole::Hole(const Vec2& position) :
	DamageObject(GameObject::TypeTag::Hole, position, AssetName, U"⚫"_emoji, TextureSize, TextureSize * 3, .5, 10) {

	scale = Random(.5, 1.25);
}

void Hole::update() {
	GameObject::update();
}

void Hole::draw() const {
	texture.scaled(scale).drawAt(pos, ColorF{ Palette::White, GameObject::opacity });
	collision.scaled(scale).draw(ColorF{Palette::Black, GameObject::opacity}, ColorF{ Palette::Black, .0 });
}

constexpr double Hole::getMaxLifetime() const {
	return 8.0;
}
