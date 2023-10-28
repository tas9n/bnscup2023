#pragma once
#include <Siv3D.hpp>

struct GameObject {
	Vec2 pos;

	TextureRegion texture;

	Circle collision;

	GameObject(const Vec2& position, const String& assetName, const Emoji& emoji, int32 size, int32 collisionSize) :
		pos{ position },
		collision{ position, collisionSize / 2} {
		if (not TextureAsset::IsRegistered(assetName)) {
			TextureAsset::Register(assetName, emoji);
		}

		texture = TextureAsset(assetName).resized(size);
	}

	virtual void update() = 0;
	virtual void draw() const = 0;

	void drawCollision() const {
		collision.drawFrame();
	}

	bool interact(const GameObject& other) {
		return collision.intersects(other.collision);
	}
};
