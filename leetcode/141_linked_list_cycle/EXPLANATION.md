# 141. Linked List Cycle

Determine whether following `next` pointers from `head` can revisit the same node. Return a Boolean without modifying the list. An empty list has no cycle.

Node identity matters: two different nodes can have the same value without forming a cycle.

## Review of your implementation

Your implementation is correct for the supplied `ListNode` definition. It uses Floyd's slow-and-fast-pointer idea:

- `slow` starts at `head` and moves one edge per iteration.
- `fast` starts at `head.next` and moves two edges per iteration when possible.
- In a cycle, they eventually meet at a node.
- Without a cycle, `fast` reaches `null` and stays there while `slow` continues to `null`. The loop then ends, and `fast != null` returns `false`.

The last point is correct but does unnecessary work after `fast` reaches the end. We can make termination clearer by returning `false` as soon as `fast` cannot take two steps.

Your original implementation, with formatting cleaned up:

```kotlin
class Solution {
    fun hasCycle(head: ListNode?): Boolean {
        if (head == null || head.next == null) return false

        var slow = head
        var fast = head.next

        while (slow != fast) {
            if (slow != null) slow = slow.next
            if (fast != null) fast = fast.next
            if (fast != null) fast = fast.next
        }

        return fast != null
    }
}
```

## Solution evolution

### 1. Remember previously visited nodes

Follow `next` pointers and store each node's identity in a set. If a node is already present, return `true`. If traversal reaches `null`, return `false`.

For `A → B → C → D → B`, we record `A, B, C, D`, then encounter `B` again and detect the cycle. For `A → B → null`, traversal ends without revisiting a node.

This takes expected O(n) time with a hash set and O(n) auxiliary space, where `n` is the number of distinct reachable nodes. With the supplied ordinary `ListNode` class, default equality is based on identity; a value-based equality implementation would require an identity-aware set.

**What to say:** “A straightforward approach is to remember each visited node. Revisiting the same object proves there is a cycle, but storing the visited nodes costs linear space.”

### 2. Replace stored history with two traversal speeds

Instead of storing all previously visited nodes, use two pointers. Move `slow` one edge and `fast` two edges per iteration.

Without a cycle, `fast` reaches the end. With a cycle, both pointers eventually enter it, and their relative positions change by one edge per iteration, forcing a meeting.

This keeps O(n) time while reducing auxiliary space to O(1).

**What to say:** “A cycle lets the faster pointer keep moving around the same nodes. Once both pointers are inside the cycle, the faster pointer gains one position per iteration, so they must eventually meet.”

| Approach | Time | Auxiliary space |
| --- | --- | --- |
| Visited-node hash set | Expected O(n) | O(n) |
| Slow and fast pointers | O(n) | O(1) |

## Polished Kotlin implementation

The judge provides `ListNode`; its definition is included below as a reference comment.

```kotlin
/**
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */
class Solution {
    fun hasCycle(head: ListNode?): Boolean {
        var slow = head
        var fast = head

        while (fast != null && fast.next != null) {
            slow = slow?.next
            fast = fast.next?.next

            if (slow === fast) return true
        }

        return false
    }
}
```

### What changed and why

- Both pointers now start at `head`, so the meeting check happens **after moving**. Checking before moving would incorrectly report a cycle just because their initial positions match.
- The loop guard checks whether `fast` can take two steps. When it cannot, the list ends and the method returns `false`; there is no need to wait for `slow`.
- `===` explicitly compares object identity. Your `==` also works for the supplied class, which does not override `equals`, but `===` states exactly what cycle detection needs.
- The guard handles empty and single-node lists, so the initial special-case return is unnecessary.

The second fast step may land on `null`, which is safe. During an executed iteration, `slow` remains a real node: in an acyclic list it has traveled fewer edges than `fast`, and in a cyclic list neither pointer reaches `null`. Thus, the meeting check cannot accidentally succeed because both are null.

## Step-by-step interview explanation

### 1. Define what counts as a cycle

“I need to determine whether following `next` pointers revisits the same node object. Equal values alone do not indicate a cycle, and I will leave the list unchanged.”

### 2. Explain the baseline and its cost

“I could keep a set of visited nodes and return true on the first repeated node. That takes linear extra space. To reduce the space, I can use two pointers moving at different speeds.”

