import sys
import heapq 
intput = sys.stdin.readline


n, m = map(int, input().split())

g = [ [] for _ in range(n + 1 )]
for _ in range(m):
    a, b, c = map(int, input().split())
    g[a].append((b, c))

def dijkstra():
    dist = [float('inf')] * (n + 1)
    dist[1] = 0
    pq = []
    heapq.heappush(pq, (0, 1))

    while pq:
        d, u = heapq.heappop(pq)
        if d != dist[u]:
            continue
        
        for v, d in g[u]:
            if dist[v] > dist[u] + d:
                dist[v] = dist[u] + d
                heapq.heappush(pq, (dist[v], v))
    

    if dist[n] != float('INF'):
        print(dist[n])
    else:
        print('-1')

dijkstra()

        

