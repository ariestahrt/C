def dijkstra(graph, source, N):
    jarak = [float('inf')] * N

    queue=[]
    queue.append(source)
    jarak[source] = 0

    while queue:
        top=queue.pop()
        for element in graph[top]:
            dst = element[0]
            weight = element[1]
            if jarak[dst] > jarak[top] + weight:
                jarak[dst] = jarak[top] + weight
                queue.insert(0,dst)
    # print(jarak)
    return jarak

N,M,Q=input().split()
N=int(N)
M=int(M)
Q=int(Q)

graph = [None] * N
for i in range(0,N):
    graph[i]=[]

for i in range(0,M):
    u,v,w=input().split()
    u=int(u) - 1
    v=int(v) - 1
    w=int(w)

    graph[u].append([v,w])
    graph[v].append([u,w])

total = 0

from_list = []
from_dict = {}

for i in range(0,Q):
    X=int(input())-1
    from_list.append(X)
    if X not in from_dict.keys():
        from_dict[X]=dijkstra(graph,X,N)
    
    if i > 0:
        total += from_dict[from_list[i-1]][X]

print(total)
