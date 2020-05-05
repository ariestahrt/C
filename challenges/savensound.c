#include<bits/stdc++.h> 
using namespace std; 
# define INF 0x3f3f3f3f 
  
// iPair ==> Integer Pair 
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

    // cout << "To\tDistance" << endl;
    // for(int i=0; i<V; i++){
    //     cout << i << "\t" << dist[i] << endl;
    // }

    // vector<int> dist(V, INF);
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

    // cout << "To\tDistance" << endl;
    // for(int i=0; i<V; i++){
    //     cout << i << "\t" << dist[i] << endl;
    // }

    (*themap)[src] = dist;
}

void getLenght(int* data,int from, int to, int t){
    // int* data=mp[from];
    if(to >= t){
        cout << "#dirumahaja" << endl;
        return;
    }

    if(data[to] == INF){
        cout << "#dirumahaja" << endl;
        return;
    }

    cout << data[to] << endl;
    return;
}

// Driver program to test methods of graph class 
int main() 
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);    

    int V;
    cin >> V;
    vector<iPair> adj[V]; 
    map<int,int*> mymap;

    for(int i=0; i<V; i++){
        int a,b,weight;
        cin >> a >> b >> weight;
        addEdge(adj, a, b, weight);
    }

    //source =
    // vector<int> tempdistance(V, INF);
    int *tempdistance;
    mymap.insert({0,tempdistance});
    shortestPath(adj, V, 0, &mymap);

    int n, citysource;
    citysource=0;
    cin >>n;

    while(n--){
        int type, arg;
        cin >> type >> arg;
        if(type==1){
            getLenght(mymap[citysource],citysource, arg, V);
        }else{
            if(mymap.count(arg) == 0){
                mymap.insert({arg,tempdistance});
                shortestPath(adj,V,arg,&mymap);
            }
            citysource=arg;
            cout << "Siap " << arg << endl;
        }
    }

    return 0; 
} 
