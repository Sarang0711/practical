#include<iostream>
#include<omp.h>
#include<stack>
#include<limits.h>
#include<vector>

using namespace std;

const int MAX = INT_MAX;
vector<int> graph[1000];
bool visited[1000];

void bfs(int node) {
    queue<int>q;
    q.push(node);
    visited[node] = true;

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        cout<<curr<<" ";

        #pragma parallel for
        for(int i=0; i<graph[curr].size(); i++) {
            int adj = graph[curr][i];
            if(!visited[adj]) {
                #pragma omp critical 
                {
                    visited[adj] = true;
                    q.push(adj);
                }
            }
        }
    }
}

void dfs(int node) {
    stack<int>s;
    s.push(node);

    while(!s.empty()) {
        int curr_node = s.top();
        cout<<curr_node<<" ";
        s.pop();
        if(!visited[curr_node]) {
            visited[curr_node] = true;
        }

        #pragma omp parallel for
        for(int i=0; i<graph[curr_node].size(); i++) {
            int adj_node = graph[curr_node][i];
            if(!visited[adj_node]) {
                s.push(adj_node);
            }
        }
    }
}


int main() {
    int n, m, start_node;
    cout<<"Enter the number of nodes, no of edges & the starting node \n";
    cin>>n >> m>> start_node;
    cout<<"Enter the adjacent nodes \n";
    for(int i=0; i<m; i++) {
        int u, v;
        cin>>u>>v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for(int i=0; i<n; i++) {
        visited[i] = false;
    }

    dfs(start_node);
    


    return 0;
}