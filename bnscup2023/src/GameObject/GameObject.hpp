#pragma once
#include <Siv3D.hpp>

struct GameObject {
	enum class TypeTag {
		Player,
		Meteo,
		Medicine,
		Junk,
		Injector,
		Hole
	};
	const TypeTag Type;

	Vec2 pos;

	TextureRegion texture;

	Circle collision;

	Stopwatch timer{ StartImmediately::Yes };

	double scale = 1.0;

	double opacity = .0;
	const double FixScalingTime;

	GameObject(GameObject::TypeTag type, const Vec2& position, const String& assetName, const Emoji& emoji, int32 size, int32 collisionSize, double fixScalingTime) :
		Type{ type },
		pos{ position },
		collision{ position, collisionSize / 2 },
		FixScalingTime{ fixScalingTime } {
		if (not TextureAsset::IsRegistered(assetName)) {
			TextureAsset::Register(assetName, emoji);
		}

		texture = TextureAsset(assetName).resized(size);
	}

	virtual void update() {
		double elapsed = timer.sF();

		if (elapsed <= FixScalingTime) {
			opacity = Periodic::Sine0_1(FixScalingTime * 2, elapsed - FixScalingTime / 2);
		}
		else if (elapsed <= getMaxLifetime() - FixScalingTime) {
			opacity = 1.0;
		}
		else {
			opacity = Periodic::Sine0_1(FixScalingTime * 2, elapsed - (getMaxLifetime() - FixScalingTime) + FixScalingTime / 2);
		}

		collision.setPos(pos);
	}

	virtual void draw() const = 0;

	virtual constexpr double getMaxLifetime() const = 0;

	void drawCollision() const {
		collision.scaled(scale).drawFrame();
	}

	bool interact(const GameObject& other) {
		return collision.scaled(scale).intersects(other.collision.scaled(other.scale));
	}
};
