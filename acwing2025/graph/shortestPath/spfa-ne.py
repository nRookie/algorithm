import sys
from collections import deque

n,m = map(int, sys.stdin.readline().split()) 

g = [ [] for _ in range(n + 1)]
for _ in range(m):
    a,b,c = map(int, sys.stdin.readline().split())
    g[a].append((b,c))

def spfa_ne():
    INF = int(1e9)
    dist = [INF] * (n + 1)
    dist[1] = 0
    st = [False] * (n + 1)
    q = deque()
    cnt = [0] * (n + 1)

    for i in range(1, n + 1):
        q.append(i)
        st[i] = True

    while q:
        u = q.popleft()
        st[u] = False

        for v, d in g[u]:
            if dist[v] > dist[u] + d:
                dist[v] = dist[u] + d
                cnt[v] = cnt[u] + 1
                if cnt[v] >= n:
                    return "Yes"
                if not st[v]:
                    st[v] = True
                    q.append(v)

    return "No"

print(spfa_ne())