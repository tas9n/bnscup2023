#include "GameScene.hpp"

GameScene::GameScene(const InitData& init) : IScene(init),
	m_camera{ Vec2::Zero(), 1.0 }, m_player{ Vec2::Zero() } {

	m_decreasePlayerHPCountor.set(SecondsF{ DecreasePlayerHPWaitTime });
}

void GameScene::update() {
	Config config;

	// lifetime
	m_meteos.remove_if([&](const Meteo& meteo) {
		return Meteo::Lifetime < meteo.elapsed;
	});

	m_junks.remove_if([&](const Junk& junk) {
		return Junk::Lifetime < junk.elapsed;
	});

	// Updates
	m_player.update();

	for (auto& meteo : m_meteos) {
		if (m_player.interact(meteo)) {
			if (DecreasePlayerHPWaitTime <= m_decreasePlayerHPCountor.sF()) {
				m_player.damage(Meteo::DamageValue);
				m_decreasePlayerHPCountor.restart();
			}
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

	// meteo
	if (MeteoSpawnWaitTime <= m_meteoSpawnCountor.sF()) {
		auto pos = getPointOnRandomEdge(config.windowSize);
		m_meteos << Meteo{ m_player.pos - config.windowSize / 2 + pos };
		m_meteoSpawnCountor.restart();
	}

	if (JunkSpawnWaitTime <= m_junkSpawnCountor.sF()) {
		m_junks << Junk{ m_player.pos - config.windowSize / 2 + RandomVec2(RectF{ config.windowSize }) };
		m_junkSpawnCountor.restart();
	}

	// effect
	if (EffectAppendTwinkleStarWaitTime <= m_effectAppendTwinkleStarCountor.sF()) {
		m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
		m_effectAppendTwinkleStarCountor.restart();
	}

	// カメラ追従
	m_camera.setCenter(m_camera.getCenter().lerp(m_player.pos, 0.0075));
}

void GameScene::updateFadeIn(double) {
	// フェードイン中でもエフェクトが出るように
	{
		auto t = m_camera.createTransformer();

		// EffectAppendTwinkleStarWaitTime毎にTwinkleStar追加
		if (EffectAppendTwinkleStarWaitTime <= m_effectAppendTwinkleStarCountor.sF()) {
			m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
			m_effectAppendTwinkleStarCountor.restart();
		}
	}
}

void GameScene::draw() const {
	{
		auto t = m_camera.createTransformer();

		m_effect.update();

		m_player.draw();
		for (const auto& meteo : m_meteos) meteo.draw();
		for (const auto& junk : m_junks) junk.draw();
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
