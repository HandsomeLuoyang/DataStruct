/*
-------------------------------------------------
   Author :       86178
   date:          2021/8/15 18:05
   Description :
-------------------------------------------------
*/
#include<bits/stdc++.h>

using namespace std;

const int INTMAX = 10000000;
const int NUMS = 1000; // 图中节点最大数量
typedef char data; // 通过这种方式设置节点中存储的数据类型

class Node {
public:
    data val;
};

class Edge {
public:
    int lIndex;
    int rIndex;
    int weight;

    Edge(int lIndex, int rIndex, int weight) : lIndex(lIndex), rIndex(rIndex), weight(weight) {}

    bool operator>(const Edge &other) const {
        return this->weight > other.weight;
    }

    bool operator<(const Edge &other) const {
        return this->weight <= other.weight;
    }
};


class Graph {
private:
    int curSize;
    int capacity;
    Node *nodes;
    vector<Edge *> edges;
    int *Matrix;

    /*
     * 深搜的递归部分函数
     */
    void DFS(int nIndex, int *visited) {
        cout << nodes[nIndex].val << " "; // 输出值
        for (int i = 0; i < curSize; i++) {
            if (Matrix[nIndex * capacity + i] && !visited[i]) {
                visited[i] = 1; // 设置为已访问
                DFS(i, visited); // 递归
            }
        }
    }

    /*
     * 找出给定值在大集合中的哪个小集合中
     */
    int getSetIndex(int index, vector<vector<int> > bigSet) {
        for (int i = 0; i < bigSet.size(); i++) {
            for (int j = 0; j < bigSet[i].size(); j++) {
                if (bigSet[i][j] == index) return i;
            }
        }
        return -1; // 代表目前不在集合当中
    }

public:
    /*
     * 构造函数
     */
    Graph() : curSize(0), capacity(NUMS) {
        nodes = new Node[capacity]; // 节点列表
        Matrix = new int[capacity * capacity]; // 邻接矩阵
        memset(Matrix, 0, capacity * capacity * sizeof(int)); // 初始化为0
    }

    /*
     * 打印邻接矩阵
     */
    void print_Matrix() {
        for (int i = 0; i < curSize; i++)
            for (int j = 0; j < curSize; j++) {
                cout << Matrix[i * capacity + j] << " ";
            }
        cout << endl;
    }

    /*
     * 添加节点
     */
    bool addNode(data val) {
        if (curSize > capacity)
            return false;
        nodes[curSize++].val = val;
        return true;
    }

    /*
     * 为无向图设置邻接矩阵
     * 格式:{{0,1,10}, {2,3,15}}
     */
    bool setMatrixForUndirectedMap(int start, int end, int weight) {
        // 首先检测是否合法
        if (start < 0 || start >= curSize || end < 0 || end >= curSize)
            return false;

        Matrix[start * capacity + end] = weight;
        Matrix[end * capacity + start] = weight;
        edges.push_back(new Edge(start, end, weight));
        edges.push_back(new Edge(end, start, weight));
        return true;
    }

    /*
     * 为有向图设置邻接矩阵
     * 格式:{{0,1,10}, {2,3,15}}
     */
    bool setMatrixForDirectedMap(int start, int end, int weight) {
        // 首先检测是否合法
        if (start < 0 || start >= curSize || end < 0 || end >= curSize)
            return false;

        Matrix[start * capacity + end] = weight;
        edges.push_back(new Edge(start, end, weight));
        return true;
    }

    /*
     * 打印邻接矩阵
     */
    void printMatrix() {
        for (int i = 0; i < curSize; i++) {
            for (int j = 0; j < curSize; j++) {
                cout << Matrix[i * capacity + j] << " ";
            }
            cout << endl;
        }
    }

