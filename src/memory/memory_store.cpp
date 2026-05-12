// ClawLite — SQLite 存储层实现
// TODO: B 同学实现
// 这是工作量最大的文件，需要调用 SQLite C API

#include "memory/memory_store.h"

// TODO: #include "third_party/sqlite3/sqlite3.h"
// 如果用 vcpkg: #include <sqlite3.h>

namespace clawlite {

MemoryStore::MemoryStore() = default;
MemoryStore::~MemoryStore() { close(); }

bool MemoryStore::open(const std::string& dbPath) {
    // TODO: 实现
    // 1. sqlite3_open(dbPath, &m_db)
    // 2. 启用 WAL 模式：PRAGMA journal_mode=WAL
    // 3. 调用 createSchema() 和 createFtsTable()
    return false;
}

void MemoryStore::close() {
    // TODO: 实现
    // if (m_db) { sqlite3_close(m_db); m_db = nullptr; }
}

void MemoryStore::createSchema() {
    // TODO: 实现 — 创建 4 张表
    //
    // 参考：openclaw-main/packages/memory-host-sdk/host/memory-schema.ts:ensureMemoryIndexSchema
    //
    // CREATE TABLE IF NOT EXISTS meta (
    //     key TEXT PRIMARY KEY,
    //     value TEXT NOT NULL
    // );
    //
    // CREATE TABLE IF NOT EXISTS files (
    //     path TEXT PRIMARY KEY,
    //     source TEXT,
    //     hash TEXT,
    //     mtime INTEGER,
    //     size INTEGER
    // );
    //
    // CREATE TABLE IF NOT EXISTS chunks (
    //     id TEXT PRIMARY KEY,
    //     path TEXT,
    //     source TEXT,
    //     start_line INTEGER,
    //     end_line INTEGER,
    //     hash TEXT,
    //     text TEXT,
    //     embedding TEXT,  -- JSON 格式的向量
    //     updated_at INTEGER
    // );
    //
    // CREATE TABLE IF NOT EXISTS embedding_cache (
    //     provider TEXT,
    //     model TEXT,
    //     hash TEXT,
    //     embedding TEXT,
    //     dims INTEGER,
    //     updated_at INTEGER,
    //     PRIMARY KEY (provider, model, hash)
    // );
    //
    // CREATE INDEX IF NOT EXISTS idx_chunks_path ON chunks(path);
    // CREATE INDEX IF NOT EXISTS idx_chunks_source ON chunks(source);
}

void MemoryStore::createFtsTable() {
    // TODO: 实现 — 创建 FTS5 虚拟表
    //
    // CREATE VIRTUAL TABLE IF NOT EXISTS chunks_fts USING fts5(
    //     text, id, path, source,
    //     tokenize='unicode61'
    // );
    //
    // 注意：FTS5 需要 SQLite 编译时启用 -DSQLITE_ENABLE_FTS5
}

// ── 文件索引 ──────────────────────────────────────────────

void MemoryStore::upsertFile(const FileEntry& entry) {
    // TODO: 实现
    // INSERT OR REPLACE INTO files (path, hash, mtime, size) VALUES (?, ?, ?, ?)
}

void MemoryStore::removeFile(const std::string& path) {
    // TODO: 实现
    // DELETE FROM files WHERE path = ?
}

std::optional<FileEntry> MemoryStore::getFile(const std::string& path) {
    // TODO: 实现
    // SELECT path, hash, mtime, size FROM files WHERE path = ?
    return std::nullopt;
}

std::vector<FileEntry> MemoryStore::getAllFiles() {
    // TODO: 实现
    // SELECT path, hash, mtime, size FROM files
    return {};
}

// ── 块存储 ────────────────────────────────────────────────

void MemoryStore::upsertChunk(const MemoryChunk& chunk) {
    // TODO: 实现
    // 1. INSERT OR REPLACE INTO chunks (id, path, start_line, end_line, hash, text, embedding, updated_at)
    // 2. INSERT OR REPLACE INTO chunks_fts (text, id, path) — 同步 FTS 索引
    //
    // embedding 存储为 JSON 字符串: "[0.1, 0.2, 0.3, ...]"
}

void MemoryStore::removeChunksByFile(const std::string& path) {
    // TODO: 实现
    // DELETE FROM chunks WHERE path = ?
    // DELETE FROM chunks_fts WHERE path = ?
}

std::vector<MemoryChunk> MemoryStore::getAllChunks() {
    // TODO: 实现
    // SELECT id, path, start_line, end_line, hash, text, embedding FROM chunks
    return {};
}

std::vector<MemoryChunk> MemoryStore::getChunksByFile(const std::string& path) {
    // TODO: 实现
    return {};
}

// ── 全文搜索 ──────────────────────────────────────────────

std::vector<std::pair<std::string, double>> MemoryStore::ftsSearch(
    const std::string& query, int limit
) {
    // TODO: 实现 — FTS5 搜索
    //
    // SELECT id, bm25(chunks_fts) as score
    // FROM chunks_fts
    // WHERE chunks_fts MATCH ?
    // ORDER BY score
    // LIMIT ?
    //
    // 注意：FTS5 MATCH 语法，query 需要转义特殊字符
    // BM25 分数越小越好（负数），取反后越大越好
    return {};
}

// ── 嵌入缓存 ─────────────────────────────────────────────

void MemoryStore::cacheEmbedding(const std::string& hash,
                                  const std::string& provider,
                                  const std::string& model,
                                  const std::vector<double>& embedding) {
    // TODO: 实现
    // INSERT OR REPLACE INTO embedding_cache (provider, model, hash, embedding, dims, updated_at)
}

std::optional<std::vector<double>> MemoryStore::getCachedEmbedding(
    const std::string& hash,
    const std::string& provider,
    const std::string& model
) {
    // TODO: 实现
    // SELECT embedding FROM embedding_cache WHERE provider=? AND model=? AND hash=?
    return std::nullopt;
}

// ── 元数据 ────────────────────────────────────────────────

void MemoryStore::setMeta(const std::string& key, const std::string& value) {
    // TODO: 实现
    // INSERT OR REPLACE INTO meta (key, value) VALUES (?, ?)
}

std::optional<std::string> MemoryStore::getMeta(const std::string& key) {
    // TODO: 实现
    // SELECT value FROM meta WHERE key = ?
    return std::nullopt;
}

// ── 事务 ──────────────────────────────────────────────────

void MemoryStore::beginTransaction() {
    // TODO: sqlite3_exec(m_db, "BEGIN TRANSACTION", ...)
}

void MemoryStore::commit() {
    // TODO: sqlite3_exec(m_db, "COMMIT", ...)
}

void MemoryStore::rollback() {
    // TODO: sqlite3_exec(m_db, "ROLLBACK", ...)
}

int MemoryStore::fileCount() const {
    // TODO: SELECT COUNT(*) FROM files
    return 0;
}

int MemoryStore::chunkCount() const {
    // TODO: SELECT COUNT(*) FROM chunks
    return 0;
}

} // namespace clawlite
