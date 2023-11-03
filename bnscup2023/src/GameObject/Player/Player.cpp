#include "Player.hpp"

Player::Player(const Vec2& pos) : GameObject(GameObject::TypeTag::Player, pos, AssetName, U"🚀"_emoji, TextureSize, 64, .0) {
	
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

int32 Player::onCollision(std::shared_ptr<GameObject>& other, bool interval) {
	if (other->Type == GameObject::TypeTag::Meteo) {
		if(interval) damage(dynamic_cast<DamageObject*>(other.get())->getDamage());
		return 0;
	}
	if (other->Type == GameObject::TypeTag::Hole) {
		if (interval) damage(dynamic_cast<DamageObject*>(other.get())->getDamage());
		angle = Math::LerpAngle(angle, Vec2{ other->pos - pos }.getAngle(), 0.01);

		return 0;
	}
	if (other->Type == GameObject::TypeTag::Junk) {
		return dynamic_cast<Item*>(other.get())->pick();
	}
	if (other->Type == GameObject::TypeTag::Medicine) {
		int32 score = dynamic_cast<Item*>(other.get())->pick();
		if (score != 0) heal(15);
		return score;
	}

	return 0;
}

constexpr double Player::getMaxLifetime() const {
	return .0;
}


void Player::damage(int32 damage) {
	hpBar.damage(damage);

	AudioAsset(U"Game.Player.Damaged").playOneShot();
	damagedTimer.restart();
}

void Player::heal(int32 heal) {
	hpBar.heal(heal);

	AudioAsset::Register(U"Game.PickupItem", U"resource/sounds/pickup-item.mp3");
}

bool Player::isGameover() const {
	return hpBar.getHP() <= 0;
}
