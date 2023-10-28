#include "GameScene.hpp"

GameScene::GameScene(const InitData& init) : IScene(init),
	m_camera{ Vec2::Zero(), 1.0 }, m_player{ Vec2::Zero() } {

}

void GameScene::update() {
	Config config;

	// lifetime
	removeIfPassLifetime(m_meteos);
	removeIfPassLifetime(m_junks);
	removeIfPassLifetime(m_holes);

	// effect
	if (m_twinkleStarSpawner.update()) {
		m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
	}

	// Spawn
	if (m_meteoSpawner.update()) {
		auto pos = getPointOnRandomEdge(config.windowSize);
		m_meteos << Meteo{ m_player.pos - config.windowSize / 2 + pos };
	}

	if (m_junkSpawner.update()) {
		m_junks << Junk{ m_player.pos - config.windowSize / 2 + RandomVec2(RectF{ config.windowSize }) };
	}

	if (m_holeSpawner.update()) {
		m_holes << Hole{ OffsetCircular{ m_player.pos, 128.0 + Random(0, config.windowSize.x / 2 - 128), Random(0.0, 360_deg) } };
	}

	// Updates
	m_player.update();

	for (auto& meteo : m_meteos) {
		if (m_player.interact(meteo)) {
			damagedPlayer(meteo.DamageValue);
		}

		meteo.update();
	}

	for (auto& junk : m_junks) {
		if (m_player.interact(junk) && not junk.isPickuped) {
			junk.pick();
			addScore(JunkScoreAmmount);
		}
		junk.update();
	}

	for (auto& hole : m_holes) {
		if (m_player.interact(hole)) {
			damagedPlayer(hole.DamageValue);

			m_player.angle = Math::LerpAngle(m_player.angle, Vec2{ hole.pos - m_player.pos }.getAngle(), 0.01);
		}

		hole.update();
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

		for (const auto& junk : m_junks) junk.draw();
		for (const auto& hole : m_holes) hole.draw();

		m_player.draw();

		for (const auto& meteo : m_meteos) meteo.draw();
	}

	// 回りを暗く
	Config config;
	Circle{ Scene::Center(), config.windowSize.x }.draw(ColorF{ Palette::Black, 0.0 }, Palette::Black);

	Vec2 uiPos{ 10, 40 };

	{
		double offset = FontAsset(U"UI.Normal")(U"HP: ").draw(Arg::leftCenter(uiPos.movedBy(0, 15)), theme.uiFont).w;
		m_player.hpBar.draw(RectF{ uiPos.movedBy(offset, 0), 210, 30 });
		uiPos.y += 60;
	}

	FontAsset(U"UI.Normal")(U"Score: {}"_fmt(getData().score)).draw(Arg::leftCenter(uiPos), theme.uiFont);
}

template<class T>
void GameScene::removeIfPassLifetime(Array<T>& objects) {
	objects.remove_if([](const T& obj) {
		return T::Lifetime < obj.elapsed;
	});
}

void GameScene::damagedPlayer(int32 damage) {
	if (m_decreasePlayerHPCountor.update()) {
		m_player.damage(damage);
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
