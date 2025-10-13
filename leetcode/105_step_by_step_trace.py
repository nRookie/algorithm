"""
Interactive Step-by-Step Trace of Building Tree from Preorder and Inorder
逐步跟踪从前序和中序遍历构造二叉树的过程
"""

from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class SolutionWithTrace:
    def __init__(self):
        self.step = 0
        self.indent_level = 0
    
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        print("=" * 80)
        print("开始构造二叉树 (Start Building Tree)")
        print("=" * 80)
        print(f"Preorder: {preorder}")
        print(f"Inorder:  {inorder}")
        print("=" * 80)
        print()
        
        self.inorder_map = {val: idx for idx, val in enumerate(inorder)}
        self.preorder = preorder
        self.inorder = inorder
        
        result = self.build(0, len(preorder) - 1, 0, len(inorder) - 1)
        
        print("=" * 80)
        print("构造完成! (Construction Complete!)")
        print("=" * 80)
        return result
    
    def build(self, pre_left: int, pre_right: int, in_left: int, in_right: int) -> Optional[TreeNode]:
        # Indentation for nested calls
        indent = "  " * self.indent_level
        
        # Base case
        if pre_left > pre_right:
            print(f"{indent}└─ 空节点 (Empty node)")
            return None
        
        self.step += 1
        print(f"\n{indent}{'─' * 60}")
        print(f"{indent}步骤 {self.step} (Step {self.step})")
        print(f"{indent}{'─' * 60}")
        
        # Current range
        pre_range = self.preorder[pre_left:pre_right+1]
        in_range = self.inorder[in_left:in_right+1]
        print(f"{indent}当前前序范围: {pre_range} (indices [{pre_left}:{pre_right}])")
        print(f"{indent}当前中序范围: {in_range} (indices [{in_left}:{in_right}])")
        
        # Step 1: Find root
        root_val = self.preorder[pre_left]
        print(f"{indent}")
        print(f"{indent}1️⃣  前序第一个元素 = {root_val} → 这是根节点!")
        root = TreeNode(root_val)
        
        # Step 2: Find root in inorder
        root_idx_in_inorder = self.inorder_map[root_val]
        print(f"{indent}2️⃣  在中序中找到 {root_val} 的位置: index = {root_idx_in_inorder}")
        
        # Step 3: Calculate left subtree size
        left_subtree_size = root_idx_in_inorder - in_left
        right_subtree_size = in_right - root_idx_in_inorder
        
        print(f"{indent}3️⃣  计算子树大小:")
        print(f"{indent}   左子树: {left_subtree_size} 个节点")
        print(f"{indent}   右子树: {right_subtree_size} 个节点")
        
        if left_subtree_size > 0:
            left_pre = self.preorder[pre_left+1:pre_left+1+left_subtree_size]
            left_in = self.inorder[in_left:root_idx_in_inorder]
            print(f"{indent}   左子树前序: {left_pre}")
            print(f"{indent}   左子树中序: {left_in}")
        
        if right_subtree_size > 0:
            right_pre = self.preorder[pre_left+left_subtree_size+1:pre_right+1]
            right_in = self.inorder[root_idx_in_inorder+1:in_right+1]
            print(f"{indent}   右子树前序: {right_pre}")
            print(f"{indent}   右子树中序: {right_in}")
        
        # Build left subtree
        print(f"{indent}")
        print(f"{indent}4️⃣  递归构建左子树:")
        self.indent_level += 1
        root.left = self.build(
            pre_left + 1,
            pre_left + left_subtree_size,
            in_left,
            root_idx_in_inorder - 1
        )
        self.indent_level -= 1
        
        # Build right subtree
        print(f"{indent}")
        print(f"{indent}5️⃣  递归构建右子树:")
        self.indent_level += 1
        root.right = self.build(
            pre_left + left_subtree_size + 1,
            pre_right,
            root_idx_in_inorder + 1,
            in_right
        )
        self.indent_level -= 1
        
        print(f"{indent}")
        print(f"{indent}✅ 节点 {root_val} 构造完成!")
        
        return root


def visualize_tree(root: Optional[TreeNode], level=0, prefix="Root: "):
    """可视化树结构"""
    if root is None:
        return
    print(" " * (level * 4) + prefix + str(root.val))
    if root.left or root.right:
        if root.left:
            visualize_tree(root.left, level + 1, "L--- ")
        else:
            print(" " * ((level + 1) * 4) + "L--- None")
        if root.right:
            visualize_tree(root.right, level + 1, "R--- ")
        else:
            print(" " * ((level + 1) * 4) + "R--- None")


if __name__ == "__main__":
    # Test Case 1: Simple example
    print("\n")
    print("█" * 80)
    print("测试案例 1 (Test Case 1)")
    print("█" * 80)
    
    solution = SolutionWithTrace()
    preorder = [3, 9, 20, 15, 7]
    inorder = [9, 3, 15, 20, 7]
    
    tree = solution.buildTree(preorder, inorder)
    
    print("\n")
    print("最终树结构 (Final Tree Structure):")
    print("-" * 40)
    visualize_tree(tree)
    
    print("\n" * 2)
    print("█" * 80)
    print("测试案例 2 (Test Case 2) - 更复杂的例子")
    print("█" * 80)
    
    solution2 = SolutionWithTrace()
    preorder2 = [1, 2, 4, 5, 3, 6, 7]
    inorder2 = [4, 2, 5, 1, 6, 3, 7]
    
    tree2 = solution2.buildTree(preorder2, inorder2)
    
    print("\n")
    print("最终树结构 (Final Tree Structure):")
    print("-" * 40)
    visualize_tree(tree2)
    print("\n期望结构:")
    print("""
        1
       / \\
      2   3
     / \\ / \\
    4  5 6  7
    """)

