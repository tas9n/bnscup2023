#include "Player.hpp"

Player::Player(const Vec2& pos) : GameObject(pos, AssetName, U"🚀"_emoji, TextureSize) {

}

void Player::update() {
	double dt = Scene::DeltaTime();

	if (KeyA.pressed()) direction -= rotationSpeed * dt;
	if (KeyD.pressed()) direction += rotationSpeed * dt;

	if(MouseL.pressed())
		pos += Vec2::Up().rotated(direction) * DefaultMoveSpeed * speed * dt;


	collision.setPos(pos);

	hpBar.update();
}

void Player::draw() const {
	texture.rotated(DefaultTextureRotationOffset + direction).drawAt(pos);
}


void Player::damage(int32 ammount) {
	hpBar.damage(ammount);
}

bool Player::isGameover() const {
	return hpBar.getHP() <= 0;
}
