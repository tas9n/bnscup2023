# include <Siv3D.hpp> // OpenSiv3D v0.6.6

class WindowRecorder {
	VideoWriter m_writer;
	double t = 0;

public:
	/// @brief Siv3Dのウィンドウを録画します。
	/// @param path ファイルパス
	/// @param size 動画サイズ
	/// @param fps fps
	WindowRecorder() { }

	void open(FilePath path, Size size, double fps) {
		m_writer.open(path, size, fps);
	}

	/// @brief 実行中、ウィンドウを録画し、動画に書き込みます。
	void update() {
		if (m_writer.isOpen()) return;

		double fps = m_writer.getFPS();

		ScreenCapture::RequestCurrentFrame();

		t += Scene::DeltaTime();

		if (1 / fps <= t) {
			t -= 1 / fps;
			m_writer.writeFrame(ScreenCapture::GetFrame());
		}
	}

	bool isOpen() const {
		return m_writer.isOpen();
	}
};
