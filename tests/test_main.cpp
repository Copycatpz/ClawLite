// ClawLite — 统一测试入口

#include <iostream>

// 各测试模块的入口函数声明
extern int run_skill_parser_tests();
extern int run_skill_registry_tests();
extern int run_chunker_tests();
extern int run_memory_store_tests();
extern int run_search_tests();
extern int run_session_store_tests();
extern int run_prompt_builder_tests();

int main() {
    std::cout << "========== ClawLite Tests ==========\n\n";

    int failures = 0;
    failures += run_skill_parser_tests();
    failures += run_skill_registry_tests();
    failures += run_chunker_tests();
    failures += run_memory_store_tests();
    failures += run_search_tests();
    failures += run_session_store_tests();
    failures += run_prompt_builder_tests();

    std::cout << "\n========== Results ==========\n";
    if (failures == 0) {
        std::cout << "All tests passed!\n";
    } else {
        std::cout << failures << " test(s) failed.\n";
    }
    return failures;
}
