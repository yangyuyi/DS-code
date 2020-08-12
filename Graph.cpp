#include <iostream>
#include <vector>
#include <queue>

#define UNVISITED 0
#define VISITED 1
#define INFINITY 0x3FFFFFFF
using namespace std;

class Edge {
public:
    int from, to, weight;

    Edge();

    Edge(int from, int to, int weight);
};

Edge::Edge() {
    from = -1;
    to = -1;
    weight = 0;
}

Edge::Edge(int from, int to, int weight) {
    this->from = from;
    this->to = to;
    this->weight = weight;
}

class Graph {
public:
    int numVertex;
    int numEdge;
    int *Mark;

    explicit Graph(int numVertex);

    ~Graph();

    bool isEdge(Edge oneEdge);

    virtual Edge FirstEdge(int oneVertex) = 0;

    virtual Edge NextEdge(Edge preEdge) = 0;
};

Graph::Graph(int numVertex) {
    this->numVertex = numVertex;
    numEdge = 0;
    Mark = new int[numVertex];
    for (int i = 0; i < numVertex; i++) Mark[i] = UNVISITED;
}

Graph::~Graph() {
    delete[]Mark;
}

bool Graph::isEdge(Edge oneEdge) {
    return oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.from >= 0 && oneEdge.from < numVertex &&
           oneEdge.to >= 0 && oneEdge.to < numVertex;
}

class GraphMatrix : public Graph {
private:
    int **Matrix{};
public:
    explicit GraphMatrix(int numVertex);

    ~GraphMatrix();

    Edge FirstEdge(int oneVertex) override;

    Edge NextEdge(Edge preEdge) override;

    void BuildGraphMatrix();
};

GraphMatrix::GraphMatrix(int numVertex) : Graph(numVertex) {
    Matrix = (int **) new int *[numVertex];
    for (int i = 0; i < numVertex; i++) Matrix[i] = new int[numVertex];
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++)
            Matrix[i][i] = 0;
}

GraphMatrix::~GraphMatrix() {
    for (int i = 0; i < numVertex; i++) delete[]Matrix[i];
}

Edge GraphMatrix::FirstEdge(int oneVertex) {
    Edge first;
    first.from = oneVertex;
    for (int i = 0; i < numVertex; i++)
        if (Matrix[oneVertex][i] != 0) {
            first.to = i;
            first.weight = Matrix[oneVertex][i];
            break;
        }
    return first;
}

Edge GraphMatrix::NextEdge(Edge preEdge) {
    int from = preEdge.from;
    Edge next;
    if (preEdge.to >= numVertex) return next;
    for (int i = preEdge.to + 1; i < numVertex; i++)
        if (Matrix[from][i] != 0) {
            next.to = i;
            next.weight = Matrix[from][i];
            break;
        }
    next.from = from;
    return next;
}

void GraphMatrix::BuildGraphMatrix() {
    cout << "Please input adjacent matrix of your graph(numV*numV):" << endl;
    for (int i = 0; i < numVertex; i++)
        for (int j = 0; j < numVertex; j++) {
            cin >> Matrix[i][j];
            if (Matrix[i][j] > 0) numEdge++;
        }
}

class Dist {
public:
    int index;
    int length;
    int pre;
};

struct cmp {
    bool operator()(Dist d1, Dist d2) {
        return d1.length > d2.length;
    }
};

void Dijkstra(Graph &G, int start, Dist *&Dis) {
    int numV = G.numVertex;
    Dis = new Dist[numV];
    for (int i = 0; i < numV; i++) {
        G.Mark[i] = UNVISITED;
        Dis[i].index = i;
        Dis[i].length = INFINITY;
        Dis[i].pre = start;
    }

    Dis[start].length = 0;
    priority_queue<Dist, vector<Dist>, cmp> Heap;
    Heap.push(Dis[start]);
    for (int i = 0; i < numV; i++) {
        bool found = false;
        Dist dis;
        while (!Heap.empty()) {
            dis = Heap.top();
            Heap.pop();
            if (G.Mark[dis.index] == UNVISITED) {
                found = true;
                break;
            }
        }
        if (!found) break;
        int vertex = dis.index;
        G.Mark[vertex] = VISITED;
        for (Edge e = G.FirstEdge(vertex); G.isEdge(e); e = G.NextEdge(e))
            if (Dis[e.to].length > Dis[vertex].length + e.weight) {
                Dis[e.to].length = Dis[vertex].length + e.weight;
                Dis[e.to].pre = vertex;
                Heap.push(Dis[e.to]);
            }
    }
}

