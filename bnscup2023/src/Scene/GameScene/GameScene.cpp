#include "GameScene.hpp"

GameScene::GameScene(const InitData& init) : IScene(init),
	m_camera{ Vec2::Zero(), 1.0 }, m_player{ Vec2::Zero() } {

	AudioAsset(U"Global.BGM").playOneShot(0.5, 0.0, 0.75);
}

void GameScene::update() {
	Config config;

	m_objects.remove_if([](const std::shared_ptr<GameObject>& object) {
		return object->getMaxLifetime() <= object->timer.sF();
	});

	// effect
	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
	}

	// Spawn

	if (m_meteoSpawner.update()) {
		auto pos = getPointOnRandomEdge(config.windowSize);
		m_objects << std::make_shared<Meteo>(m_player.pos - config.windowSize / 2 + pos);
	}

	if (m_junkSpawner.update()) {
		m_objects << std::make_shared<Junk>(m_player.pos - config.windowSize / 2 + RandomVec2(RectF{ config.windowSize }));
	}

	if (m_holeSpawner.update()) {
		m_objects << std::make_shared<Hole>(OffsetCircular{ m_player.pos, 128.0 + Random(0, config.windowSize.x / 2 - 128), Random(0.0, 360_deg) });
	}

	if (m_medicineSpawner.update()) {
		m_objects << std::make_shared<Medicine>(m_player.pos - config.windowSize / 2 + RandomVec2(RectF{ config.windowSize }));
	}

	// Updates
	m_player.update();

	for (std::shared_ptr<GameObject>& object : m_objects) {
		object->update();

		if (object->interact(m_player)) {
			getData().score += m_player.onCollision(object, m_interactInterval.update());
		}
	}

	if (m_player.hpBar.getHP() <= 0) {
		changeScene(SceneState::Score);
	}

	// カメラ追従
	m_camera.setCenter(m_camera.getCenter().lerp(m_player.pos, 0.0075));
}

void GameScene::updateFadeIn(double) {
	// フェードイン中でもエフェクトが出るように
	{
		auto t = m_camera.createTransformer();

		// EffectAppendTwinkleStarWaitTime毎にTwinkleStar追加
		if (m_twinkleStarSpawner.update()) {
			m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
		}
	}
}

void GameScene::draw() const {
	{
		auto t = m_camera.createTransformer();

		m_effect.update();

		for (const std::shared_ptr<GameObject>& object : m_objects) {
			object->draw();
		}

		m_player.draw();
	}

	// 回りを暗く
	Config config;
	Circle{ Scene::Center(), config.windowSize.x }.draw(ColorF{ Palette::Black, 0.0 }, Palette::Black);

	Vec2 uiPos{ 10, 40 };

	m_player.hpBar.draw(RectF{ uiPos, 210, 32 });
	uiPos.y += 32 + 10;

	FontAsset(U"UI.Normal")(U"Score: {}"_fmt(getData().score)).draw(uiPos, theme.uiFont);
}

template<class T>
void GameScene::removeIfPassLifetime(Array<T>& objects) {
	objects.remove_if([](const T& obj) {
		return T::Lifetime < obj.elapsed;
	});
}

void GameScene::damagedPlayer(int32 damage) {
	if (m_interactInterval.update()) {
		if (0 <= damage) {
			getData().score -= 50;
			m_player.damage(damage);
		} else m_player.heal(-damage);
	}
}

void GameScene::addScore(int32 add) {
	int32& score = getData().score;
	score += add;
}

Vec2 GameScene::getPointOnRandomEdge(const Vec2& size) const {
	int32 side = Random(0, 3);

	if (side == 0) return Vec2{ Random(0.0, size.x), 0.0 };
	if (side == 1) return Vec2{ Random(0.0, size.x), size.y };
	if (side == 2) return Vec2{ 0.0, Random(0.0, size.y) };

	return Vec2{ size.x, Random(0.0, size.y) };
}
