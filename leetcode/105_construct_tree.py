"""
LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
从前序与中序遍历序列构造二叉树

Key Insight:
- Preorder: [root, left_subtree, right_subtree]
- Inorder:  [left_subtree, root, right_subtree]
"""

from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        # Build a hashmap for quick lookup of root position in inorder
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        
        def build(pre_left: int, pre_right: int, in_left: int, in_right: int) -> Optional[TreeNode]:
            """
            Build tree from preorder[pre_left:pre_right+1] and inorder[in_left:in_right+1]
            """
            # Base case: empty range
            if pre_left > pre_right:
                return None
            
            # Step 1: Root is the first element in preorder
            root_val = preorder[pre_left]
            root = TreeNode(root_val)
            
            # Step 2: Find root position in inorder
            root_idx_in_inorder = inorder_map[root_val]
            
            # Step 3: Calculate left subtree size
            left_subtree_size = root_idx_in_inorder - in_left
            
            # Step 4: Recursively build left and right subtrees
            # Left subtree:
            #   - Preorder: [pre_left+1, pre_left+left_subtree_size]
            #   - Inorder:  [in_left, root_idx_in_inorder-1]
            root.left = build(
                pre_left + 1,
                pre_left + left_subtree_size,
                in_left,
                root_idx_in_inorder - 1
            )
            
            # Right subtree:
            #   - Preorder: [pre_left+left_subtree_size+1, pre_right]
            #   - Inorder:  [root_idx_in_inorder+1, in_right]
            root.right = build(
                pre_left + left_subtree_size + 1,
                pre_right,
                root_idx_in_inorder + 1,
                in_right
            )
            
            return root
        
        return build(0, len(preorder) - 1, 0, len(inorder) - 1)


# ============================================
# Alternative: Simpler but Less Efficient
# ============================================

class SolutionSimple:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        if not preorder or not inorder:
            return None
        
        # Step 1: Root is first in preorder
        root_val = preorder[0]
        root = TreeNode(root_val)
        
        # Step 2: Find root in inorder
        root_idx = inorder.index(root_val)
        
        # Step 3: Split into left and right
        # Left subtree has 'root_idx' nodes
        root.left = self.buildTree(
            preorder[1 : 1 + root_idx],
            inorder[: root_idx]
        )
        
        root.right = self.buildTree(
            preorder[1 + root_idx :],
            inorder[root_idx + 1 :]
        )
        
        return root


# ============================================
# Helper Functions for Testing
# ============================================

def print_tree_level_order(root: Optional[TreeNode]) -> List[Optional[int]]:
    """Print tree in level order (BFS)"""
    if not root:
        return []
    
    result = []
    queue = [root]
    
    while queue:
        node = queue.pop(0)
        if node:
            result.append(node.val)
            queue.append(node.left)
            queue.append(node.right)
        else:
            result.append(None)
    
    # Remove trailing None values
    while result and result[-1] is None:
        result.pop()
    
    return result


def visualize_tree(root: Optional[TreeNode], level=0, prefix="Root: "):
    """Print tree structure"""
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


# ============================================
# Test Cases
# ============================================

if __name__ == "__main__":
    solution = Solution()
    
    # Test Case 1
    print("=" * 60)
    print("Test Case 1:")
    print("=" * 60)
    preorder1 = [3, 9, 20, 15, 7]
    inorder1 = [9, 3, 15, 20, 7]
    print(f"Preorder: {preorder1}")
    print(f"Inorder:  {inorder1}")
    print()
    
    tree1 = solution.buildTree(preorder1, inorder1)
    print("Constructed Tree:")
    visualize_tree(tree1)
    print()
    print(f"Level order: {print_tree_level_order(tree1)}")
    print(f"Expected:    [3, 9, 20, None, None, 15, 7]")
    print()
    
    # Test Case 2
    print("=" * 60)
    print("Test Case 2:")
    print("=" * 60)
    preorder2 = [-1]
    inorder2 = [-1]
    print(f"Preorder: {preorder2}")
    print(f"Inorder:  {inorder2}")
    print()
    
    tree2 = solution.buildTree(preorder2, inorder2)
    print("Constructed Tree:")
    visualize_tree(tree2)
    print()
    
    # Test Case 3: More complex
    print("=" * 60)
    print("Test Case 3:")
    print("=" * 60)
    preorder3 = [1, 2, 4, 5, 3, 6, 7]
    inorder3 = [4, 2, 5, 1, 6, 3, 7]
    print(f"Preorder: {preorder3}")
    print(f"Inorder:  {inorder3}")
    print()
    
    tree3 = solution.buildTree(preorder3, inorder3)
    print("Constructed Tree:")
    visualize_tree(tree3)
    print()
    print("""
Expected tree:
        1
       / \\
      2   3
     / \\ / \\
    4  5 6  7
    """)

