#pragma once
#include "../GameObject.hpp"

struct Item : public GameObject {

	const int32 ScoreAmmount;
	bool isPickuped = false;

	Item(GameObject::TypeTag type, const Vec2& position, const String& assetName, const Emoji& emoji, int32 size, int32 collisionSize, double fixScalingTime, int32 ammount) :
		GameObject(type, position, assetName, emoji, size, collisionSize, fixScalingTime),
		ScoreAmmount{ ammount } {

	}

	int32 pick() {
		if (not isPickuped) {
			AudioAsset(U"Game.PickupItem").playOneShot();
			timer.set(Duration{ getMaxLifetime() - FixScalingTime });

			isPickuped = true;
			return static_cast<int32>(ScoreAmmount * scale);
		}

		return 0;
	}
};