    /*
     * 从给定节点开始深度优先遍历
     */
    void depthTraverse(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize]; // 初始化visited列表
        memset(visited, 0, curSize * sizeof(int));
        visited[nIndex] = 1;
        DFS(nIndex, visited);
    }


    /*
     * 从给定节点开始广度优先遍历
     */
    void broadTraverse(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize]; // 初始化visited列表
        memset(visited, 0, curSize * sizeof(int));
        visited[nIndex] = 1;

        queue<int> q;
        q.push(nIndex);
        while (!q.empty()) {
            int temp_index = q.front();
            q.pop();
            cout << nodes[temp_index].val << " ";

            for (int i = 0; i < curSize; i++) {
                if (Matrix[temp_index * capacity + i] && !visited[i]) {
                    q.push(i);
                    visited[i] = 1;
                }
            }

        }
    }

    /*
     * Prim算法求最小生成树
     */
    void prim(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize];
        memset(visited, 0, curSize * sizeof(int));
        visited[nIndex] = 1;
        set<Edge> edgeSet;

        priority_queue<Edge, vector<Edge>, greater<Edge> > pq;
        while (edgeSet.size() < curSize - 1) {
            // 每次对当前节点拿到它的所有连接的边,并且这条边另外一边所连接的节点需要是未访问过的
            for (int i = 0; i < curSize; i++) {
                if (Matrix[nIndex * capacity + i] && !visited[i]) {
                    // 将边加入最小堆
                    Edge curEdge(nIndex, i, Matrix[nIndex * capacity + i]);
                    pq.push(curEdge);
                }
            }
            // 从边集中拿出权值最小的那条边，把右边的节点拿出来贯通
            Edge curEdge = pq.top();
            pq.pop();
            nIndex = curEdge.rIndex;
            visited[nIndex] = 1;
            edgeSet.insert(curEdge);
            cout << nodes[curEdge.lIndex].val << "----" << nodes[curEdge.rIndex].val << endl;
        }
    }

    /*
     * Kruskal算法求最小生成树
     */
    void kruskal() {
        priority_queue<Edge, vector<Edge>, greater<> > small_heap;
        for (int i = 0; i < edges.size(); i++) {
            small_heap.push(*edges[i]);
        }

        vector<vector<int> > bigSet;
        set<Edge> edgeSet;
//        cout << "总大小：" << curSize << endl;
        while (edgeSet.size() < curSize - 1) {
//            cout << "大小：" << edgeSet.size() << endl;
            Edge curEdge = small_heap.top(); // 选出当前权最小的边
            small_heap.pop(); // 弹出边
            // 判断边两头节点的情况

            int lIndex = curEdge.lIndex, rIndex = curEdge.rIndex;
            // 获取左右节点分别所在集合序号
            int lSet = getSetIndex(lIndex, bigSet), rSet = getSetIndex(rIndex, bigSet);

            // 1.如果属于同一集合（同一连通分量），舍弃这条边
            if (lSet != -1 && lSet == rSet) continue;

                // 2.如果都还不属于某个集合的话
            else if (lSet == -1 && lSet == rSet) {
                // 构成新集合
                vector<int> newSet;
                newSet.push_back(lIndex);
                newSet.push_back(rIndex);
                bigSet.push_back(newSet);
            }

                // 3.左节点打单，右节点有集合
            else if (lSet == -1 && lSet != rSet) {
                // 收留左节点
                bigSet[rSet].push_back(lIndex);
            }

                // 4.右节点打单，左节点有集合
            else if (rSet == -1 && lSet != rSet) {
                // 收留右节点
                bigSet[lSet].push_back(rIndex);
            }

                // 5.两个节点都有集合，合并集合
            else {
                for (int i = 0; i < bigSet[rSet].size(); i++) {
                    // 右节点所在集合元素全部加入左节点所在集合
                    bigSet[lSet].push_back(bigSet[rSet][i]);
                }
                // 从大集合中删除右节点所在集合
                bigSet.erase(bigSet.begin() + rSet);
            }

            // 处理完节点的集合问题之后，如果之前没有continue，那么这条边就被选中加入了最小生成树了
            edgeSet.insert(curEdge);
            cout << nodes[lIndex].val << " --- " << nodes[rIndex].val << endl;
        }
    }

    /*
     * Dijkstra 算法
     */
    void dijkstra(int nIndex) {
        int flag[curSize];
        int dist[curSize];
        int prev[curSize];
        memset(flag, 0, curSize * sizeof(int));
        memset(prev, 0, curSize * sizeof(int));

        // 初始化dist数组
        for (int i = 0; i < curSize; i++) {
            if (Matrix[nIndex * capacity + i]) {
                dist[i] = Matrix[nIndex * capacity + i];
            } else {
                dist[i] = INTMAX;
            }
        }

        flag[nIndex] = 1;
        dist[nIndex] = 0;

        int k = -1;// 用来记录每一次从dist中找出的最短路径的编号
        for (int _ = 0; _ < curSize; _++) {
            int min = INTMAX;
            for (int i = 0; i < curSize; i++) {
                if (!flag[i] && dist[i] < min) {
                    min = dist[i];
                    k = i;
                }
            }
            // 找完之后，k就是短的那条路径的下标，这个节点已经确定！
            flag[k] = 1;

            // 开始利用这各节点更新距离列表
            for (int i = 0; i < curSize; i++) {
                if (!flag[i]) {
                    int distance = Matrix[k * capacity + i] == 0 ? INTMAX : Matrix[k * capacity + i];
                    if (dist[i] > dist[k] + distance) {
                        dist[i] = dist[k] + distance;
                        prev[i] = k;
                    }
                }
            }

        }
        for (int i = 0; i < curSize; i++) {
            cout << dist[i] << " ";
        }

    }

    /*
     * Floyd 最短路径算法
     */
    void floyd() {
        int A[curSize * curSize];
        int Path[curSize * curSize];

        // 初始化A矩阵，不相连的距离设置成为无穷大
        // Path矩阵初始化为自己
        for (int i = 0; i < curSize; i++) {
            for (int j = 0; j < curSize; j++) {
                Path[i * curSize + j] = j;
                if (i == j) {
                    A[i * curSize + j] = 0;
                    continue;
                }
                int val = Matrix[i * capacity + j];
                A[i * curSize + j] = val == 0 ? INTMAX : val;
            }
        }


        // 开始迭代更新
        for (int k = 0; k < curSize; k++) {
            // k代表选择的中间点
            for (int i = 0; i < curSize; i++) {
                for (int j = 0; j < curSize; j++) {
                    if (i == j || i == k || j == k) continue;
                    int distance = A[i * curSize + k] + A[k * curSize + j];
                    distance = distance == 0 ? INTMAX : distance;
                    if (distance < A[i * curSize + j]) {
                        A[i * curSize + j] = distance;
                        Path[i * curSize + j] = k;
                    }
                }
            }
        }

        for (int i = 0; i < curSize; i++) {
            for (int j = 0; j < curSize; ++j) {
                cout << A[i * curSize + j] << " ";
            }
            cout << endl;
        }

    }
};


int main() {
    Graph g;
    // 添加节点
    g.addNode('a');
    g.addNode('b');
    g.addNode('c');
    g.addNode('d');
    g.addNode('e');
    g.addNode('f');

    // 添加边
    g.setMatrixForUndirectedMap(0, 1, 20);
    g.setMatrixForUndirectedMap(1, 2, 10);
    g.setMatrixForUndirectedMap(2, 3, 5);
    g.setMatrixForUndirectedMap(0, 5, 3);
    g.setMatrixForUndirectedMap(1, 4, 2);
    g.setMatrixForUndirectedMap(4, 2, 5);


    g.printMatrix();
    cout << "深度优先搜索: " << endl;
    g.depthTraverse(0);
    cout << endl;
    cout << "广度优先搜索: " << endl;
    g.broadTraverse(0);
    cout << endl;
    cout << "kruskal最小生成树: " << endl;
    g.kruskal();
    cout << endl;
    cout << "prim最小生成树: " << endl;
    g.prim(0);
    cout << endl;
    cout << "dijkstra最短路径: " << endl;
    g.dijkstra(1);
    cout << endl;
    cout << endl;
    cout << "floyd最短路径: " << endl;
    g.floyd();

    return 0;
}