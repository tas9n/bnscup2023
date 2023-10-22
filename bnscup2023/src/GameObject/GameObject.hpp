#pragma once
#include <Siv3D.hpp>

struct GameObject {
	Vec2 pos;

	TextureRegion texture;

	GameObject(const Vec2& position, const String& assetName, const Emoji& emoji, int32 size) :
		pos{ position } {
		if (not TextureAsset::IsRegistered(assetName)) {
			TextureAsset::Register(assetName, emoji);
		}

		texture = TextureAsset(assetName).resized(size);
	}

	virtual void update() = 0;
	virtual void draw() const = 0;
};
