// ClawLite — 技能注册表实现
// TODO: A 同学实现

#include "skill/skill_registry.h"
#include <algorithm>

namespace clawlite {

void SkillRegistry::loadFromWorkspace(const std::string& workspaceDir) {
    // TODO: 实现
    // 1. 获取默认目录列表
    // 2. 调用 SkillLoader::loadAndMerge() 加载并合并
    // 3. 将结果存入 m_skills
    auto dirs = SkillLoader::getDefaultDirs(workspaceDir);
    auto entries = SkillLoader::loadAndMerge(dirs);
    for (auto& entry : entries) {
        m_skills[entry.definition.name] = std::move(entry);
    }
}

void SkillRegistry::registerSkill(const SkillEntry& entry) {
    m_skills[entry.definition.name] = entry;
}

std::vector<SkillEntry> SkillRegistry::getActiveSkills() const {
    std::vector<SkillEntry> result;
    result.reserve(m_skills.size());
    for (const auto& [name, entry] : m_skills) {
        result.push_back(entry);
    }
    return result;
}

const SkillEntry* SkillRegistry::findSkill(const std::string& name) const {
    auto it = m_skills.find(name);
    if (it != m_skills.end()) return &it->second;
    return nullptr;
}

std::string SkillRegistry::buildSkillPrompt(int charBudget) const {
    // TODO: 实现 — 这是数据结构课程重点！
    //
    // 算法：
    //   1. 获取所有技能，按 name 排序（locale-aware）
    //   2. 先尝试完整格式（name + description + path），拼接为 XML
    //   3. 如果超过预算，尝试紧凑格式（仅 name + path）
    //   4. 如果仍然超过预算，用二分搜索找到最大前缀
    //
    // 参考：openclaw-main/src/agents/skills/workspace.ts:resolveWorkspaceSkillPromptState
    //   完整格式：<available_skills><skill><name>...<description>...<location>...
    //   紧凑格式：仅 <name> 和 <location>
    //   二分搜索：applySkillsPromptLimits (line 888-900)
    //
    // XML 输出格式示例：
    // <available_skills>
    //   <skill>
    //     <name>weather</name>
    //     <description>Get weather information</description>
    //     <location>skills/weather/SKILL.md</location>
    //   </skill>
    //   ...
    // </available_skills>

    auto skills = getActiveSkills();

    // 按 name 排序
    std::sort(skills.begin(), skills.end(),
        [](const SkillEntry& a, const SkillEntry& b) {
            return a.definition.name < b.definition.name;
        });

    // TODO: 实现完整格式 → 紧凑格式 → 二分裁剪的降级逻辑
    std::string prompt = "<available_skills>\n";
    for (const auto& skill : skills) {
        prompt += formatSkillXml(skill, false);
    }
    prompt += "</available_skills>\n";
    return prompt;
}

size_t SkillRegistry::size() const {
    return m_skills.size();
}

void SkillRegistry::clear() {
    m_skills.clear();
}

int SkillRegistry::binarySearchPromptLimit(
    const std::vector<SkillEntry>& sorted,
    int charBudget
) {
    // TODO: 实现二分搜索 — 数据结构课程重点！
    //
    // 目标：在 sorted 数组中找到最大的 k，使得前 k 个技能的提示词总长度 <= charBudget
    //
    // 算法：
    //   int lo = 0, hi = sorted.size();
    //   while (lo < hi) {
    //       int mid = (lo + hi + 1) / 2;
    //       if (totalChars(sorted, mid) <= charBudget) lo = mid;
    //       else hi = mid - 1;
    //   }
    //   return lo;
    return 0;
}

std::string SkillRegistry::formatSkillXml(const SkillEntry& entry, bool compact) {
    // TODO: 实现 XML 格式化
    // compact = true: 仅 <name> 和 <location>
    // compact = false: <name> + <description> + <location>
    std::string xml = "  <skill>\n";
    xml += "    <name>" + entry.definition.name + "</name>\n";
    if (!compact) {
        xml += "    <description>" + entry.definition.description + "</description>\n";
    }
    xml += "    <location>" + entry.definition.filePath + "</location>\n";
    xml += "  </skill>\n";
    return xml;
}

} // namespace clawlite
