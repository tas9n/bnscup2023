#pragma once
#include <Siv3D.hpp>

struct Spawner {
	Stopwatch watch;

	Duration duration;

	Spawner(Duration _duration, StartImmediately startImmediately = StartImmediately::Yes) :
		duration{ _duration },
		watch{ startImmediately } {

	}

	bool update(double scale = 1.0) {
		if (not watch.isStarted()) watch.start();

		if (duration / scale <= watch.elapsed()) {
			watch.restart();
			return true;
		}
		return false;
	}
};
