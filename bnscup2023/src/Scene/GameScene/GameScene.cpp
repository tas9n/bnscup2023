#include "GameScene.hpp"

GameScene::GameScene(const InitData& init) : IScene(init),
	m_camera{ Vec2::Zero(), 1.0 }, m_player{ Vec2::Zero() } {

	m_decreasePlayerHPCountor.set(SecondsF{ DecreasePlayerHPWaitTime });
}

void GameScene::update() {
	if (MouseR.down()) {
		auto t = m_camera.createTransformer();
		m_meteos << Meteo{ Cursor::PosF() };
	}


	// 
	m_meteos.remove_if([&](const Meteo& meteo) {
		return Meteo::MaxLifetime < meteo.elapsed;
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

	// transformerでupdate
	{
		auto t = m_camera.createTransformer();

		// EffectAppendTwinkleStarWaitTime毎にTwinkleStar追加
		if (EffectAppendTwinkleStarWaitTime <= m_effectAppendTwinkleStarCountor.sF()) {
			m_effect.add<TwinkleStar>(m_player.pos.movedBy(Scene::Size() / 2) - RandomVec2(Scene::Width(), Scene::Height()));
			m_effectAppendTwinkleStarCountor.restart();
		}
	}

	// カメラ追従
	m_camera.setCenter(m_camera.getCenter().lerp(m_player.pos, 0.0075));
}

void GameScene::draw() const {
	{
		auto t = m_camera.createTransformer();

		m_effect.update();

		m_player.draw();
		for (const auto& meteo : m_meteos) meteo.draw();
	}

	// 回りを暗く
	Config config;
	Circle{ Scene::Center(), config.windowSize.x }.draw(ColorF{ Palette::Black, 0.0 }, Palette::Black);

	Vec2 uiPos{ 10, 40 };

	{
		int32 offset = FontAsset(U"UI.Normal")(U"HP: ").draw(Arg::leftCenter(uiPos.movedBy(0, 15)), theme.uiFont).w;
		m_player.hpBar.draw(RectF{ uiPos.movedBy(offset, 0), 210, 40 });
	}
}
