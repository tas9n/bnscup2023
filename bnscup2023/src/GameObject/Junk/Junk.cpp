#include "Junk.hpp"

Junk::Junk(const Vec2& position) : GameObject(position, AssetName, U"💎"_emoji, TextureSize) {

}

void Junk::update() {
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

void Junk::draw() const {
	const ScopedRenderStates2D blend{ BlendState::Additive };

	auto tex = texture.scaled(scale);
	tex.rotated(Periodic::Sine1_1(1s, elapsed) * 15_deg).drawAt(pos, ColorF{ Palette::White, scale });
	tex.scaled(1.1).rotated(Periodic::Sine1_1(1s, elapsed) * 15_deg).drawAt(pos, ColorF{Palette::White, scale});
}
