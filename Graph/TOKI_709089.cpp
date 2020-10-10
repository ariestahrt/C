#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> iPair;

// Class Graph
class Graph{
    int N;
    list<iPair> *adj;
    public:
        Graph(int N); // Inisiasi graph
        void addEdge(int u, int v, int w); // Menambahkan Edge
        int* dijkstra(int src); // Dijkstra alogrithm
};

Graph::Graph(int N){
    this->N = N;
    adj = new list<iPair> [N];
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back(make_pair(v,w));
    adj[v].push_back(make_pair(u,w));
}

int* Graph::dijkstra(int src){
    priority_queue<int> pqueue;

    int* path = new int[N];
    for(int i=0; i<N; i++) path[i] = INT_MAX;

    pqueue.push(src);
    path[src] = 0;

    while(!pqueue.empty()){
        int u = pqueue.top();
        pqueue.pop();
        for(iPair element:adj[u]){
            int v=element.first;
            int w=element.second;
            if(path[v] > path[u]+w){
                path[v] = path[u]+w;
                pqueue.push(v);
            }
        }
    }
    return path;
}

int main(){
    ios_base::sync_with_stdio(false);
    int N,M,Q;
    cin >> N >> M >> Q;
    Graph g(N);
    while(M--){
        int u,v,w;
        cin >> u >> v >> w;
        g.addEdge(u-1,v-1,w);
    }

    map<int,int*> map_path; // Menyimpan path yang dicari
    vector<int> listQi; // List Q yang akan dikunjungi
    int total=0;
    for(int i=0; i<Q; i++){
        int Qi;
        cin >> Qi;
        Qi-=1;
        listQi.push_back(Qi); // Masukkan Qi kedalam List Q
        if(i!=Q-1){ // path pada Qi terakhir tidak perlu dicari
            if(map_path.find(Qi) == map_path.end()){ // Apabila path belum ada di map
                map_path.insert({Qi, g.dijkstra(Qi)});
            }
        }

        if(i>0) total+=map_path[listQi[i-1]][Qi]; // Hitung total dari i=1 s/d i=Q
    }

    cout << total << endl; // Keluarkan total
    return 0;
}
