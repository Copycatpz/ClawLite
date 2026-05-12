// ClawLite — 技能加载器实现
// TODO: A 同学实现

#include "skill/skill_loader.h"
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

namespace clawlite {

std::vector<SkillEntry> SkillLoader::loadFromDir(const std::string& dir, SkillSource source) {
    // TODO: 实现
    // 1. 检查目录是否存在
    // 2. 遍历子目录，每个子目录找 SKILL.md
    // 3. 调用 SkillParser::parse() 解析
    // 4. 过滤掉解析失败的（无 name/description）
    // 5. 返回 vector<SkillEntry>
    //
    // 参考：openclaw-main/src/agents/skills/local-loader.ts:loadSkillsFromDirSafe
    // 注意：用 isSafePath() 防止路径穿越
    return {};
}

std::vector<SkillEntry> SkillLoader::loadAndMerge(
    const std::vector<std::pair<std::string, SkillSource>>& dirs
) {
    // TODO: 实现多源加载与优先级合并
    // 数据结构：unordered_map<string, SkillEntry> 按 name 去重
    //
    // 算法：
    //   1. 按 SkillSource 从小到大排序（低优先级先加载）
    //   2. 对每个目录调用 loadFromDir()
    //   3. 结果插入 map，已存在则检查优先级，高优先级覆盖低优先级
    //   4. 最终 map 的 values 就是合并结果
    //
    // 参考：openclaw-main/src/agents/skills/workspace.ts:loadSkillEntries
    //   merged: Map<string, LoadedSkillRecord> 按 name 去重
    return {};
}

std::vector<std::pair<std::string, SkillSource>> SkillLoader::getDefaultDirs(
    const std::string& workspaceDir
) {
    // 返回默认搜索目录列表（按优先级从低到高）
    std::vector<std::pair<std::string, SkillSource>> dirs;

    // 1. 内置技能（最低优先级）
    dirs.push_back({workspaceDir + "/skills", SkillSource::Builtin});

    // 2. 用户技能
    // TODO: 获取用户主目录，拼接 ~/.clawlite/skills
    // dirs.push_back({homeDir + "/.clawlite/skills", SkillSource::User});

    // 3. 项目技能（最高优先级）
    dirs.push_back({workspaceDir + "/skills", SkillSource::Project});

    return dirs;
}

bool SkillLoader::isSafePath(const std::string& path, const std::string& root) {
    // TODO: 实现路径安全检查
    // 防止路径穿越（如 ../../../etc/passwd）
    // 检查：规范化后的路径是否以 root 开头
    try {
        auto canonical = fs::canonical(path);
        auto canonicalRoot = fs::canonical(root);
        auto canonicalStr = canonical.string();
        auto rootStr = canonicalRoot.string();
        return canonicalStr.substr(0, rootStr.size()) == rootStr;
    } catch (...) {
        return false;
    }
}

} // namespace clawlite
