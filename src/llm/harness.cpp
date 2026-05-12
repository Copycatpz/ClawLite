// ClawLite — Agent 主循环实现
// TODO: C 同学实现 — 数据结构课程重点（状态机）！

#include "llm/harness.h"

namespace clawlite {

AgentHarness::AgentHarness(
    LlmClient& llm,
    ToolExecutor& tools,
    IContextEngine* memory
) : m_llm(llm), m_tools(tools), m_memory(memory) {}

RunResult AgentHarness::runTurn(
    const std::string& systemPrompt,
    const std::vector<Message>& history,
    const std::string& userInput,
    const RuntimePlan& plan
) {
    // TODO: 实现 — Agent 主循环状态机！
    //
    // 参考：openclaw-main/src/agents/pi-embedded-runner/run/attempt.ts
    //
    // 这是整个项目最核心的算法，一定要实现好！
    //
    // 伪代码：
    //   RunResult result;
    //   m_state = AgentState::Idle;
    //
    //   // 构建完整消息列表
    //   vector<Message> messages;
    //   messages.push_back(Message::system(systemPrompt));
    //   messages.insert(messages.end(), history.begin(), history.end());
    //   messages.push_back(Message::user(userInput));
    //
    //   int roundCount = 0;
    //
    //   while (m_state != AgentState::Done && m_state != AgentState::Error) {
    //       switch (m_state) {
    //           case AgentState::Idle:
    //               m_state = AgentState::Thinking;
    //               break;
    //
    //           case AgentState::Thinking: {
    //               // 调用 LLM
    //               auto tools = m_tools.getAllTools();
    //               LlmResponse resp = m_llm.chat(messages, tools);
    //
    //               if (!resp.success) {
    //                   result.status = RunStatus::Error;
    //                   result.error = resp.error;
    //                   m_state = AgentState::Error;
    //                   break;
    //               }
    //
    //               // 将助手回复加入消息列表
    //               Message assistantMsg = Message::assistant(resp.content);
    //               assistantMsg.toolCalls = resp.toolCalls;
    //               messages.push_back(assistantMsg);
    //
    //               if (!resp.toolCalls.empty()) {
    //                   m_state = AgentState::ToolCalling;
    //               } else {
    //                   result.reply = resp.content;
    //                   m_state = AgentState::Responding;
    //               }
    //               break;
    //           }
    //
    //           case AgentState::ToolCalling: {
    //               roundCount++;
    //               if (roundCount >= plan.transport.maxToolRounds) {
    //                   result.status = RunStatus::MaxTurnsExceeded;
    //                   result.error = "max tool rounds exceeded";
    //                   m_state = AgentState::Error;
    //                   break;
    //               }
    //
    //               // 执行所有工具调用
    //               const auto& toolCalls = messages.back().toolCalls;
    //               for (const auto& tc : toolCalls) {
    //                   ToolResult tr = m_tools.execute(tc);
    //                   messages.push_back(Message::toolResult(
    //                       tc.id, tc.name, tr.output
    //                   ));
    //               }
    //
    //               m_state = AgentState::Thinking;  // 回到 Thinking 继续循环
    //               break;
    //           }
    //
    //           case AgentState::Responding:
    //               result.status = RunStatus::Success;
    //               result.totalTurns = roundCount;
    //               m_state = AgentState::Done;
    //               break;
    //
    //           default:
    //               m_state = AgentState::Error;
    //               break;
    //       }
    //   }
    //
    //   m_state = AgentState::Idle;
    //   return result;

    RunResult result;
    result.status = RunStatus::Error;
    result.error = "not implemented";
    return result;
}

} // namespace clawlite
