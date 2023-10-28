#pragma once
#include <Siv3D.hpp>

struct Spawner {
	Stopwatch watch;

	Duration duration;

	Spawner(Duration _duration, StartImmediately startImmediately = StartImmediately::Yes) :
		duration{ _duration },
		watch{ startImmediately } {

	}

	bool update() {
		if (duration <= watch.elapsed()) {
			watch.restart();
			return true;
		}
	}
};
