#pragma once
#include <Siv3D.hpp>

inline struct Debug_impl{
	void operator<<(String s) {
		#if SIV3D_BUILD(DEBUG)
		Console << s;
		#endif
	}
} Debug;
