import sys

n,m, k = map(int, sys.stdin.readline().split())

edges = []

for _ in range(m):
    a,b,c = map(int, sys.stdin.readline().split())
    edges.append((a,b,c))

def bellman_ford():
    INF = int(1e9)
    dist = [INF] * (n + 1)
    dist[1] = 0

    for _ in range(k):
        backup = dist[:]
        for a,b,c in edges:
            if dist[b] > backup[a] + c:
                dist[b] = backup[a] + c

    return "impossible" if dist[n] > (INF // 2) else dist[n]



print(bellman_ford())