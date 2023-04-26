#include "stdafx.h"


class YaraScanner {
private:
	YR_COMPILER* yr_compiler = nullptr;
	YR_RULES* yr_rules = nullptr;
	YaraScanner() { 

		if (yr_initialize() != ERROR_SUCCESS) {
			printf("yr_initialized fail");
			exit(-1);
		}

		if (yr_compiler_create(&yr_compiler) != ERROR_SUCCESS) {
			printf("yr_compiler_create fail");
			exit(-1);
		}
	};
	YaraScanner(const YaraScanner& o);
	~YaraScanner() {
		
		if (yr_rules) {
			yr_rules_destroy(yr_rules);
		}
		if (yr_compiler) {
			yr_compiler_destroy(yr_compiler);
		}
	
		if (yr_finalize() != ERROR_SUCCESS) {
			printf("yr_finalized fail");
			exit(-1);
		}
	};

	static YaraScanner* scanner;
public:
	static YaraScanner* GetInstance();
	static void ReleaseInstance();
	int LoadRulesFromFile(const char* rulepath);
	
};