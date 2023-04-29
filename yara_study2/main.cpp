#include "stdafx.h"


int main(int argc, char* argv[]) {
	
	if (IsDebuggerPresent()) {
		return 0;
	}
	YaraScanner* scanner = YaraScanner::GetInstance();



	YaraScanner::ReleaseInstance();
}