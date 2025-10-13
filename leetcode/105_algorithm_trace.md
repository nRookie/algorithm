# 从前序与中序遍历构造二叉树 - 算法过程详解

## 核心思想 (Core Idea)

**前序遍历 (Preorder)**: `[根, 左子树, 右子树]` - 根节点总是第一个
**中序遍历 (Inorder)**: `[左子树, 根, 右子树]` - 根节点在中间

---

## 完整算法过程 (Complete Algorithm Process)

### Example: 
```
preorder = [3, 9, 20, 15, 7]
inorder  = [9, 3, 15, 20, 7]
```

---

## 第一步 (Step 1): 找到根节点

```
前序遍历的第一个元素 = 3
→ 根节点 = 3
```

---

## 第二步 (Step 2): 在中序遍历中定位根节点

```
inorder = [9, 3, 15, 20, 7]
               ↑
          根节点位置 (index = 1)

左边: [9]       → 左子树 (1个节点)
右边: [15,20,7] → 右子树 (3个节点)
```

**当前树结构:**
```
    3
   / \
  ?   ?
```

---

## 第三步 (Step 3): 递归构建左子树

### 3.1 确定左子树的前序和中序范围

```
左子树大小 = 1

左子树的前序: preorder[1:2] = [9]
左子树的中序: inorder[0:1] = [9]
```

### 3.2 递归调用

```
build(preorder=[9], inorder=[9])

- 根节点 = 9
- 在中序中找到 9，位置 = 0
- 左子树: 空 (0个节点)
- 右子树: 空 (0个节点)
- 返回: TreeNode(9)
```

**当前树结构:**
```
    3
   / \
  9   ?
```

---

## 第四步 (Step 4): 递归构建右子树

### 4.1 确定右子树的前序和中序范围

```
右子树的前序: preorder[2:5] = [20, 15, 7]
右子树的中序: inorder[2:5] = [15, 20, 7]
```

### 4.2 递归调用 - 构建右子树的根

```
build(preorder=[20,15,7], inorder=[15,20,7])

- 根节点 = 20
- 在中序中找到 20，位置 = 1
- 左边: [15]   → 左子树 (1个节点)
- 右边: [7]    → 右子树 (1个节点)
```

**当前树结构:**
```
    3
   / \
  9   20
     /  \
    ?    ?
```

### 4.3 构建 20 的左子树

```
build(preorder=[15], inorder=[15])

- 根节点 = 15
- 无左右子树
- 返回: TreeNode(15)
```

**当前树结构:**
```
    3
   / \
  9   20
     /  \
    15   ?
```

### 4.4 构建 20 的右子树

```
build(preorder=[7], inorder=[7])

- 根节点 = 7
- 无左右子树
- 返回: TreeNode(7)
```

**最终树结构:**
```
    3
   / \
  9   20
     /  \
    15   7
```

---

## 递归调用树 (Recursion Tree)

```
build([3,9,20,15,7], [9,3,15,20,7])
│
├─ build([9], [9])                    → TreeNode(9)
│
└─ build([20,15,7], [15,20,7])
   │
   ├─ build([15], [15])               → TreeNode(15)
   │
   └─ build([7], [7])                 → TreeNode(7)
```

---

## 索引计算详解 (Index Calculation Details)

对于递归函数 `build(pre_left, pre_right, in_left, in_right)`:

### 初始调用:
```
build(0, 4, 0, 4)
- preorder[0:5] = [3, 9, 20, 15, 7]
- inorder[0:5]  = [9, 3, 15, 20, 7]
```

### 根节点:
```
root_val = preorder[pre_left] = preorder[0] = 3
root_idx_in_inorder = 1 (找到3在inorder中的位置)
```

### 左子树大小:
```
left_subtree_size = root_idx_in_inorder - in_left
                  = 1 - 0
                  = 1
```

### 左子树范围:
```
前序: [pre_left+1, pre_left+left_subtree_size]
    = [0+1, 0+1]
    = [1, 1]
    → preorder[1:2] = [9]

中序: [in_left, root_idx_in_inorder-1]
    = [0, 1-1]
    = [0, 0]
    → inorder[0:1] = [9]
```

### 右子树范围:
```
前序: [pre_left+left_subtree_size+1, pre_right]
    = [0+1+1, 4]
    = [2, 4]
    → preorder[2:5] = [20, 15, 7]

中序: [root_idx_in_inorder+1, in_right]
    = [1+1, 4]
    = [2, 4]
    → inorder[2:5] = [15, 20, 7]
```

---

## 复杂度分析 (Complexity Analysis)

**时间复杂度:** O(n)
- 每个节点访问一次
- 使用哈希表使得在中序中查找根节点为 O(1)

**空间复杂度:** O(n)
- 递归调用栈: O(h) 其中 h 是树高
- 哈希表: O(n)
- 总计: O(n)

---

## 关键点总结 (Key Points)

1. **前序第一个 = 根节点**
2. **在中序中找到根 → 分割左右子树**
3. **左子树大小 = 根在中序中的位置 - 左边界**
4. **使用索引避免切片，提高效率**
5. **哈希表加速查找根节点位置**

---

## 常见错误 (Common Mistakes)

❌ **错误1:** 忘记左子树的大小会影响右子树在前序中的起始位置
```python
# 错误
right_start = pre_left + 1  # ❌ 没有考虑左子树大小

# 正确
right_start = pre_left + left_subtree_size + 1  # ✓
```

❌ **错误2:** 使用切片创建新数组（低效）
```python
# 低效但简单
left_pre = preorder[1:1+root_idx]

# 高效
build(pre_left+1, pre_left+left_size, ...)
```

❌ **错误3:** 每次都用 `index()` 查找根节点
```python
# O(n) 每次查找
root_idx = inorder.index(root_val)

# O(1) 查找（预处理哈希表）
root_idx = inorder_map[root_val]
```

---

## 相关问题 (Related Problems)

- **106. 从中序与后序遍历序列构造二叉树**
  - 后序: `[左子树, 右子树, 根]`
  - 根节点是后序的**最后一个**元素
  
- **889. 根据前序和后序遍历构造二叉树**
  - 注意: 不能唯一确定（需要额外约束）

