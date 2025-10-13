"""
LeetCode 105: Construct Binary Tree from Preorder and Inorder Traversal
从前序与中序遍历序列构造二叉树

Time: O(n)
Space: O(n)
"""

from typing import List, Optional


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        """
        Build binary tree from preorder and inorder traversal arrays.
        
        Key insight:
        - Preorder: [root, left_subtree, right_subtree] - root is first
        - Inorder:  [left_subtree, root, right_subtree] - root is middle
        
        Args:
            preorder: Preorder traversal array
            inorder: Inorder traversal array
            
        Returns:
            Root node of constructed tree
        """
        # Build hashmap for O(1) lookup of root position in inorder
        inorder_map = {val: idx for idx, val in enumerate(inorder)}
        
        def build(pre_left: int, pre_right: int, in_left: int, in_right: int) -> Optional[TreeNode]:
            """
            Recursively build tree from preorder[pre_left:pre_right+1] 
            and inorder[in_left:in_right+1]
            """
            # Base case: empty range
            if pre_left > pre_right:
                return None
            
            # Step 1: Root is first element in preorder range
            root_val = preorder[pre_left]
            root = TreeNode(root_val)
            
            # Step 2: Find root position in inorder (O(1) with hashmap)
            root_idx_in_inorder = inorder_map[root_val]
            
            # Step 3: Calculate left subtree size
            left_subtree_size = root_idx_in_inorder - in_left
            
            # Step 4: Recursively build left subtree
            # Left subtree in preorder: [pre_left+1, pre_left+left_subtree_size]
            # Left subtree in inorder:  [in_left, root_idx_in_inorder-1]
            root.left = build(
                pre_left + 1,
                pre_left + left_subtree_size,
                in_left,
                root_idx_in_inorder - 1
            )
            
            # Step 5: Recursively build right subtree
            # Right subtree in preorder: [pre_left+left_subtree_size+1, pre_right]
            # Right subtree in inorder:  [root_idx_in_inorder+1, in_right]
            root.right = build(
                pre_left + left_subtree_size + 1,
                pre_right,
                root_idx_in_inorder + 1,
                in_right
            )
            
            return root
        
        # Start recursion with full arrays
        return build(0, len(preorder) - 1, 0, len(inorder) - 1)


# Test and visualization functions
def level_order(root: Optional[TreeNode]) -> List[Optional[int]]:
    """Return level-order traversal of tree"""
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


def preorder_traversal(root: Optional[TreeNode]) -> List[int]:
    """Return preorder traversal"""
    if not root:
        return []
    return [root.val] + preorder_traversal(root.left) + preorder_traversal(root.right)


def inorder_traversal(root: Optional[TreeNode]) -> List[int]:
    """Return inorder traversal"""
    if not root:
        return []
    return inorder_traversal(root.left) + [root.val] + inorder_traversal(root.right)


def visualize(root: Optional[TreeNode], level=0, prefix="Root: "):
    """Print tree structure"""
    if not root:
        return
    print(" " * (level * 4) + prefix + str(root.val))
    if root.left or root.right:
        if root.left:
            visualize(root.left, level + 1, "L--- ")
        else:
            print(" " * ((level + 1) * 4) + "L--- None")
        if root.right:
            visualize(root.right, level + 1, "R--- ")
        else:
            print(" " * ((level + 1) * 4) + "R--- None")


if __name__ == "__main__":
    solution = Solution()
    
    # Example 1
    print("Example 1:")
    print("-" * 50)
    preorder1 = [3, 9, 20, 15, 7]
    inorder1 = [9, 3, 15, 20, 7]
    
    tree1 = solution.buildTree(preorder1, inorder1)
    print(f"Input:  preorder = {preorder1}")
    print(f"        inorder  = {inorder1}")
    print(f"\nOutput tree:")
    visualize(tree1)
    print(f"\nVerification:")
    print(f"  Preorder: {preorder_traversal(tree1)}")
    print(f"  Inorder:  {inorder_traversal(tree1)}")
    print()
    
    # Example 2
    print("Example 2:")
    print("-" * 50)
    preorder2 = [-1]
    inorder2 = [-1]
    
    tree2 = solution.buildTree(preorder2, inorder2)
    print(f"Input:  preorder = {preorder2}")
    print(f"        inorder  = {inorder2}")
    print(f"\nOutput tree:")
    visualize(tree2)
    print()
    
    # Example 3
    print("Example 3:")
    print("-" * 50)
    preorder3 = [1, 2, 4, 5, 3, 6, 7]
    inorder3 = [4, 2, 5, 1, 6, 3, 7]
    
    tree3 = solution.buildTree(preorder3, inorder3)
    print(f"Input:  preorder = {preorder3}")
    print(f"        inorder  = {inorder3}")
    print(f"\nOutput tree:")
    visualize(tree3)
    print(f"\nVerification:")
    print(f"  Preorder: {preorder_traversal(tree3)}")
    print(f"  Inorder:  {inorder_traversal(tree3)}")