### 3. Define the pointer roles

“I start `slow` and `fast` at `head`. On each iteration, `slow` moves one edge and `fast` moves two. I compare them only after moving, because they share the initial position even when there is no cycle.”

Write the two initializations.

### 4. Establish when movement is safe

“Before each iteration, I check that `fast` and `fast.next` exist. If either is null, the path has reached its end, so there is no cycle. The second step itself is allowed to land on null.”

Write the `while` guard and the two pointer updates.

### 5. Detect a meeting

“After the moves, if both pointers reference the same node, I return true. Otherwise, I continue. I use identity comparison because two different nodes may contain the same value.”

Write `if (slow === fast) return true`, followed by `return false` after the loop.

### 6. Explain why a cycle guarantees a meeting

“Once both pointers enter a cycle of length `L`, their relative position changes by one modulo `L` per iteration. Within at most `L` more iterations, that relative position becomes zero, meaning they meet. The faster pointer cannot keep skipping over the slower pointer forever because the relative step is exactly one.”

### 7. Close with complexity and edge cases

“The algorithm takes O(n) time and O(1) extra space. An empty list and a single node ending at null return false immediately. A node pointing to itself returns true after the first move. Duplicate values do not affect the result.”

## Execution traces

Letters below identify distinct node objects, not their stored values. Each iteration row shows positions **after both moves**, followed by the identity check.

### A list with a cycle

```text
A → B → C → D
    ↑       │
    └───────┘

D.next = B
```

| State | `slow` | `fast` | Action |
| --- | --- | --- | --- |
| Initial | A | A | Do not compare yet. |
| Iteration 1 | B | C | Different nodes; continue. |
| Iteration 2 | C | B | Different nodes; continue. |
| Iteration 3 | D | D | Same node; return `true`. |

For example, in iteration 2, `fast` moves `C → D → B`. The meeting at `D` proves a cycle exists; it does not mean `D` is the cycle's entry node.

### A list without a cycle

```text
A → B → C → D → null
```

| State | `slow` | `fast` | Action |
| --- | --- | --- | --- |
| Initial | A | A | Do not compare yet. |
| Iteration 1 | B | C | Different nodes; continue. |
| Iteration 2 | C | null | Different; the next loop guard fails. |
| Finished | C | null | Return `false`. |

Unlike your original implementation, the polished version does not wait for `slow` to reach null.

## Correctness and termination

**Without a cycle:** After `t` iterations, `slow` has traveled `t` edges and `fast` has traveled `2t` edges. For `t > 0`, they cannot reference the same non-null node on a path with no repeated nodes. Eventually, `fast` or `fast.next` is null, so the method terminates and returns `false`.

**With a cycle:** Let `μ` be the number of edges before the cycle entry and `L` the cycle length. After at most `μ` iterations, both pointers are inside the cycle. Each further iteration changes their relative position by one modulo `L`, so a meeting occurs within at most `L` further iterations. The method returns `true`.

The total work is O(μ + L) for a cyclic list and O(n) for an acyclic list, hence O(n) in terms of distinct reachable nodes. Only two pointers are stored, giving O(1) auxiliary space.

## Boundary cases to check

| List | Expected result | Reason |
| --- | --- | --- |
| `null` | `false` | The loop never starts. |
| `A → null` | `false` | `fast.next` is null. |
| `A → A` | `true` | Both moves return to A. |
| `A → B → null` | `false` | First iteration places fast at null. |
| `A → B → A` | `true` | The pointers meet after two iterations. |
| Two distinct nodes both storing `5`, then null | `false` | Equal values do not imply equal identities. |

These traces and boundary cases are reasoning checks, not a report of executed tests.

## Short interview recap

“I use Floyd's cycle detection. A slow pointer moves one step and a fast pointer moves two steps. If the fast pointer reaches the end, there is no cycle. If there is a cycle, their relative position changes by one each iteration once they are inside it, so they must meet. I compare node identity after moving and use O(n) time with O(1) extra space.”

## Recall questions

1. Why must the meeting check happen after moving when both pointers start at `head`?
2. Why does comparing node values give incorrect results?
3. Why does the relative speed of one guarantee a meeting inside the cycle?
4. Why can the polished implementation stop before `slow` reaches null?
