#include "yara_scan.h"
#include "stdafx.h"

YaraScanner* YaraScanner::scanner = nullptr;

YaraScanner* YaraScanner::GetInstance() {

	if (scanner == NULL) {
		scanner = new YaraScanner();
	}

	return scanner;
}

void YaraScanner::ReleaseInstance() {
	if (scanner) {
		delete scanner;
		scanner = nullptr;
	}
}

int YaraScanner::LoadRulesFromFile(const char* rulespath) {
	return yr_rules_load(rulespath, &yr_rules);
}