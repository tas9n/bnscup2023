#include "TwinkleStar.hpp"

TwinkleStar::TwinkleStar(const Vec2& position) :
	pos{ position } {

}

bool TwinkleStar::update(double t) {
	const ScopedRenderStates2D blend{ BlendState::Additive };

	double freq = Periodic::Sine0_1(Lifetime / BlinkingNum, (Lifetime / BlinkingNum) * 0.75 + t);

	Shape2D::NStar(4, 4.5, 1.5, pos).draw(ColorF{ color, freq });
	Shape2D::NStar(4, 3.0, 1.5, pos).draw(ColorF{ color, freq });

	return t < Lifetime;
}
