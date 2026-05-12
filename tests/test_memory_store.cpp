// ClawLite — SQLite 存储层测试
// TODO: B 同学补充测试用例

#include "memory/memory_store.h"
#include <iostream>
#include <cassert>
#include <cstdio>

using namespace clawlite;

void testOpenClose() {
    MemoryStore store;
    bool ok = store.open(":memory:");
    assert(ok);
    store.close();
    std::cout << "  [PASS] testOpenClose\n";
}

void testFileCrud() {
    MemoryStore store;
    store.open(":memory:");

    FileEntry entry;
    entry.path = "test.md";
    entry.hash = "abc123";
    entry.mtimeMs = 1000;
    entry.size = 500;

    store.upsertFile(entry);
    assert(store.fileCount() == 1);

    auto got = store.getFile("test.md");
    assert(got.has_value());
    assert(got->path == "test.md");
    assert(got->hash == "abc123");

    store.removeFile("test.md");
    assert(store.fileCount() == 0);

    store.close();
    std::cout << "  [PASS] testFileCrud\n";
}

void testChunkCrud() {
    MemoryStore store;
    store.open(":memory:");

    MemoryChunk chunk;
    chunk.path = "test.md";
    chunk.startLine = 1;
    chunk.endLine = 10;
    chunk.text = "Hello world";
    chunk.hash = "def456";

    store.upsertChunk(chunk);
    assert(store.chunkCount() == 1);

    auto chunks = store.getChunksByFile("test.md");
    assert(chunks.size() == 1);
    assert(chunks[0].text == "Hello world");

    store.removeChunksByFile("test.md");
    assert(store.chunkCount() == 0);

    store.close();
    std::cout << "  [PASS] testChunkCrud\n";
}

void testFtsSearch() {
    // TODO: 测试 FTS5 全文搜索
    // 需要 SQLite 编译时启用 FTS5
    std::cout << "  [SKIP] testFtsSearch (需要 FTS5 支持)\n";
}

void testEmbeddingCache() {
    MemoryStore store;
    store.open(":memory:");

    std::vector<double> embedding = {0.1, 0.2, 0.3};
    store.cacheEmbedding("hash1", "local", "mock", embedding);

    auto cached = store.getCachedEmbedding("hash1", "local", "mock");
    assert(cached.has_value());
    assert(cached->size() == 3);
    assert((*cached)[0] == 0.1);

    store.close();
    std::cout << "  [PASS] testEmbeddingCache\n";
}

int run_memory_store_tests() {
    std::cout << "Memory Store Tests:\n";
    testOpenClose();
    testFileCrud();
    testChunkCrud();
    testFtsSearch();
    testEmbeddingCache();
    std::cout << "All memory store tests passed.\n";
    return 0;
}
