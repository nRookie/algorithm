# SPFA Algorithm - Termination and Negative Cycles

## Your Question: "How do I know when to finish?"

Great observation! This is a critical issue with SPFA.

---

## Case 1: Graph WITHOUT Negative Cycle ✅

**SPFA terminates naturally when the queue becomes empty**

```
Example: 1 --(-5)--> 2 --(3)--> 3
```

- Even with negative weight -5, there's no cycle
- Each node is updated a **finite** number of times
- Eventually, no more relaxations are possible → queue becomes empty
- **Termination: Guaranteed** ✅

---

## Case 2: Graph WITH Negative Cycle ⚠️

**SPFA can loop forever (or a very long time)**

```
Example: 1 --> 2 --> 3
              ↑      ↓
              +------+
           (total cycle weight = -1)
```

- You can keep going around the cycle
- Distance keeps decreasing: 0 → -1 → -2 → -3 → ...
- Nodes keep getting added to queue repeatedly
- **Without detection: Infinite loop** ⚠️

---

## The Solution: Count Relaxations 🔍

### Key Insight:
**In a graph with N nodes, any shortest path has at most N-1 edges**

Why? Because:
- A shortest path never visits the same node twice (that would be suboptimal)
- With N nodes, you can visit at most N nodes
- That means at most N-1 edges

### Therefore:
**If a node is relaxed N or more times → Negative cycle exists!**

---

## Implementation

```python
cnt = [0] * (n + 1)  # Count edges in path to each node

while q:
    u = q.popleft()
    st[u] = False
    
    for v, d in g[u]:
        if dist[v] > dist[u] + d:
            dist[v] = dist[u] + d
            cnt[v] = cnt[u] + 1  # ← Track path length
            
            if cnt[v] >= n:      # ← Negative cycle!
                return "NEGATIVE CYCLE"
            
            if not st[v]:
                st[v] = True
                q.append(v)
```

---

## When to Use Which Version?

### 1. **Standard SPFA** (no negative cycle detection)
- Use when: Problem guarantees no negative cycles
- Example: "Find shortest path from 1 to N"
- Safer: Terminates naturally

### 2. **SPFA with negative cycle detection**
- Use when: Graph might have negative cycles
- Example: "Detect if negative cycle exists"
- Necessary: Prevents infinite loops

---

## Time Complexity

- **Best case**: O(E) where E = number of edges
- **Average case**: O(kE) where k is small (usually 2)
- **Worst case**: O(VE) where V = nodes, E = edges
  - This happens when there's a negative cycle
  - With detection: stops at O(VE) when cnt[v] >= n

---

## Summary

| Scenario | Termination | Need Detection? |
|----------|-------------|-----------------|
| No negative weights | Queue empty | ❌ No |
| Negative weights, no cycle | Queue empty | ❌ No (but safe to have) |
| Negative cycle | Never (without detection) | ✅ Yes! |

**Your intuition was correct!** SPFA can indeed loop forever with negative cycles, which is why the `cnt` array is crucial for real-world implementations.

