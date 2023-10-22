#pragma once
#include "../Common.hpp"

class TitleScene : public App::Scene {
public:
	TitleScene(const InitData&);

	void update() override;

	void draw() const override;
};
