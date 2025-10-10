# Bellman-Ford vs SPFA Comparison

## Overview
Both algorithms solve single-source shortest path problems with **negative edge weights** (unlike Dijkstra).

---

## Bellman-Ford Algorithm

### Core Idea
Relax **ALL edges** exactly `n-1` times.

### Pseudocode
```cpp
// Initialize
dist[start] = 0;
dist[others] = INF;

// Relax all edges n-1 times
for (int i = 0; i < n - 1; i++) {
    for (each edge (u, v, w)) {
        dist[v] = min(dist[v], dist[u] + w);
    }
}
```

### Time Complexity
- **Always O(n × m)** - fixed number of iterations
- n = number of nodes
- m = number of edges

### Space Complexity
- O(n) - only need distance array

### Characteristics
✅ Simple to implement
✅ Easy to modify for "at most k edges" constraint
✅ Guaranteed to work with negative weights
❌ Slow - processes all edges every iteration
❌ No early termination

### When to Use
1. **Edge limit constraint** - "shortest path with at most k edges"
2. Small graphs where performance doesn't matter
3. When simplicity is priority

---

## SPFA (Shortest Path Faster Algorithm)

### Core Idea
Only relax edges from nodes whose distance **recently changed** (using a queue).

### Pseudocode
```python
dist[start] = 0
dist[others] = INF
st = [False] * (n + 1)  # Track if node is in queue

q = deque([start])
st[start] = True

while q:
    u = q.popleft()
    st[u] = False  # Mark as being processed

    for (v, weight) in neighbors(u):
        if dist[v] > dist[u] + weight:
            dist[v] = dist[u] + weight

            if not st[v]:  # Only add if not already in queue
                st[v] = True
                q.append(v)
```

### Time Complexity
- **Average case: O(m)** - much faster in practice! 🚀
- **Worst case: O(n × m)** - same as Bellman-Ford (dense graphs with many updates)

### Space Complexity
- O(n + m) - need distance array, queue, and st array

### Characteristics
✅ **Much faster** on average (often 10-1000x speedier)
✅ Adapts to graph structure
✅ Works with negative weights
✅ Easy to detect negative cycles
❌ Slightly more complex implementation
❌ Worst case same as Bellman-Ford

### When to Use
1. **Large graphs** with negative weights
2. **Sparse graphs** - gets closer to O(m) performance
3. **Competitive programming** - usually the preferred choice
4. When you need **negative cycle detection**

---

## Direct Comparison

| Aspect | Bellman-Ford | SPFA |
|--------|--------------|------|
| **Average Time** | O(nm) | **O(m)** ⚡ |
| **Worst Time** | O(nm) | O(nm) |
| **Space** | O(n) | O(n) |
| **Implementation** | Simpler | Moderate |
| **Early Stop** | ❌ No | ✅ Yes (queue empty) |
| **Edge Limit** | ✅ Easy to add | ❌ Harder |
| **Negative Cycle Detection** | Can add | Easy to add |

---

## Example Performance

Graph: n = 1000 nodes, m = 5000 edges

**Bellman-Ford:**
```
Iterations: 999 (always)
Edge relaxations: 999 × 5000 = 4,995,000
Time: ~500ms
```

**SPFA (typical case):**
```
Iterations: ~50 (variable)
Edge relaxations: ~10,000
Time: ~1ms
```

**Speedup: ~500x faster!** 🎉

---

## Negative Cycle Detection

### Bellman-Ford
```cpp
// After n-1 iterations, do one more check
for (each edge (u, v, w)) {
    if (dist[v] > dist[u] + w) {
        // Negative cycle exists!
    }
}
```

### SPFA
```python
cnt = [0] * (n + 1)  # Count relaxations per node

while q:
    u = q.popleft()
    st[u] = False

    for v, weight in g[u]:
        if dist[v] > dist[u] + weight:
            dist[v] = dist[u] + weight
            cnt[v] = cnt[u] + 1

            if cnt[v] >= n:  # Path has n+ edges = negative cycle!
                return "negative cycle detected"

            if not st[v]:
                st[v] = True
                q.append(v)
```

**Logic:** Any simple path uses at most `n-1` edges. If a node is relaxed `n` times, a negative cycle must exist.

---

## Relationship

**SPFA is Bellman-Ford with queue optimization:**

- **Bellman-Ford:** "Check ALL edges every round, even if nothing changed"
- **SPFA:** "Only check edges from nodes that just improved"

Think of SPFA as:
- Optimized Bellman-Ford (for friendly graphs)
- Dijkstra for negative weights (without negative cycles)

---

## Common Pitfall: Why st[] array?

❌ **Without st[]:**
```python
if dist[v] > dist[u] + weight:
    dist[v] = dist[u] + weight
    q.append(v)  # Can add same node multiple times!
```
Queue might have: `[2, 3, 2, 2, 4, 2, ...]` - wasteful!

✅ **With st[]:**
```python
if dist[v] > dist[u] + weight:
    dist[v] = dist[u] + weight
    if not st[v]:  # Only add once
        st[v] = True
        q.append(v)
```
Queue: `[2, 3, 4]` - each node at most once until processed!

---

## When Each Algorithm Wins

### Bellman-Ford Wins:
```
Problem: "Find shortest path from 1 to n using at most k edges"
```
- Can easily modify outer loop to `for i in range(k)`
- SPFA doesn't naturally track edge count

### SPFA Wins:
```
Problem: "Find shortest path in graph with 10^5 nodes, 10^6 edges,
         some negative weights but no negative cycles"
```
- Bellman-Ford: Always 10^5 × 10^6 = 10^11 operations 💀
- SPFA: Usually ~10^6 operations ⚡

---

## Summary

**Use Bellman-Ford when:**
- Edge limit constraints
- Simplicity matters
- Small graphs

**Use SPFA when:**
- Large graphs
- Need speed
- Competitive programming (unless edge limits required)

**Both handle:**
- ✅ Negative edge weights
- ✅ Negative cycle detection (with modifications)
- ❌ Not faster than Dijkstra when all weights positive

---

## Fun Facts

- SPFA was invented by 段凡丁 (Duan Fanding), a Chinese computer scientist
- SPFA is sometimes called "Queue-optimized Bellman-Ford"
- In competitive programming, SPFA is often the go-to for negative weights
- SPFA can degrade to O(nm) on specially constructed adversarial graphs, but this rarely happens in practice