#include <bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 
  
typedef pair<int, int> iPair; 
  
void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt) 
{ 
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void shortestPath(vector<pair<int,int> > adj[], int V, int src, map<int,int*> *themap)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
    int* dist = (int*) malloc( V * sizeof(int));
    memset(dist, INF, V * sizeof(int));

    // printf("Vertex Distance from Source\n"); 
    // for (int k = 0; k < V; ++k) 
    //     printf("%d \t\t %d\n", k, dist[k]); 

    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 

        for (auto x : adj[u]) 
        {
            int v = x.first; 
            int weight = x.second; 

            if (dist[v] > dist[u] + weight) 
            {
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    }
    
    (*themap)[src] = dist;
}

int main() 
{
    ios_base::sync_with_stdio(false);

    int V;
    cin >> V;
    vector<iPair> adj[V]; 
    map<int,int*> mymap;

    for(int i=0; i<V; i++){
        int a,b,weight;
        cin >> a >> b >> weight;
        addEdge(adj, a, b, weight);
    }

    mymap.insert({0,NULL});
    shortestPath(adj, V, 0, &mymap);

    int n, citysource;
    citysource=0;
    cin >>n;

    while(n--){
        int type, arg;
        cin >> type >> arg;
        if(type==1){
            if(mymap[citysource][arg] == INF || arg >= V) cout << "#dirumahaja"<< endl ;
            else  cout << mymap[citysource][arg] << endl ;
        }else{
            if(mymap.count(arg) == 0){
                mymap.insert({arg,NULL});
                shortestPath(adj,V,arg,&mymap);
            }
            citysource=arg;
            cout << "Siap " << arg << endl;
        }
    }

    return 0; 
} 
