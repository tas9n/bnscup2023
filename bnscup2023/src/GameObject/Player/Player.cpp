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

	AudioAsset(U"Game.Player.Damaged").playOneShot();
	damagedTimer.restart();
}

void Player::heal(int32 ammount) {
	hpBar.heal(ammount);

	AudioAsset::Register(U"Game.PickupItem", U"resource/sounds/pickup-item.mp3");
}

bool Player::isGameover() const {
	return hpBar.getHP() <= 0;
}
