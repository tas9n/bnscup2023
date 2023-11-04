#pragma once
#include "../Common.hpp"

#include "../../Utility/Theme.hpp"
#include "../../Utility/Spawner.hpp"
#include "../../Utility/LeaderBoard.hpp"

class ScoreScene : public App::Scene {
	String m_titleName;

	static constexpr Size RecordRectSize{ 800, 60 };

	// リーダーボードを取得するタスク
	Optional<AsyncHTTPTask> m_leaderboardGetTask = LeaderBoard::CreateGetTask(getData().LeaderboardURL, 7);

	Array<LeaderBoard::Record> m_records;

	Rect m_exitButton{ Arg::center(getData().config.windowSize.x / 2, getData().config.windowSize.y - 10 - RecordRectSize.y / 2), RecordRectSize  };

public:
	ScoreScene(const InitData&);

	void update() override;

	void draw() const override;
};
