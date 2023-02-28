#include <iostream>
#include <yara.h>


int callback_function(
    YR_SCAN_CONTEXT* context 
    ,int message
    ,void* message_data 
    ,void*user_data) {

    if (message == CALLBACK_MSG_RULE_MATCHING) {
        printf("rule matching\n");
    }
    else if (message == CALLBACK_MSG_SCAN_FINISHED) {
        printf("scan done \n");
    }
    else {
        printf(" no \n");
    }

    return CALLBACK_CONTINUE;
}
/*
message는 callback에서 해당 값이 매칭됐는 지 여부 또는 스캔이 마무리 되었는 지에 대해 나옴.

CALLBACK_CONTINUE
CALLBACK_ABORT
CALLBACK_ERROR

If it returns CALLBACK_CONTINUE YARA will continue normally,
CALLBACK_ABORT will abort the scan but the result from the yr_rules_scan_XXXX function will be ERROR_SUCCESS. 
On the other hand CALLBACK_ERROR will abort the scanning too, but the result from yr_rules_scan_XXXX will be ERROR_CALLBACK_ERROR.

message list 

CALLBACK_MSG_RULE_MATCHING
CALLBACK_MSG_RULE_NOT_MATCHING
CALLBACK_MSG_SCAN_FINISHED
CALLBACK_MSG_IMPORT_MODULE
CALLBACK_MSG_MODULE_IMPORTED
CALLBACK_MSG_TOO_MANY_MATCHES
CALLBACK_MSG_CONSOLE_LOG

*/



int main()
{
    YR_COMPILER* compiler = nullptr;
    YR_RULES* rules = nullptr;
    int result = 0;
    const char* rule_string = "rule HelloWorld { \
                                 strings: \
                                   $hello = \"Hello, world!\" \
                                 condition: \
                                   $hello \
                               }";

    // Initialize Yara
    const char* buffer = "Hello, world!";
    yr_initialize();

    // Create a new compiler
    yr_compiler_create(&compiler);

    // Compile the rule
    result = yr_compiler_add_string(compiler, rule_string, nullptr);
    if (result != ERROR_SUCCESS)
    {
       // std::cout << "Failed to compile rule: " << yr_compiler_get_error_message(compiler) << std::endl;
        goto _exit;
    }

    // Get the compiled rules
    result = yr_compiler_get_rules(compiler, &rules);
    if (result != ERROR_SUCCESS)
    {
        goto _exit;
    }

    result = yr_rules_scan_mem(rules, (const uint8_t*)buffer, strlen(buffer), SCAN_FLAGS_FAST_MODE, callback_function, nullptr,0);
    /*
    flag 값은 다음과 같이 
    SCAN_FLAGS_FAST_MODE 
    SCAN_FLAGS_NO_TRYCATCH 
    SCAN_FLAGS_REPORT_RULES_MATCHING 
    SCAN_FLAGS_REPORT_RULES_NOT_MATCHING
    
    */
_exit:
    // Clean up Yara
    if (rules != nullptr)
    {
        yr_rules_destroy(rules);
    }
    if (compiler != nullptr)
    {
        yr_compiler_destroy(compiler);
    }
    yr_finalize();

    return 0;
}