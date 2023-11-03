#include "Hole.hpp"

Hole::Hole(const Vec2& position) :
	DamageObject(GameObject::TypeTag::Hole, position, AssetName, U"⚫"_emoji, TextureSize, TextureSize * 3, .5, 10) {

	scale = Random(0.5, 1.2);
	collision.r *= scale;
}

void Hole::update() {
	GameObject::update();
}

void Hole::draw() const {
	texture.scaled(scale).drawAt(pos, ColorF{ Palette::White, GameObject::opacity });
	collision.draw(ColorF{ Palette::Black, GameObject::opacity }, ColorF{ .0, .0, .0, .0 });
}

constexpr double Hole::getMaxLifetime() const {
	return 8.0;
}
