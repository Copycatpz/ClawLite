// ClawLite — 技能解析器测试
// TODO: A 同学补充测试用例

#include "skill/skill_parser.h"
#include <iostream>
#include <cassert>

using namespace clawlite;

void testParseFrontmatter() {
    std::string block = R"(name: weather
description: Get weather information for a city
user-invocable: true
)";

    auto result = SkillParser::parseFrontmatter(block);
    assert(result["name"] == "weather");
    assert(result["description"] == "Get weather information for a city");
    assert(result["user-invocable"] == "true");
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
    assert(!fm.empty());
    assert(body.find("This is the body content.") != std::string::npos);
    std::cout << "  [PASS] testExtractSections\n";
}

void testParseComplete() {
    // TODO: 创建一个临时 SKILL.md 文件并测试完整解析
    std::cout << "  [SKIP] testParseComplete (需要文件 I/O)\n";
}

int run_skill_parser_tests() {
    std::cout << "Skill Parser Tests:\n";
    testParseFrontmatter();
    testExtractSections();
    testParseComplete();
    std::cout << "All skill parser tests passed.\n";
    return 0;
}
