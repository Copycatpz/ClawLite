// ClawLite — 向量嵌入实现
// TODO: B 同学实现

#include "memory/embedding.h"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <functional>

namespace clawlite {

// ── LocalMockEmbedding ────────────────────────────────────

LocalMockEmbedding::LocalMockEmbedding(int dims) : m_dims(dims) {}

std::vector<double> LocalMockEmbedding::embedQuery(const std::string& text) {
    return textToVector(text);
}

std::vector<std::vector<double>> LocalMockEmbedding::embedBatch(
    const std::vector<std::string>& texts
) {
    std::vector<std::vector<double>> results;
    results.reserve(texts.size());
    for (const auto& text : texts) {
        results.push_back(textToVector(text));
    }
    return results;
}

int LocalMockEmbedding::dimensions() const { return m_dims; }
std::string LocalMockEmbedding::id() const { return "local-mock"; }

std::vector<double> LocalMockEmbedding::textToVector(const std::string& text) {
    // TODO: 实现 — 基于字符频率的简单向量化
    //
    // 算法：
    //   1. 初始化 m_dims 维零向量
    //   2. 遍历文本的每个字符
    //   3. 用 hash(ch) % m_dims 确定位置
    //   4. 在该位置累加
    //   5. L2 归一化
    //
    // 这不是真正的语义嵌入，但足以演示向量搜索流程
    // 真正的实现应该调用 OpenAI / 本地模型的 embedding API

    std::vector<double> vec(m_dims, 0.0);

    for (size_t i = 0; i < text.size(); i++) {
        unsigned char ch = static_cast<unsigned char>(text[i]);
        int idx = (ch * 31 + static_cast<int>(i)) % m_dims;
        if (idx < 0) idx += m_dims;
        vec[idx] += 1.0;
    }

    // L2 归一化
    double norm = 0.0;
    for (double v : vec) norm += v * v;
    norm = std::sqrt(norm);
    if (norm > 0) {
        for (double& v : vec) v /= norm;
    }

    return vec;
}

// ── 余弦相似度 ────────────────────────────────────────────

double cosineSimilarity(const std::vector<double>& a, const std::vector<double>& b) {
    // TODO: 实现 — 数据/线性代数课程重点！
    //
    // 参考：openclaw-main/packages/memory-host-sdk/host/internal.ts:cosineSimilarity
    //
    // 公式：cos(a, b) = dot(a, b) / (||a|| * ||b||)
    //
    // 实现：
    //   if (a.size() != b.size()) return 0.0;
    //   double dot = 0, normA = 0, normB = 0;
    //   for (int i = 0; i < a.size(); i++) {
    //       dot   += a[i] * b[i];
    //       normA += a[i] * a[i];
    //       normB += b[i] * b[i];
    //   }
    //   if (normA == 0 || normB == 0) return 0.0;
    //   return dot / (sqrt(normA) * sqrt(normB));

    if (a.size() != b.size() || a.empty()) return 0.0;

    double dot = 0.0, normA = 0.0, normB = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        dot   += a[i] * b[i];
        normA += a[i] * a[i];
        normB += b[i] * b[i];
    }
    if (normA == 0.0 || normB == 0.0) return 0.0;
    return dot / (std::sqrt(normA) * std::sqrt(normB));
}

} // namespace clawlite
