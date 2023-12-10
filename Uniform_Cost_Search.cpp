#include <bits/stdc++.h>
#include<climits>
using namespace std;

const int N = 1e6;
vector<pair<int, int>> adj[N];


void UCS(int start, int goal, vector<bool> &vis,int nodes){
    int curr, curr_cost;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> dist(nodes);
    vector<int> parent(nodes,-1);
    for(int i=0;i<nodes; i++){
        dist[i]= INT_MAX;
    }

    pq.push({0,start});
    dist[start] = 0;
//    cout<<start<<" ";

    while(!pq.empty()){
        curr = pq.top().second;
        curr_cost = pq.top().first;
        pq.pop();

        if(vis[curr]==true){
            continue;
        }
        cout << curr << " ";
        vis[curr] = true;
        if(curr == goal){
//            cout<<curr<<endl;
            vector<int> path;
            int node = goal;
            while(node != -1){
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(),path.end());
            cout<<endl<<"Optimal Path= ";
            for(int i=0; i<path.size();i++){
                cout<<path[i]<<" ";
            }
            cout<<endl<<"Optimal Cost= "<<curr_cost<<endl;

            cout<<"Goal Found"<<endl;
            break;
        }

        vector<pair<int,int>> :: iterator it;
        for(it= adj[curr].begin(); it!=adj[curr].end(); it++){
            int next_node = it->second;
            int edge_cost = it->first;
            if(vis[next_node]==false){

                if(dist[curr]+edge_cost<dist[next_node]){
                    dist[next_node]=dist[curr]+edge_cost;

                    pq.push({dist[next_node],next_node});
                    parent[next_node]=curr;
                }
            }

        }


    }




}


int main()
{

    int n, m, x, y, r, g, cost;  // no. of nodes, edges, and x, y are helpful in input
    cout << "Enter the no. of nodes: ";
    cin >> n;
    cout << endl << "Enter the no. of edges: ";
    cin >> m;
    cout << "Enter x and y for making edges to vertices" << endl;
    vector<bool> vis(n);
    for(int i=0; i<n; i++){
        vis[i]=false;
    }
    for (int i = 0; i < m; i++)
    {
        cout <<endl<< "Enter x: ";
        cin >> x;
        cout << endl<< "Enter y: ";
        cin >> y;
        cout<<endl<<"Enter cost: ";
        cin>>cost;
        adj[x].push_back({cost,y});
        adj[y].push_back({cost,x});

    }
    cout<<endl<<"Enter root node"<<endl;
    cin>>r;
    cout<<"Enter Goal Node"<<endl;
    cin>>g;
    UCS(r,g,vis,n);

    return 0;
}