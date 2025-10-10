from collections import deque
import sys

n,m = map(int, sys.stdin.readline().split())


g = [[] for _ in range(n + 1) ]

for _ in range(m):
    a,b,c = map(int, sys.stdin.readline().split())
    g[a].append((b, c))



def spfa():
    INF = 1e9
    dist = [INF] * (n + 1)
    dist[1] = 0
    st = [False] * (n + 1)

    q = deque()
    q.append(1)
    st[1] = True 
    while q:
        u = q.popleft()
        st[u] = False

        for v,d in g[u]:
            if dist[v] > dist[u] + d:
                dist[v] = dist[u] + d
                if not st[v]:
                    st[v] = True
                    q.append(v)
    return dist[n] if dist[n] < INF // 2 else "impossible"


print(spfa())