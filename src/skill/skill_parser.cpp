// ClawLite — SKILL.md 解析器实现
// TODO: A 同学实现

#include "skill/skill_parser.h"
#include <fstream>
#include <sstream>

namespace clawlite {

std::optional<SkillDefinition> SkillParser::parse(const std::string& filePath) {
    // TODO: 实现
    // 1. 读取文件内容
    // 2. 调用 extractSections() 分离 frontmatter 和 body
    // 3. 调用 parseFrontmatter() 解析 KV 对
    // 4. 从 frontmatter 中提取 name 和 description
    // 5. 如果缺少 name 或 description，返回 nullopt
    return std::nullopt;
}

ParsedFrontmatter SkillParser::parseFrontmatter(const std::string& rawBlock) {
    // TODO: 实现双策略解析
    // 策略 1：行正则解析（parseByLine）
    //   逐行匹配 /^(\w[\w-]*):\s*(.+)$/ 格式
    //   支持多行值（缩进行拼接）
    // 策略 2：YAML 库解析（parseByYaml，如果链接了 yaml-cpp）
    //   用 yaml-cpp 解析整个 block
    // 合并：YAML 结果优先，但行正则在某些情况下更准确（参考 shouldPreferInlineLineValue）
    return parseByLine(rawBlock);
}

std::pair<std::string, std::string> SkillParser::extractSections(const std::string& content) {
    // TODO: 实现
    // 查找第一个 "---" 和第二个 "---" 之间的内容作为 frontmatter
    // 第二个 "---" 之后的内容作为 body
    // 参考标准 YAML frontmatter 格式
    return {"", ""};
}

ParsedFrontmatter SkillParser::parseByLine(const std::string& block) {
    // TODO: 实现
    // 逐行扫描，匹配 key: value 模式
    // 处理多行值（以空格或 tab 开头的行拼接到上一个 key）
    return {};
}

ParsedFrontmatter SkillParser::parseByYaml(const std::string& block) {
    // TODO: 实现（需要 yaml-cpp）
    // 用 YAML::Load(block) 解析
    // 遍历顶层 map，将所有值转为 string 存入 ParsedFrontmatter
    return {};
}

} // namespace clawlite
