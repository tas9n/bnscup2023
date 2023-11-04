#include "Medicine.hpp"

Medicine::Medicine(const Vec2& position) :
	Item(GameObject::TypeTag::Medicine, position, AssetName, U"🛠️"_emoji, TextureSize, TextureSize, .5, -10) {

}

void Medicine::update() {
	GameObject::update();
}

void Medicine::draw() const {
	texture.drawAt(pos, ColorF{ Palette::White, GameObject::opacity });
}

constexpr double Medicine::getMaxLifetime() const {
	return 3.0;
}
