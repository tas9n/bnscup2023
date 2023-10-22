#include "GameScene.hpp"

GameScene::GameScene(const InitData& init) : IScene(init),
	m_camera{ Vec2::Zero(), 1.0 }, m_player{ Vec2::Zero() } {

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

	for (auto& meteo : m_meteos) meteo.update();

	// Set camera forcus center
	m_camera.setCenter(m_camera.getCenter().lerp(m_player.pos, 0.01));
}

void GameScene::draw() const {
	{
		auto t = m_camera.createTransformer();

		m_player.draw();
		for (const auto& meteo : m_meteos) meteo.draw();
	}
}
