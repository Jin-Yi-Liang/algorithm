# PTAL1101 别再来这么多猫娘了！

## 题目描述

文本审查：给定 N 个违禁词和阈值 k，检测文本中的违禁词：
- 违禁词数量 < k：替换为 `<censored>`
- 违禁词数量 ≥ k：输出违禁词数量和警告

**关键规则**：从左到右处理，违禁词按输入顺序依次处理，有重叠时从违禁词末尾继续

## 核心算法

**跳跃表（jump array）**：用 `jump[i]` 标记文本第 i 个字符是否已被某个违禁词覆盖（值为违禁词长度，0 表示未覆盖）

```cpp
vector<int> jump(text.size(), 0);

for (auto& word : words) {
    int idx = 0, len = word.length();
    while ((idx = text.find(word, idx)) != string::npos) {
        // 检查是否与已覆盖区域重叠
        bool overlap = false;
        for (int i = 0; i < len; ++i) {
            if (jump[idx + i] > 0) { overlap = true; break; }
        }
        if (!overlap) {
            ++count;  // 有效违禁词
            for (int i = 0; i < len; ++i) jump[idx + i] = len;
            idx += len;  // 跳到违禁词末尾
        } else {
            ++idx;  // 重叠，跳过第一个字符继续
        }
    }
}
```

## 替换输出

按 jump 表从左到右扫描：
- `jump[i] > 0`：输出 `<censored>`，跳 `jump[i]` 个字符
- 否则：输出原字符

## 关键点

- **重叠处理**：`find` 找到匹配后，若与已覆盖区域重叠，只跳过第一个字符继续找（不计数）
- **一次覆盖**：一个字符只能被一个违禁词覆盖，后续违禁词遇到已覆盖区域跳过
- **jump 跳转**：替换时遇到已标记区域直接跳过去，避免重复输出
