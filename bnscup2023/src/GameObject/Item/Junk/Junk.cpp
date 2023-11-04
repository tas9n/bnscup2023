#include "Junk.hpp"

Junk::Junk(const Vec2& position) : Item(GameObject::TypeTag::Junk, position, AssetName, U"💎"_emoji, TextureSize, 32, .25, 100) {
	scale = Random(.5, 1.5);
	collision.r *= scale;
}

void Junk::update() {
	GameObject::update();
}

void Junk::draw() const {
	const ScopedRenderStates2D blend{ BlendState::Additive };

	auto tex = texture.scaled(scale);
	tex.rotated(Periodic::Sine1_1(1s, Scene::Time()) * 15_deg).drawAt(pos, ColorF{ Palette::White, GameObject::opacity });
	tex.scaled(1.1).rotated(Periodic::Sine1_1(1s, Scene::Time()) * 15_deg).drawAt(pos, ColorF{ Palette::White, .5 * GameObject::opacity });
}

constexpr double Junk::getMaxLifetime() const {
	return 4.5;
}
