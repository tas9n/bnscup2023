#pragma once
#include "../GameObject.hpp"

struct DamageObject : public GameObject {
	const int32 DamageAmmount;

	DamageObject(GameObject::TypeTag type, const Vec2& position, const String& assetName, const Emoji& emoji, int32 size, int32 collisionSize, double fixScalingTime, int32 damagedAmmount) :
		GameObject(type, position, assetName, emoji, size, collisionSize, fixScalingTime),
		DamageAmmount{ damagedAmmount } {

	}

	int32 getDamage() const {
		return static_cast<int32>(DamageAmmount * scale);
	}
};
