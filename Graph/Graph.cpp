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
const int NUMS = 1000; // ͼ�нڵ��������
typedef char data; // ͨ�����ַ�ʽ���ýڵ��д洢����������

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
     * ���ѵĵݹ鲿�ֺ���
     */
    void DFS(int nIndex, int *visited) {
        cout << nodes[nIndex].val << " "; // ���ֵ
        for (int i = 0; i < curSize; i++) {
            if (Matrix[nIndex * capacity + i] && !visited[i]) {
                visited[i] = 1; // ����Ϊ�ѷ���
                DFS(i, visited); // �ݹ�
            }
        }
    }

    /*
     * �ҳ�����ֵ�ڴ󼯺��е��ĸ�С������
     */
    int getSetIndex(int index, vector<vector<int> > bigSet) {
        for (int i = 0; i < bigSet.size(); i++) {
            for (int j = 0; j < bigSet[i].size(); j++) {
                if (bigSet[i][j] == index) return i;
            }
        }
        return -1; // ����Ŀǰ���ڼ��ϵ���
    }

public:
    /*
     * ���캯��
     */
    Graph() : curSize(0), capacity(NUMS) {
        nodes = new Node[capacity]; // �ڵ��б�
        Matrix = new int[capacity * capacity]; // �ڽӾ���
        memset(Matrix, 0, capacity * capacity * sizeof(int)); // ��ʼ��Ϊ0
    }

    /*
     * ��ӡ�ڽӾ���
     */
    void print_Matrix() {
        for (int i = 0; i < curSize; i++)
            for (int j = 0; j < curSize; j++) {
                cout << Matrix[i * capacity + j] << " ";
            }
        cout << endl;
    }

    /*
     * ��ӽڵ�
     */
    bool addNode(data val) {
        if (curSize > capacity)
            return false;
        nodes[curSize++].val = val;
        return true;
    }

    /*
     * Ϊ����ͼ�����ڽӾ���
     * ��ʽ:{{0,1,10}, {2,3,15}}
     */
    bool setMatrixForUndirectedMap(int start, int end, int weight) {
        // ���ȼ���Ƿ�Ϸ�
        if (start < 0 || start >= curSize || end < 0 || end >= curSize)
            return false;

        Matrix[start * capacity + end] = weight;
        Matrix[end * capacity + start] = weight;
        edges.push_back(new Edge(start, end, weight));
        edges.push_back(new Edge(end, start, weight));
        return true;
    }

    /*
     * Ϊ����ͼ�����ڽӾ���
     * ��ʽ:{{0,1,10}, {2,3,15}}
     */
    bool setMatrixForDirectedMap(int start, int end, int weight) {
        // ���ȼ���Ƿ�Ϸ�
        if (start < 0 || start >= curSize || end < 0 || end >= curSize)
            return false;

        Matrix[start * capacity + end] = weight;
        edges.push_back(new Edge(start, end, weight));
        return true;
    }

    /*
     * ��ӡ�ڽӾ���
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
     * �Ӹ����ڵ㿪ʼ������ȱ���
     */
    void depthTraverse(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize]; // ��ʼ��visited�б�
        memset(visited, 0, curSize * sizeof(int));
        visited[nIndex] = 1;
        DFS(nIndex, visited);
    }


    /*
     * �Ӹ����ڵ㿪ʼ������ȱ���
     */
    void broadTraverse(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize]; // ��ʼ��visited�б�
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
     * Prim�㷨����С������
     */
    void prim(int nIndex) {
        if (nIndex < 0 || nIndex >= curSize) return;
        int visited[curSize];
        memset(visited, 0, curSize * sizeof(int));
        visited[nIndex] = 1;
        set<Edge> edgeSet;

        priority_queue<Edge, vector<Edge>, greater<Edge> > pq;
        while (edgeSet.size() < curSize - 1) {
            // ÿ�ζԵ�ǰ�ڵ��õ������������ӵı�,��������������һ�������ӵĽڵ���Ҫ��δ���ʹ���
            for (int i = 0; i < curSize; i++) {
                if (Matrix[nIndex * capacity + i] && !visited[i]) {
                    // ���߼�����С��
                    Edge curEdge(nIndex, i, Matrix[nIndex * capacity + i]);
                    pq.push(curEdge);
                }
            }
            // �ӱ߼����ó�Ȩֵ��С�������ߣ����ұߵĽڵ��ó�����ͨ
            Edge curEdge = pq.top();
            pq.pop();
            nIndex = curEdge.rIndex;
            visited[nIndex] = 1;
            edgeSet.insert(curEdge);
            cout << nodes[curEdge.lIndex].val << "----" << nodes[curEdge.rIndex].val << endl;
        }
    }

    /*
     * Kruskal�㷨����С������
     */
    void kruskal() {
        priority_queue<Edge, vector<Edge>, greater<> > small_heap;
        for (int i = 0; i < edges.size(); i++) {
            small_heap.push(*edges[i]);
        }

        vector<vector<int> > bigSet;
        set<Edge> edgeSet;
//        cout << "�ܴ�С��" << curSize << endl;
        while (edgeSet.size() < curSize - 1) {
//            cout << "��С��" << edgeSet.size() << endl;
            Edge curEdge = small_heap.top(); // ѡ����ǰȨ��С�ı�
            small_heap.pop(); // ������
            // �жϱ���ͷ�ڵ�����

            int lIndex = curEdge.lIndex, rIndex = curEdge.rIndex;
            // ��ȡ���ҽڵ�ֱ����ڼ������
            int lSet = getSetIndex(lIndex, bigSet), rSet = getSetIndex(rIndex, bigSet);

            // 1.�������ͬһ���ϣ�ͬһ��ͨ������������������
            if (lSet != -1 && lSet == rSet) continue;

                // 2.�������������ĳ�����ϵĻ�
            else if (lSet == -1 && lSet == rSet) {
                // �����¼���
                vector<int> newSet;
                newSet.push_back(lIndex);
                newSet.push_back(rIndex);
                bigSet.push_back(newSet);
            }

                // 3.��ڵ�򵥣��ҽڵ��м���
            else if (lSet == -1 && lSet != rSet) {
                // ������ڵ�
                bigSet[rSet].push_back(lIndex);
            }

                // 4.�ҽڵ�򵥣���ڵ��м���
            else if (rSet == -1 && lSet != rSet) {
                // �����ҽڵ�
                bigSet[lSet].push_back(rIndex);
            }

                // 5.�����ڵ㶼�м��ϣ��ϲ�����
            else {
                for (int i = 0; i < bigSet[rSet].size(); i++) {
                    // �ҽڵ����ڼ���Ԫ��ȫ��������ڵ����ڼ���
                    bigSet[lSet].push_back(bigSet[rSet][i]);
                }
                // �Ӵ󼯺���ɾ���ҽڵ����ڼ���
                bigSet.erase(bigSet.begin() + rSet);
            }

            // ������ڵ�ļ�������֮�����֮ǰû��continue����ô�����߾ͱ�ѡ�м�������С��������
            edgeSet.insert(curEdge);
            cout << nodes[lIndex].val << " --- " << nodes[rIndex].val << endl;
        }
    }

    /*
     * Dijkstra �㷨
     */
    void dijkstra(int nIndex) {
        int flag[curSize];
        int dist[curSize];
        int prev[curSize];
        memset(flag, 0, curSize * sizeof(int));
        memset(prev, 0, curSize * sizeof(int));

        // ��ʼ��dist����
        for (int i = 0; i < curSize; i++) {
            if (Matrix[nIndex * capacity + i]) {
                dist[i] = Matrix[nIndex * capacity + i];
            } else {
                dist[i] = INTMAX;
            }
        }

        flag[nIndex] = 1;
        dist[nIndex] = 0;

        int k = -1;// ������¼ÿһ�δ�dist���ҳ������·���ı��
        for (int _ = 0; _ < curSize; _++) {
            int min = INTMAX;
            for (int i = 0; i < curSize; i++) {
                if (!flag[i] && dist[i] < min) {
                    min = dist[i];
                    k = i;
                }
            }
            // ����֮��k���Ƕ̵�����·�����±꣬����ڵ��Ѿ�ȷ����
            flag[k] = 1;

            // ��ʼ��������ڵ���¾����б�
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
     * Floyd ���·���㷨
     */
    void floyd() {
        int A[curSize * curSize];
        int Path[curSize * curSize];

        // ��ʼ��A���󣬲������ľ������ó�Ϊ�����
        // Path�����ʼ��Ϊ�Լ�
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


        // ��ʼ��������
        for (int k = 0; k < curSize; k++) {
            // k����ѡ����м��
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
    // ��ӽڵ�
    g.addNode('a');
    g.addNode('b');
    g.addNode('c');
    g.addNode('d');
    g.addNode('e');
    g.addNode('f');

    // ��ӱ�
    g.setMatrixForUndirectedMap(0, 1, 20);
    g.setMatrixForUndirectedMap(1, 2, 10);
    g.setMatrixForUndirectedMap(2, 3, 5);
    g.setMatrixForUndirectedMap(0, 5, 3);
    g.setMatrixForUndirectedMap(1, 4, 2);
    g.setMatrixForUndirectedMap(4, 2, 5);


    g.printMatrix();
    cout << "�����������: " << endl;
    g.depthTraverse(0);
    cout << endl;
    cout << "�����������: " << endl;
    g.broadTraverse(0);
    cout << endl;
    cout << "kruskal��С������: " << endl;
    g.kruskal();
    cout << endl;
    cout << "prim��С������: " << endl;
    g.prim(0);
    cout << endl;
    cout << "dijkstra���·��: " << endl;
    g.dijkstra(1);
    cout << endl;
    cout << endl;
    cout << "floyd���·��: " << endl;
    g.floyd();

    return 0;
}