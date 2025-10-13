"""
简洁版本 - LeetCode 105: 从前序与中序遍历构造二叉树
Simple Version - Construct Binary Tree from Preorder and Inorder Traversal
"""

from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        # 哈希表: 快速查找根在中序中的位置
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        
        def build(pre_l, pre_r, in_l, in_r):
            if pre_l > pre_r:
                return None
            
            # 前序第一个 = 根节点
            root = TreeNode(preorder[pre_l])
            
            # 在中序中找到根的位置
            root_idx = inorder_map[root.val]
            
            # 左子树大小
            left_size = root_idx - in_l
            
            # 递归构建左右子树
            root.left = build(pre_l + 1, pre_l + left_size, in_l, root_idx - 1)
            root.right = build(pre_l + left_size + 1, pre_r, root_idx + 1, in_r)
            
            return root
        
        return build(0, len(preorder) - 1, 0, len(inorder) - 1)


# 更简洁的版本 (使用数组切片，但效率较低)
class SolutionSimple:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        if not preorder:
            return None
        
        root = TreeNode(preorder[0])
        idx = inorder.index(root.val)
        
        root.left = self.buildTree(preorder[1:idx+1], inorder[:idx])
        root.right = self.buildTree(preorder[idx+1:], inorder[idx+1:])
        
        return root


# 测试
if __name__ == "__main__":
    solution = Solution()
    
    preorder = [3, 9, 20, 15, 7]
    inorder = [9, 3, 15, 20, 7]
    
    tree = solution.buildTree(preorder, inorder)
    print(f"Tree root: {tree.val}")
    print(f"Left child: {tree.left.val}")
    print(f"Right child: {tree.right.val}")
    print(f"Right's left: {tree.right.left.val}")
    print(f"Right's right: {tree.right.right.val}")

