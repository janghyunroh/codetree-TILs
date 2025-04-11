/*
여러 간선 가능 --> 그래프 구성 시 최소값만 적용
자기 자신 간선 가능 --> 

*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF (~0U>>2)
#define MAX_CITIES 2000
#define MAX_ID 30000

using namespace std;

int N, M;
int graph[MAX_CITIES][MAX_CITIES];
int dist[MAX_CITIES];

bool isMade[MAX_ID] = {false, }; // idx로 pq에 존재하는지 빠르게 검색하는 용
bool isCanceled[MAX_ID] = {false, };
int S;

//여행 상품 구조체
struct package {
    int id;
    int revenue;
    int dest;
    int profit; // revenue - dist[dest]

    //정렬 위한 구조체!
    struct Comparator {
        bool operator()(const package& a, const package& b) const {
            if(a.profit == b.profit) return a.id > b.id;
            return a.profit < b.profit;
        }
    };
};

//여행 상품 리스트(우선순위 큐 사용)
priority_queue<package, vector<package>, package::Comparator> pq;

//debugging
void display(int step, int T) {
    cout << step << "번째 쿼리: " << T << '\n';
    cout << "상품 개수:" << pq.size() << '\n';
    for(int i =0; i < MAX_ID; i++) {
        if(isMade[i]) cout << i << ' ';
    }
    cout << '\n';
}


// S로부터 나머지 모든 노드까지의 거리 계산
void dijkstra() {
    bool visit[MAX_CITIES];
    for(int i = 0; i < N; i++) {
        dist[i] = INF;
        visit[i] = false;
    }

    dist[S] = 0;
    for(int i = 0; i < N - 1; i++) {
        int v = 0; 
        int minDist = INF;
        for(int j = 0; j < N; j++) {
            if(!visit[j] && minDist > dist[j]) {
                v = j;
                minDist = dist[j];
            }
        }

        visit[v] = true;

        for(int j= 0; j < N; j++) {
            if(!visit[j] && dist[v] != INF && graph[v][j] != INF && dist[j] > dist[v] + graph[v][j]) {
                dist[j] = dist[v] + graph[v][j];
            }
        }
    }
}

// 쿼리 100. Build Land
// 입력 기반 graph 생성
void buildLand() {
    cin >> N >> M;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            graph[i][j] = INF;
        }
        graph[i][i] = 0;
    }

    for(int i = 0; i < M; i++) {
        int u, v, w; cin >> u >> v >> w;
        graph[u][v] = min(graph[u][v], w);
        graph[v][u] = min(graph[u][v], w);;
    }
    
}

// 쿼리 200. 여행 상품 생성
// priority queue에 insert
void addPackage(int id, int revenue, int dest) {
    package p;
    p.id = id;
    p.revenue = revenue;
    p.dest = dest;
    p.profit = p.revenue - dist[p.dest];

    isMade[id] = true;
    pq.push(p);
}

// 쿼리 300. 여행 상품 취소
// priority queue에서 id 검색 및 delete
// 없으면 -1 출력
void cancelPackage(int id) {
    if(isMade[id]) isCanceled[id] = true;
    //else cout << -1 << '\n';
}

// 쿼리 400. 최적 상품 판매 후 제거
// priority queue에서 front의 id 검색, 출력 및 delete
// 없으면 -1 출력
int sellPackage() {

    //PQ에서 
    while(!pq.empty()) {
        package p = pq.top();
        if(p.profit < 0) break;
        pq.pop();
        if(!isCanceled[p.id]) return p.id;
    }
    return -1;
}

// 쿼리 500. 여행 상품 출발지 변경
// dijkstra로 dist배열 갱신
// priority queue에서 cost와 profit update

void updateStart() {

    cin >> S;
    vector<package> packages;
    dijkstra();
    while(!pq.empty()) {
        packages.push_back(pq.top());
        pq.pop();
    }
    for (package p : packages) {
        addPackage(p.id, p.revenue, p.dest);
    }
}

int main() {
    int Q, id, revenue, dest;
    cin >> Q;

    int step = 1;
    while(Q--) {
        int T; cin >> T;
        switch(T) {
            case 100:
                buildLand();
                dijkstra();
                break;
            case 200: 
                cin >> id >> revenue >> dest;
                addPackage(id, revenue, dest);
                break;
            case 300:
                cin >> id;
                cancelPackage(id);
                break;
            case 400:
                cout << sellPackage() << '\n';
                break;
            case 500:
                updateStart();
                break;
        }

        //debugging
        //display(step, T);
        //step++;
    }
    return 0;
}