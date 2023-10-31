#include "Player.hpp"

Player::Player(const Vec2& pos) : GameObject(pos, AssetName, U"🚀"_emoji, TextureSize, 64) {
	
}

void Player::update() {
	double dt = Scene::DeltaTime();

	if (KeyA.pressed()) angle -= rotationSpeed * dt;
	if (KeyD.pressed()) angle += rotationSpeed * dt;

	pos += Circular{ DefaultMoveSpeed * speed * dt, angle };

	collision.setPos(pos);

	if (MaxDamagedTimer <= damagedTimer.sF()) {
		damagedTimer.reset();
	}

	hpBar.update();
}

void Player::draw() const {
	texture.rotated(DefaultTextureRotationOffset + angle).drawAt(pos);
	texture.rotated(DefaultTextureRotationOffset + angle).drawAt(pos, ColorF{ Palette::Red, Periodic::Jump0_1(MaxDamagedTimer, damagedTimer.sF()) });
}


void Player::damage(int32 ammount) {
	hpBar.damage(ammount);

	damagedTimer.restart();
}

bool Player::isGameover() const {
	return hpBar.getHP() <= 0;
}
