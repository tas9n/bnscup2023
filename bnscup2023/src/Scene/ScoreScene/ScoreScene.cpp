#include "ScoreScene.hpp"

ScoreScene::ScoreScene(const InitData& init) : IScene(init){

}

void ScoreScene::update() {
	if (m_exitButton.leftClicked()) {
		if (m_leaderboardGetTask)
			m_leaderboardGetTask->cancel();

		changeScene(SceneState::Title);
	}

	// リーダーボード取得処理が完了したら
	if (m_leaderboardGetTask && m_leaderboardGetTask->isReady()) {
		if (const auto response = m_leaderboardGetTask->getResponse();
			response.isOK()) {

			if (LeaderBoard::ReadLeaderboard(m_leaderboardGetTask->getAsJSON(), m_records)) {

			}
			else {
				Print << U"Failed to read the leaderboard.";
			}
		}

		m_leaderboardGetTask.reset();
	}
}

void ScoreScene::draw() const {
	Point center = Scene::Center();

	m_exitButton.draw(m_exitButton.mouseOver() ? theme.background : Palette::White);

	FontAsset(U"UI.Small")(U"EXIT").draw(Arg::center = m_exitButton.center(), Palette::Black);

	m_exitButton.drawFrame(1.0, Palette::Black);

	if (m_leaderboardGetTask) {
		auto progress = m_leaderboardGetTask->getProgress();
		if (progress.download_total_bytes) {
			double ratio = static_cast<double>(progress.downloaded_bytes) / progress.download_total_bytes.value();

			RoundRect reigion{ Arg::center = center, Size{ getData().config.windowSize.x - 120, 120 }, 32 };

			reigion.setSize(reigion.w * ratio, reigion.h).draw(Palette::White);
			reigion.drawFrame(2.0, Palette::White);
		}
		else {
			Circle{ center, 120 }.drawArc((Scene::Time() * 90_deg), 300_deg, 10, 0);
		}

		return;
	}

	Vec2 uiCenter{ getData().config.windowSize.x / 2, 10 + RecordRectSize.y / 2 };
	{
		RectF reigion{ Arg::center = uiCenter, RecordRectSize };

		reigion.draw(theme.uiFont);

		FontAsset(U"UI.Small")(U"RANK").draw(Arg::leftCenter = reigion.leftCenter().movedBy(10, 0), theme.background);
		FontAsset(U"UI.Small")(U"USER NAME").draw(Arg::leftCenter = reigion.leftCenter().movedBy(110, 0), theme.background);
		FontAsset(U"UI.Small")(U"SCORE").draw(Arg::center = reigion.leftCenter().movedBy(410, 0), theme.background);
		FontAsset(U"UI.Small")(U"SURVIVE").draw(Arg::center = reigion.leftCenter().movedBy(550, 0), theme.background);

		reigion.drawFrame(1.0, Palette::Black);
	}

	for (int32 i = 0; i < m_records.size(); i++) {
		RectF reigion{ Arg::center = uiCenter.movedBy(0, RecordRectSize.y * static_cast<int32>(i + 1)), RecordRectSize };

		reigion.draw();

		const LeaderBoard::Record record = m_records[i];

		FontAsset(U"UI.Small")(i + 1).draw(Arg::center = reigion.leftCenter().movedBy(20, 0), theme.background);
		FontAsset(U"UI.Small")(record.userName).draw(Arg::leftCenter = reigion.leftCenter().movedBy(110, 0), Palette::Black);
		FontAsset(U"UI.Small")(ToString(record.score)).draw(Arg::center = reigion.leftCenter().movedBy(410, 0), Palette::Black);
		FontAsset(U"UI.Small")(U"{:.1f}秒"_fmt(record.survive)).draw(Arg::center = reigion.leftCenter().movedBy(550, 0), Palette::Black);

		reigion.drawFrame(1.0, Palette::Black);
	}
}

