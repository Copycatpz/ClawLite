// ClawLite — 混合检索管理器实现
// TODO: B 同学实现 — 数据结构课程重点！

#include "memory/search_manager.h"
#include <algorithm>
#include <unordered_map>

namespace clawlite {

SearchManager::SearchManager(MemoryStore& store, std::unique_ptr<IEmbeddingProvider> embedding)
    : m_store(store), m_embedding(std::move(embedding)) {}

std::vector<SearchResult> SearchManager::search(
    const std::string& query,
    const SearchConfig& config
) {
    // TODO: 实现 — 混合搜索算法
    //
    // 参考：openclaw-main/packages/memory-host-sdk/host/types.ts:search
    //
    // 步骤：
    //   1. vectorResults = vectorSearch(query, config.vectorCandidateLimit)
    //   2. textResults = ftsSearch(query, config.ftsCandidateLimit)
    //   3. merged = mergeResults(vectorResults, textResults, config.vectorWeight, config.textWeight)
    //   4. sort merged by score descending
    //   5. return top config.topK

    auto vectorResults = vectorSearch(query, config.vectorCandidateLimit);
    auto textResults = ftsSearch(query, config.ftsCandidateLimit);
    auto merged = mergeResults(vectorResults, textResults, config.vectorWeight, config.textWeight);

    // 按分数降序排序
    std::sort(merged.begin(), merged.end(),
        [](const SearchResult& a, const SearchResult& b) {
            return a.score > b.score;
        });

    // 取 top-k
    if ((int)merged.size() > config.topK) {
        merged.resize(config.topK);
    }
    return merged;
}

std::vector<SearchResult> SearchManager::vectorSearch(const std::string& query, int topK) {
    // TODO: 实现 — 向量搜索
    //
    // 算法：
    //   1. queryEmbedding = m_embedding->embedQuery(query)
    //   2. allChunks = m_store.getAllChunks()
    //   3. 对每个 chunk:
    //      score = cosineSimilarity(queryEmbedding, chunk.embedding)
    //   4. 按 score 降序排序
    //   5. 取 top-k
    //
    // 这是暴力遍历 + 排序，适合小规模数据
    // 大规模数据需要 ANN 索引（如 HNSW），但对课程作业来说暴力搜索足够
    return {};
}

std::vector<SearchResult> SearchManager::ftsSearch(const std::string& query, int topK) {
    // TODO: 实现 — FTS5 全文搜索
    //
    // 算法：
    //   1. ftsResults = m_store.ftsSearch(query, topK)
    //   2. 对每个结果，从 chunks 表获取完整信息
    //   3. 构造 SearchResult（textScore = BM25 分数归一化后的值）
    return {};
}

std::vector<SearchResult> SearchManager::mergeResults(
    const std::vector<SearchResult>& vectorResults,
    const std::vector<SearchResult>& textResults,
    double vectorWeight,
    double textWeight
) {
    // TODO: 实现 — 结果合并算法
    //
    // 算法：
    //   1. 归一化两个列表的分数到 [0, 1]
    //   2. 用 unordered_map<string, SearchResult> 按 path+line 去重
    //   3. 向量结果：score = vectorWeight * normalizedScore
    //   4. 全文结果：score = textWeight * normalizedScore
    //   5. 如果同一个 chunk 在两个列表中都出现，分数相加
    //   6. 返回合并后的列表
    return {};
}

void SearchManager::normalizeScores(std::vector<SearchResult>& results) {
    // TODO: 实现分数归一化
    // 找到 maxScore，然后每个分数 /= maxScore
    if (results.empty()) return;
    double maxScore = 0;
    for (const auto& r : results) {
        if (r.score > maxScore) maxScore = r.score;
    }
    if (maxScore > 0) {
        for (auto& r : results) {
            r.score /= maxScore;
        }
    }
}

} // namespace clawlite
