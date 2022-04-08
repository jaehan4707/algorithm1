/*
최적이진트리 문제는 최소의 탐색비용으로 트리를 구성하려는 것이 목표다.
이진트리는 부모의 왼쪽이 부모보다 작거나같아야 부모의 오른쪽이 부모보다 크거나같아야한다.
탐색비용은 각 트리의 높이 * 탐색비용(확률)이다. 보통의 탐색 비용은 높이가 낮을때가 유리하다.
k1,k2,k3, *** kn이 key라고 하고 각 key에 확률을 p1,p2,p3,***pn이라고 하자.
그러면 average search time은 ci*pi i가 1에서 n까지 일것이다.
D[i][j]의 최적값은 최적값인 root를 찾고 최적인 root를 중심으로 left,right를 나눠서 계산.
여기서 k란? 최적인 root 값을 말한다. k를 i부터 j까지의 값을 반복문으로 돌려서 그 k를 기준으로 left,right 쪼개서 left트리의 탐색비용과 right트리의 탐색비용을 계산한다.
그 탐색 비용이 최소가 되는 k값이 최적의 root이다.
k를 기준으로 쪼개진 left,right트리의 부모노드가 k가 되기때문에 각각의 pi값을 한번씩 더 더해준다. 높이가 한칸씩 증가했기떄문이다.
*/

#include <iostream>
#include <vector>
#define INF 9999
using namespace std;
void printary(int n, vector<int>& a);
typedef struct node* node_ptr;
struct node
{
    int key;
    node_ptr left;
    node_ptr right;
};
int main()
{
    int n, root;
    cin >> n;
    vector<int> key(n + 1);
    vector<int> pro(n + 1);
    vector<vector<int>> D(n + 1, vector<int>(n + 1, -1));
    vector<vector<int>> P(n + 1, vector<int>(n + 1, -1));
    node N;
    for (int i = 1; i <= n; i++)
    {
        cin >> key[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> pro[i];
    }
    for (int i = 1; i <= n; i++)
    {
        D[i][i] = pro[i];
    }
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= n - i; j++)
        {
            int k = j + i;
            if (D[j][k] != -1)
            {
                D[j][k] = mini(j, k, root, D, pro);
                P[j][k] = root;
            }
            else
            {
                continue;
            }
        }
    }
    return 0;
}
void printary(int n, vector<int>& a)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (j < n)
                cout << a[i][j] << " ";
            else
                cout << a[i][j];
        }
        if (i < n)
            cout << endl;
    }
}
int mini(int i, int j, int& a, vector<vector<int>>& D, vector<int>& p)
{
    int minvalue = INF, value, sum = 0; // i<=k<=j
    for (int k = i; k <= j; k++)
    {
        value = D[i][k - 1] + D[k + 1][j];
        if (minvalue > value)
        {
            minvalue = value;
            a = k; //최적인 루트 k값을 저장.
        }
        sum = sum + p[k];
    }
    return minvalue + p[j];
}