void Floyd(Graph &G, Dist **&Dis) {
    int numV = G.numVertex;
    Dis = (Dist **) new Dist *[numV];
    for (int i = 0; i < numV; i++) {
        Dis[i] = new Dist[numV];
    }
    for (int i = 0; i < numV; i++)
        for (int j = 0; j < numV; j++) {
            if (i == j) {
                Dis[i][j].length = 0;
                Dis[i][j].pre = i;
            } else {
                Dis[i][j].length = INFINITY;
                Dis[i][j].pre = -1;
            }
        }
    for (int i = 0; i < numV; i++)
        for (Edge e = G.FirstEdge(i); G.isEdge(e); e = G.NextEdge(e)) {
            Dis[i][e.to].length = e.weight;
            Dis[i][e.to].pre = i;
        }

    for (int k = 0; k < numV; k++)
        for (int i = 0; i < numV; i++)
            for (int j = 0; j < numV; j++)
                if (Dis[i][j].length > Dis[i][k].length + Dis[k][j].length) {
                    Dis[i][j].length = Dis[i][k].length + Dis[k][j].length;
                    Dis[i][j].pre = Dis[k][j].pre;
                }
}

int minVertex(Graph &G, Dist *&Dis) {
    int v = 0;
    int numV = G.numVertex;
    for (int i = 0; i < numV; i++)
        if (G.Mark[i] == UNVISITED) {
            v = i;
            break;
        }
    for (int i = v + 1; i < numV; i++)
        if (G.Mark[i] == UNVISITED && Dis[i].length < Dis[v].length) v = i;
    return v;
}

bool Prim(Graph &G, int start, Edge *&MST) {
    int numE = 0;
    int numV = G.numVertex;
    MST = new Edge[numV - 1];
    Dist *Dis;
    Dis = new Dist[numV];
    for (int i = 0; i < numV; i++) {
        G.Mark[i] = UNVISITED;
        Dis[i].length = INFINITY;
        Dis[i].pre = start;
    }
    Dis[start].length = 0;
    G.Mark[start] = VISITED;
    int v = start;
    for (int i = 0; i < numV - 1; i++) {
        if (Dis[v].length == INFINITY) return false;
        for (Edge e = G.FirstEdge(v); G.isEdge(e); e = G.NextEdge(e)) {
            if (G.Mark[e.to] == UNVISITED && Dis[e.to].length > e.weight) {
                Dis[e.to].length = e.weight;
                Dis[e.to].pre = v;
            }
        }
        v = minVertex(G, Dis);
        G.Mark[v] = VISITED;
        Edge edge(Dis[v].pre, v, Dis[v].length);
        MST[numE++] = edge;
    }
    return true;
}

void PrintPath(Dist *DIST, int i) {
    if (i == 0) {
        cout << "v" << i;
        return;
    } else {
        PrintPath(DIST, DIST[i].pre);
        cout << " -> v" << i;
    }
}

int main() {
    int numV;
    cout << "四 18072021[21] 杨雨怡 上机题4" << endl;
    cout << "Please enter vertex number of your graph:";
    cin >> numV;
    GraphMatrix GM(numV);
    GM.BuildGraphMatrix();

    cout << "Dijkstra:" << endl;
    cout << "start:vertex 0" << endl;
    Dist *Dijkstra_D;
    Dijkstra(GM, 0, Dijkstra_D);
    for (int i = 0; i < numV; i++)
        if (Dijkstra_D[i].length == INFINITY)cout << "INFINITY" << ' ';
        else {
            cout << "Distance of vertex " << i << ':' << Dijkstra_D[i].length;
            cout << " Path:";
            PrintPath(Dijkstra_D, i);
            cout << endl;
        }
    cout << endl;

    cout << "Floyd:" << endl;
    Dist **Floyd_D;
    Floyd(GM, Floyd_D);
    cout << "Floyd Distance Matrix:" << endl;
    for (int i = 0; i < numV; i++) {
        for (int j = 0; j < numV; j++)
            if (Floyd_D[i][j].length == INFINITY)
                cout << "INF" << ' ';
            else cout << Floyd_D[i][j].length << ' ';
        cout << endl;
    }
    cout << endl;

    cout << "Prim:" << endl;
    Edge *MST;
    int cost = 0;
    if (Prim(GM, 0, MST)){
        for (int i = 0; i < numV - 1; i++) {
            cout << "Edge: vertex_from-v" << MST[i].from << " vertex_to-v" << MST[i].to << " weight:" << MST[i].weight
                 << endl;
            cost += MST[i].weight;
        }
        cout << "Total cost:" << cost << endl;
    } else cout << "No MST!" << endl;
    return 0;
}
