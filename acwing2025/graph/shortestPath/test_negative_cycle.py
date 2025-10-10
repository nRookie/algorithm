"""
Test cases to demonstrate SPFA with and without negative cycles
"""

from collections import deque

def spfa_with_detection(n, edges, start, end):
    """SPFA with negative cycle detection"""
    g = [[] for _ in range(n + 1)]
    for a, b, c in edges:
        g[a].append((b, c))
    
    INF = float('inf')
    dist = [INF] * (n + 1)
    dist[start] = 0
    st = [False] * (n + 1)
    cnt = [0] * (n + 1)  # Key difference!
    
    q = deque([start])
    st[start] = True
    
    iterations = 0  # For demonstration
    while q:
        iterations += 1
        if iterations > 10000:  # Safety limit
            return "Too many iterations - likely negative cycle"
        
        u = q.popleft()
        st[u] = False
        
        for v, d in g[u]:
            if dist[v] > dist[u] + d:
                dist[v] = dist[u] + d
                cnt[v] = cnt[u] + 1
                
                if cnt[v] >= n:
                    return f"NEGATIVE CYCLE (detected after {iterations} iterations)"
                
                if not st[v]:
                    st[v] = True
                    q.append(v)
    
    if dist[end] == INF:
        return f"impossible (iterations: {iterations})"
    return f"distance: {dist[end]} (iterations: {iterations})"


# Test Case 1: Normal graph with negative weight (NO CYCLE)
print("=" * 60)
print("Test 1: Graph with NEGATIVE WEIGHT but NO CYCLE")
print("=" * 60)
edges1 = [
    (1, 2, -5),  # Negative weight
    (2, 3, 3),
    (1, 3, 10)
]
result1 = spfa_with_detection(3, edges1, 1, 3)
print(f"Result: {result1}")
print("Expected: distance: -2 (via 1 -> 2 -> 3)")
print()

# Test Case 2: Graph with NEGATIVE CYCLE
print("=" * 60)
print("Test 2: Graph with NEGATIVE CYCLE")
print("=" * 60)
print("Graph: 1 -> 2 -> 3 -> 2 (cycle 2->3->2 has weight -1)")
edges2 = [
    (1, 2, 1),
    (2, 3, -2),  # Cycle: 2 -> 3 -> 2 has total weight -1
    (3, 2, -2),
    (3, 4, 1)
]
result2 = spfa_with_detection(4, edges2, 1, 4)
print(f"Result: {result2}")
print("Expected: NEGATIVE CYCLE detected")
print()

# Test Case 3: Normal graph (all positive weights)
print("=" * 60)
print("Test 3: Normal graph (positive weights only)")
print("=" * 60)
edges3 = [
    (1, 2, 2),
    (2, 3, 3),
    (1, 3, 10)
]
result3 = spfa_with_detection(3, edges3, 1, 3)
print(f"Result: {result3}")
print("Expected: distance: 5")
print()

# Test Case 4: Unreachable node
print("=" * 60)
print("Test 4: Unreachable destination")
print("=" * 60)
edges4 = [
    (1, 2, 5),
    # Node 3 is unreachable
]
result4 = spfa_with_detection(3, edges4, 1, 3)
print(f"Result: {result4}")
print("Expected: impossible")

