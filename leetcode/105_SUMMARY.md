# 从前序与中序遍历构造二叉树 - 完整总结

## 📚 算法核心 (Algorithm Core)

### 遍历特性 (Traversal Properties)

| 遍历方式 | 顺序 | 根节点位置 |
|---------|------|----------|
| **前序 (Preorder)** | `[根, 左子树, 右子树]` | **第一个** |
| **中序 (Inorder)** | `[左子树, 根, 右子树]` | **中间** |
| **后序 (Postorder)** | `[左子树, 右子树, 根]` | **最后** |

---

## 🎯 算法步骤 (Algorithm Steps)

```
对于当前范围的 preorder 和 inorder:

1. 根节点 = preorder[0]

2. 在 inorder 中找到根节点位置 → 分割左右子树
   inorder = [左子树, 根, 右子树]
              ↑      ↑    ↑
           left    root  right

3. 计算左子树大小 = root在inorder中的位置 - 左边界

4. 根据左子树大小，在 preorder 中定位左右子树范围
   preorder = [根, 左子树(n个), 右子树]
               ↑   ↑          ↑
              root left      right

5. 递归构建左子树和右子树
```

---

## 💻 核心代码 (Core Code)

```python
def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
    # 哈希表: 快速查找根节点在中序中的位置
    inorder_map = {val: idx for idx, val in enumerate(inorder)}
    
    def build(pre_left, pre_right, in_left, in_right):
        if pre_left > pre_right:
            return None
        
        # 1. 根节点 = 前序第一个
        root_val = preorder[pre_left]
        root = TreeNode(root_val)
        
        # 2. 在中序中找到根节点
        root_idx = inorder_map[root_val]
        
        # 3. 计算左子树大小
        left_size = root_idx - in_left
        
        # 4. 递归构建左右子树
        root.left = build(
            pre_left + 1,              # 左子树前序起点
            pre_left + left_size,      # 左子树前序终点
            in_left,                   # 左子树中序起点
            root_idx - 1               # 左子树中序终点
        )
        
        root.right = build(
            pre_left + left_size + 1,  # 右子树前序起点
            pre_right,                 # 右子树前序终点
            root_idx + 1,              # 右子树中序起点
            in_right                   # 右子树中序终点
        )
        
        return root
    
    return build(0, len(preorder) - 1, 0, len(inorder) - 1)
```

---

## 📊 复杂度分析 (Complexity)

| 项目 | 复杂度 | 说明 |
|-----|-------|------|
| **时间** | O(n) | 每个节点访问一次，哈希表查找O(1) |
| **空间** | O(n) | 递归栈O(h) + 哈希表O(n) = O(n) |

---

## 🔑 关键点 (Key Points)

### 1. 索引计算最重要!

```python
# 左子树大小
left_size = root_idx_in_inorder - in_left

# 左子树在前序中的范围
left_pre_start = pre_left + 1              # 跳过根节点
left_pre_end = pre_left + left_size        # 加上左子树大小

# 右子树在前序中的范围  
right_pre_start = pre_left + left_size + 1  # 左子树后面
right_pre_end = pre_right                   # 到末尾
```

### 2. 使用哈希表优化查找

```python
# ❌ 慢: 每次 O(n) 查找
root_idx = inorder.index(root_val)

# ✅ 快: O(1) 查找
inorder_map = {val: idx for idx, val in enumerate(inorder)}
root_idx = inorder_map[root_val]
```

### 3. 使用索引而不是切片

```python
# ❌ 低效: 创建新数组
left_pre = preorder[1:left_size+1]
self.buildTree(left_pre, left_in)

# ✅ 高效: 传递索引
self.build(pre_left+1, pre_left+left_size, in_left, root_idx-1)
```

---

## 🎨 可视化例子 (Visual Example)

```
preorder = [1, 2, 4, 5, 3, 6, 7]
inorder  = [4, 2, 5, 1, 6, 3, 7]

步骤1: 根节点 = 1
       inorder: [4,2,5 | 1 | 6,3,7]
                 左子树    右子树

步骤2: 左子树根 = 2
       inorder: [4 | 2 | 5]

步骤3: 右子树根 = 3
       inorder: [6 | 3 | 7]

最终树:
        1
       / \
      2   3
     / \ / \
    4  5 6  7
```

---

## 🚨 常见错误 (Common Mistakes)

### ❌ 错误1: 右子树起点计算错误
```python
# 错误
right_start = pre_left + 1  # 忘记考虑左子树大小!

# 正确
right_start = pre_left + left_size + 1
```

### ❌ 错误2: 边界条件处理不当
```python
# 错误
if not preorder:  # 应该检查索引范围

# 正确
if pre_left > pre_right:
    return None
```

### ❌ 错误3: 混淆中序和前序的索引
```python
# 左子树大小应该从中序计算!
left_size = root_idx_in_inorder - in_left  # ✅

# 不是从前序计算
left_size = pre_left + 1  # ❌ 错误!
```

---

## 🔗 相关问题 (Related Problems)

### 106. 从中序与后序遍历构造二叉树
```python
# 后序: [左子树, 右子树, 根]
# 根节点是后序的最后一个元素
root_val = postorder[-1]  # 或 postorder[post_right]
```

### 889. 从前序与后序遍历构造二叉树
```python
# 前序: [根, 左子树, 右子树]
# 后序: [左子树, 右子树, 根]
# 注意: 不能唯一确定! 需要假设左子树非空时，前序第二个元素是左子树的根
```

---

## 📝 练习建议 (Practice Tips)

1. **手动模拟**: 用纸笔画出树的构建过程
2. **调试跟踪**: 使用 print 语句打印每一步
3. **边界情况**: 测试空树、单节点、链状树
4. **变体练习**: 尝试后序+中序、前序+后序

---

## 📂 文件说明 (File Description)

| 文件 | 说明 |
|-----|------|
| `105_construct_tree.py` | 完整实现 + 测试用例 |
| `105_step_by_step_trace.py` | 逐步跟踪算法执行过程 |
| `105_algorithm_trace.md` | 详细的算法步骤说明 |
| `105_SUMMARY.md` | 本文档 - 完整总结 |

---

## 🎓 总结 (Summary)

**核心思想**: 前序找根，中序分割，递归构建

**时间复杂度**: O(n) - 使用哈希表优化

**空间复杂度**: O(n) - 递归栈 + 哈希表

**关键技巧**: 索引传递 > 数组切片

掌握这个算法后，你就能解决所有"从遍历序列构造树"的问题! 🎯

