// ClawLite — LLM HTTP 客户端实现
// TODO: C 同学实现

#include "llm/llm_client.h"
// TODO: #include <httplib.h>  // cpp-httplib

namespace clawlite {

LlmClient::LlmClient(const LlmConfig& config) : m_config(config) {}

LlmResponse LlmClient::chat(
    const std::vector<Message>& messages,
    const std::vector<Tool>& tools
) {
    // TODO: 实现同步 HTTP 调用
    //
    // 使用 cpp-httplib:
    //   httplib::Client client(m_config.baseUrl);
    //   client.set_bearer_token_auth(m_config.apiKey);
    //   auto res = client.Post("/v1/chat/completions", body, "application/json");
    //
    // 或使用 system("curl ...") 作为简化实现
    //
    // 请求体格式（OpenAI 兼容）：
    // {
    //   "model": "gpt-4o-mini",
    //   "messages": [
    //     {"role": "system", "content": "..."},
    //     {"role": "user", "content": "..."}
    //   ],
    //   "tools": [...],
    //   "temperature": 0.7,
    //   "max_tokens": 4096
    // }

    LlmResponse resp;
    resp.success = false;
    resp.error = "not implemented";
    return resp;
}

LlmResponse LlmClient::chatStream(
    const std::vector<Message>& messages,
    const std::vector<Tool>& tools,
    StreamCallback onToken
) {
    // TODO: 实现流式 SSE 调用
    //
    // 参考：openclaw-main/src/agents/pi-embedded-runner/run/attempt.ts
    //
    // 请求体中 "stream": true
    // 响应格式（Server-Sent Events）：
    //   data: {"id":"...","choices":[{"delta":{"content":"Hello"}}]}
    //   data: {"id":"...","choices":[{"delta":{"content":" world"}}]}
    //   data: {"id":"...","choices":[{"delta":{},"finish_reason":"stop"}]}
    //   data: [DONE]
    //
    // 解析状态机：
    //   逐行读取
    //   如果行以 "data: " 开头：
    //     如果是 "data: [DONE]" → 结束
    //     否则解析 JSON，提取 delta.content，调用 onToken()
    //   累积所有 delta.content 到最终响应

    LlmResponse resp;
    resp.success = false;
    resp.error = "not implemented";
    return resp;
}

std::string LlmClient::buildRequestJson(
    const std::vector<Message>& messages,
    const std::vector<Tool>& tools,
    bool stream
) {
    // TODO: 实现 JSON 构建
    //
    // 手动拼接 JSON 字符串（不依赖 JSON 库）
    // 或使用简单的 JSON 构建器
    //
    // 消息格式：
    // {"role":"user","content":"..."}
    // {"role":"assistant","content":"...","tool_calls":[...]}
    // {"role":"tool","tool_call_id":"...","content":"..."}
    //
    // 工具格式：
    // {"type":"function","function":{"name":"...","description":"...","parameters":{...}}}
    return "{}";
}

LlmResponse LlmClient::parseResponse(const std::string& json) {
    // TODO: 实现 JSON 解析
    //
    // 响应格式：
    // {
    //   "choices": [{
    //     "message": {
    //       "role": "assistant",
    //       "content": "Hello!",
    //       "tool_calls": [{
    //         "id": "call_xxx",
    //         "type": "function",
    //         "function": { "name": "xxx", "arguments": "{...}" }
    //       }]
    //     },
    //     "finish_reason": "stop"
    //   }],
    //   "usage": { "prompt_tokens": 100, "completion_tokens": 50 }
    // }
    LlmResponse resp;
    resp.success = false;
    resp.error = "not implemented";
    return resp;
}

LlmResponse LlmClient::parseSSEStream(const std::string& rawResponse, StreamCallback onToken) {
    // TODO: 实现 SSE 流解析 — 状态机
    //
    // 参考：openclaw-main/src/agents/pi-embedded-runner/run/attempt.ts
    //
    // 状态机：
    //   遍历 rawResponse 的每一行
    //   如果行以 "data: " 开头：
    //     data = line.substr(6)
    //     if data == "[DONE]": break
    //     解析 JSON data
    //     提取 choices[0].delta.content
    //     if content 非空: onToken(content); 累积到 response.content
    //     提取 choices[0].delta.tool_calls
    //     if tool_calls 非空: 累积到 response.toolCalls
    //     提取 choices[0].finish_reason
    //   否则跳过（空行或注释行）
    LlmResponse resp;
    resp.success = false;
    resp.error = "not implemented";
    return resp;
}

} // namespace clawlite
