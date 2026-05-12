#pragma once
// ClawLite — 技能注册表
// 参考：openclaw-main/src/agents/skills/workspace.ts:resolveWorkspaceSkillPromptState
// 数据结构：unordered_map<string, SkillEntry> 按 name 索引
// 算法：排序 + 二分搜索裁剪（字符预算内尽可能多的技能）

#include "skill/skill_loader.h"
#include <vector>
#include <string>
#include <functional>

namespace clawlite {

class SkillRegistry {
public:
    SkillRegistry() = default;

    // 加载并注册技能（调用 SkillLoader::loadAndMerge）
    void loadFromWorkspace(const std::string& workspaceDir);

    // 手动注册一个技能
    void registerSkill(const SkillEntry& entry);

    // 获取所有活跃技能
    std::vector<SkillEntry> getActiveSkills() const;

    // 按 name 查找技能
    const SkillEntry* findSkill(const std::string& name) const;

    // 构建技能提示词（XML 格式，带字符预算裁剪）
    // 参考：openclaw-main/src/agents/skills/workspace.ts:resolveWorkspaceSkillPromptState
    // 算法：先尝试完整格式，超预算则用紧凑格式（仅 name+path），
    //       仍然超预算则用二分搜索找到最大前缀
    // 这是数据结构课程重点！
    std::string buildSkillPrompt(int charBudget = 18000) const;

    // 获取技能数量
    size_t size() const;

    // 清空
    void clear();

private:
    // 数据结构：HashMap 按 name 索引
    std::unordered_map<std::string, SkillEntry> m_skills;

    // 二分搜索：在排序后的技能列表中，找到不超过字符预算的最大前缀长度
    // 参考：openclaw-main/src/agents/skills/workspace.ts:applySkillsPromptLimits (line 888-900)
    static int binarySearchPromptLimit(
        const std::vector<SkillEntry>& sorted,
        int charBudget
    );

    // 格式化单个技能为 XML
    static std::string formatSkillXml(const SkillEntry& entry, bool compact = false);
};

} // namespace clawlite
