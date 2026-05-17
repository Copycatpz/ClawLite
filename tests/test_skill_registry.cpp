// ClawLite — 技能注册表测试
// TODO: A 同学补充测试用例

#include "skill/skill_registry.h"
#include "test_helpers.h"
#include <iostream>

using namespace clawlite;

void testRegisterAndFind() {
    SkillRegistry registry;

    SkillEntry entry;
    entry.definition.name = "test_skill";
    entry.definition.description = "A test skill";
    entry.definition.filePath = "skills/test/SKILL.md";
    entry.source = SkillSource::Builtin;

    registry.registerSkill(entry);
    TEST_ASSERT(registry.size() == 1);

    auto found = registry.findSkill("test_skill");
    TEST_ASSERT(found != nullptr);
    TEST_ASSERT(found->definition.name == "test_skill");

    TEST_ASSERT(registry.findSkill("nonexistent") == nullptr);
    std::cout << "  [PASS] testRegisterAndFind\n";
}

void testBuildSkillPrompt() {
    SkillRegistry registry;

    for (int i = 0; i < 5; i++) {
        SkillEntry entry;
        entry.definition.name = "skill_" + std::to_string(i);
        entry.definition.description = "Description " + std::to_string(i);
        entry.definition.filePath = "skills/skill_" + std::to_string(i) + "/SKILL.md";
        entry.source = SkillSource::Builtin;
        registry.registerSkill(entry);
    }

    std::string prompt = registry.buildSkillPrompt(18000);
    TEST_ASSERT(!prompt.empty());
    TEST_ASSERT(prompt.find("<available_skills>") != std::string::npos);
    TEST_ASSERT(prompt.find("skill_0") != std::string::npos);
    std::cout << "  [PASS] testBuildSkillPrompt\n";
}

void testBinarySearchPromptLimit() {
    // TODO: 测试二分搜索裁剪
    // 创建大量技能，设置小预算，验证裁剪结果
    std::cout << "  [SKIP] testBinarySearchPromptLimit (需要实现)\n";
}

int run_skill_registry_tests() {
    std::cout << "Skill Registry Tests:\n";
    RESET_FAILURES();
    testRegisterAndFind();
    testBuildSkillPrompt();
    testBinarySearchPromptLimit();
    int f = GET_FAILURES();
    if (f == 0) std::cout << "All skill registry tests passed.\n";
    else std::cout << f << " skill registry test(s) failed.\n";
    return f;
}
