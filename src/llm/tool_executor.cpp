// ClawLite — 工具注册与执行实现
// TODO: C 同学实现

#include "llm/tool_executor.h"
#include <ctime>

namespace clawlite {

void ToolExecutor::registerTool(const Tool& tool) {
    m_tools[tool.name] = tool;
}

void ToolExecutor::registerBuiltinTools() {
    // 注册内置工具
    Tool calc;
    calc.name = "calculator";
    calc.description = "Evaluate a mathematical expression. Returns the result as text.";
    calc.parametersJson = R"({"type":"object","properties":{"expr":{"type":"string","description":"Mathematical expression to evaluate"}},"required":["expr"]})";
    calc.handler = toolCalculator;
    registerTool(calc);

    Tool time;
    time.name = "current_time";
    time.description = "Get the current date and time.";
    time.parametersJson = R"({"type":"object","properties":{}})";
    time.handler = toolCurrentTime;
    registerTool(time);

    Tool readFile;
    readFile.name = "read_file";
    readFile.description = "Read the contents of a text file.";
    readFile.parametersJson = R"({"type":"object","properties":{"path":{"type":"string","description":"File path to read"}},"required":["path"]})";
    readFile.handler = toolReadFile;
    registerTool(readFile);
}

ToolResult ToolExecutor::execute(const ToolCall& toolCall) {
    // TODO: 实现工具执行
    //
    // 参考：openclaw-main/src/agents/tools/common.ts — tool execution
    //
    // 算法：
    //   1. 查找 m_tools[toolCall.name]
    //   2. 如果未找到，返回 ToolResult{false, "", "tool not found: " + name}
    //   3. 调用 handler(toolCall.arguments)
    //   4. 返回 ToolResult{true, output, ""}

    auto it = m_tools.find(toolCall.name);
    if (it == m_tools.end()) {
        return {false, "", "tool not found: " + toolCall.name};
    }

    if (!it->second.handler) {
        return {false, "", "tool has no handler: " + toolCall.name};
    }

    ToolResult result;
    try {
        result.output = it->second.handler(toolCall.arguments);
        result.success = true;
    } catch (const std::exception& e) {
        result.success = false;
        result.error = e.what();
    }
    return result;
}

std::vector<Tool> ToolExecutor::getAllTools() const {
    std::vector<Tool> tools;
    tools.reserve(m_tools.size());
    for (const auto& [name, tool] : m_tools) {
        tools.push_back(tool);
    }
    return tools;
}

bool ToolExecutor::hasTool(const std::string& name) const {
    return m_tools.find(name) != m_tools.end();
}

size_t ToolExecutor::size() const {
    return m_tools.size();
}

// ── 内置工具实现 ──────────────────────────────────────────

std::string toolCalculator(const std::string& argsJson) {
    // TODO: 实现简单计算器
    // 从 argsJson 中提取 "expr" 字段
    // 支持 +, -, *, / 基本运算
    // 返回计算结果字符串
    //
    // 简化实现：用 system() 或手动解析表达式
    return "Calculator not implemented yet";
}

std::string toolCurrentTime(const std::string& argsJson) {
    // 获取当前时间
    time_t now = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

std::string toolReadFile(const std::string& argsJson) {
    // TODO: 实现文件读取
    // 从 argsJson 中提取 "path" 字段
    // 读取文件内容（限制大小，如 10KB）
    // 返回文件内容
    return "File reading not implemented yet";
}

} // namespace clawlite
