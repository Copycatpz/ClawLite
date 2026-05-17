// ClawLite — 技能解析器测试
// TODO: A 同学补充测试用例

#include "skill/skill_parser.h"
#include "test_helpers.h"
#include <iostream>

using namespace clawlite;

void testParseFrontmatter() {
    std::string block = R"(name: weather
description: Get weather information for a city
user-invocable: true
)";

    auto result = SkillParser::parseFrontmatter(block);
    TEST_ASSERT(result["name"] == "weather");
    TEST_ASSERT(result["description"] == "Get weather information for a city");
    TEST_ASSERT(result["user-invocable"] == "true");
    std::cout << "  [PASS] testParseFrontmatter\n";
}

void testExtractSections() {
    std::string content = R"(---
name: test
description: A test skill
---
This is the body content.
Multiple lines.
)";

    auto [fm, body] = SkillParser::extractSections(content);
    TEST_ASSERT(!fm.empty());
    TEST_ASSERT(body.find("This is the body content.") != std::string::npos);
    std::cout << "  [PASS] testExtractSections\n";
}

void testParseComplete() {
    // TODO: 创建一个临时 SKILL.md 文件并测试完整解析
    std::cout << "  [SKIP] testParseComplete (需要文件 I/O)\n";
}

int run_skill_parser_tests() {
    std::cout << "Skill Parser Tests:\n";
    RESET_FAILURES();
    testParseFrontmatter();
    testExtractSections();
    testParseComplete();
    int f = GET_FAILURES();
    if (f == 0) std::cout << "All skill parser tests passed.\n";
    else std::cout << f << " skill parser test(s) failed.\n";
    return f;
}
