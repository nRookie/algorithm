from collections import deque
import sys

n, m = map(int, sys.stdin.readline().split())

g = [[] for _ in range(n + 1)]

for _ in range(m):
    a, b, c = map(int, sys.stdin.readline().split())
    g[a].append((b, c))


def spfa():
    """
    SPFA with negative cycle detection.
    
    Key idea: If a node is relaxed n or more times, there's a negative cycle.
    Why? Because shortest path in a graph with n nodes has at most n-1 edges.
    """
    INF = float('inf')
    dist = [INF] * (n + 1)
    dist[1] = 0
    st = [False] * (n + 1)  # whether node is in queue
    cnt = [0] * (n + 1)      # number of edges in shortest path to this node

    q = deque()
    q.append(1)
    st[1] = True
    
    while q:
        u = q.popleft()
        st[u] = False

        for v, d in g[u]:
            if dist[v] > dist[u] + d:
                dist[v] = dist[u] + d
                cnt[v] = cnt[u] + 1
                
                # Negative cycle detection
                if cnt[v] >= n:
                    return "NEGATIVE CYCLE DETECTED"
                
                if not st[v]:
                    st[v] = True
                    q.append(v)
    
    if dist[n] == INF:
        return "impossible"
    else:
        return dist[n]


print(spfa())

