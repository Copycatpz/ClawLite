// ClawLite — 上下文引擎实现
// TODO: B 同学实现
// 这是 IContextEngine 的具体实现，组合 MemoryStore + Chunker + SearchManager + SessionStore

#include "memory/context_engine.h"
// TODO: #include 具体实现类

namespace clawlite {

// TODO: 实现 IContextEngine 的所有虚函数
// 组合以下组件：
//   MemoryStore m_store;         — SQLite 存储
//   SearchManager m_search;      — 混合检索
//   SessionStore m_sessions;     — 会话管理
//
// initialize():
//   1. m_store.open(dataDir + "/clawlite.db")
//   2. 创建 SearchManager
//
// indexFile():
//   1. 读取文件内容
//   2. 调用 Chunker::chunkMarkdown() 分块
//   3. 调用 m_embedding->embedBatch() 计算嵌入
//   4. 写入 m_store（upsertFile + upsertChunk）
//
// ingest():
//   1. m_sessions.appendMessage(sessionKey, msg)
//
// assemble():
//   1. m_sessions.getHistory() 获取最近对话
//   2. m_search.search() 搜索相关记忆
//   3. 合并去重
//   4. 裁剪到 tokenBudget
//
// compact():
//   1. 调用 Compactor::compact()
//
// search():
//   1. 调用 m_search.search()

} // namespace clawlite
