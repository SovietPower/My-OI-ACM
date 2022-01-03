#include <bits/stdc++.h>
#define lowbit(x) x & (-x)

using namespace std;

const int Maxn = 100000 + 100;

int N, M;
int Cnt[Maxn];
int up[Maxn], down[Maxn];
int Sum[Maxn * 2];
int l[Maxn], r[Maxn];
int a[Maxn], b[Maxn];
int Val[Maxn];

vector <int> vec[Maxn];

inline void add (int x, int v)
{
    while (x <= N)
    {
        Sum[x] += v;
        x += lowbit(x);
    }
}

inline int Query (int x)
{
    int Ans = 0;
    while (x)
    {
        Ans += Sum[x];
        x -= lowbit(x);
    }
    return Ans;
}

inline void Update(int x, int y)
{
    if (Val[x] == y) return ;
    if (y == 1) add(x, 1);
    else add(x, -1);
    Val[x] = y;
}


inline int Check (int t)
{
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(Sum, 0, sizeof(Sum));
    memset(Val, 0, sizeof(Val));
    for (int i = 1; i <= N; ++i) up[i] = 0, down[i] = Cnt[i];
    for (int i = 1; i <= N; ++i)
        if (vec[i].size() >= 2 * t)
            l[i] = vec[i][t - 1] + 1, r[i] = vec[i][vec[i].size() - t] - 1;
        else l[i] = N + 1, r[i] = 0;
    int sum = 0;
    for (int i = 1; i <= N; ++i)
    {
        vector <int> Vis;
        for (int j = 0; j < vec[i - 1].size(); ++j)
        {
            int y = vec[i - 1][j];
            Vis.push_back(y);
            up[y] ++;
            if (up[y] >= t) a[y] = 1; else a[y] = 0;
        }

        for (int j = 0; j < vec[i].size(); ++j)
        {
            int y = vec[i][j];
            Vis.push_back(y);
            down[y] --;
            if (down[y] >= t) b[y] = 1; else b[y] = 0;
        }

        for (int j = 0; j < Vis.size(); ++j)
        {
            int y = Vis[j];
            Update(y, a[y] + b[y] == 2);
        }

        if (l[i] <= r[i])
            sum += Query(r[i]) - Query(l[i] - 1);
    }
    return sum;
}

int main()
{
    scanf("%d", &M);
    N = M + 1;
    for (int i = 1; i <= M; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        ++x, ++y;
        vec[x].push_back(y);
        Cnt[y] ++;
    }

    for (int i = 1; i <= N; ++i) sort(vec[i].begin(), vec[i].end());

    int l = 0, r = M, Ans = -1;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (Check(mid)) l = mid + 1, Ans = mid;
        else r = mid - 1;
    }

    cout<<Ans<<endl<<Check(Ans)<<endl;
    return 0;
}