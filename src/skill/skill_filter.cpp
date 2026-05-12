// ClawLite — 技能资格过滤器实现
// TODO: A 同学实现

#include "skill/skill_filter.h"
#include <cstdlib>

namespace clawlite {

bool SkillFilter::isEligible(const SkillDefinition& skill, const SkillFilterConfig& config) {
    // TODO: 实现资格检查
    // 1. OS 检查：frontmatter 中的 "os" 字段是否包含当前 OS
    // 2. 二进制检查：frontmatter 中的 "requires.bins" 是否都在 availableBins 中
    // 3. 环境变量检查：frontmatter 中的 "requires.env" 是否都在 availableEnvs 中
    //
    // 参考：openclaw-main/src/agents/skills/config.ts:shouldIncludeSkill
    return checkOs(skill, config.os)
        && checkBins(skill, config.availableBins)
        && checkEnvs(skill, config.availableEnvs);
}

std::vector<SkillEntry> SkillFilter::filterSkills(
    const std::vector<SkillEntry>& skills,
    const SkillFilterConfig& config
) {
    // TODO: 实现
    std::vector<SkillEntry> result;
    for (const auto& entry : skills) {
        if (isEligible(entry.definition, config)) {
            result.push_back(entry);
        }
    }
    return result;
}

SkillFilterConfig SkillFilter::detectSystem() {
    // TODO: 实现系统检测
    SkillFilterConfig config;

    // 检测 OS
    #if defined(_WIN32)
        config.os = "windows";
    #elif defined(__APPLE__)
        config.os = "macos";
    #elif defined(__linux__)
        config.os = "linux";
    #endif

    // 检测可用二进制（用 system("which xxx") 或 std::filesystem::path 查找）
    // TODO: 常用命令检测：curl, python, git 等

    // 检测环境变量
    // TODO: 遍历常见环境变量名

    return config;
}

bool SkillFilter::checkOs(const SkillDefinition& skill, const std::string& currentOs) {
    // TODO: 实现
    // 如果技能没有指定 os 要求，则默认兼容所有 OS
    auto it = skill.frontmatter.find("os");
    if (it == skill.frontmatter.end()) return true;
    // 检查 currentOs 是否在 os 列表中（逗号分隔）
    return true;  // 暂时返回 true
}

bool SkillFilter::checkBins(const SkillDefinition& skill, const std::set<std::string>& available) {
    // TODO: 实现
    // 从 frontmatter 中解析 requires.bins（JSON 数组格式）
    // 检查每个 bin 是否在 available 集合中
    return true;  // 暂时返回 true
}

bool SkillFilter::checkEnvs(const SkillDefinition& skill, const std::set<std::string>& available) {
    // TODO: 实现
    // 从 frontmatter 中解析 requires.env（JSON 数组格式）
    // 检查每个 env 是否在 available 集合中
    return true;  // 暂时返回 true
}

} // namespace clawlite
