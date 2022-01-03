/*
$Description$
有一张$n$个点的图。M每次询问$(u,v)$，你需要回答图中$(u,v)$间是否有边。如果M可以用$<n(n-1)/2$次询问确定图中所有点是否连通，M赢；否则你赢。你可以根据M之前的询问任意改变图的连边情况。实现函数$hasEdge(u,v)$回答每次询问，使得你赢。
$n\leq 1500$。
$Solution$
挺有意思的。
既不能早告诉当前点间右边(右边就不用问当前点了，问一个连通块的就行了)，也不能一直说没边。不到最后一刻不告诉她就行了。
如果对点$i$的询问次数不足$n-i$或$i$次（看每条边统计编号小的还是大的），就不连边。
*/
#include "game.h"
#include <algorithm>

int cnt[1505];

void initialize(int n) {}

int hasEdge(int u,int v){
    return ++cnt[std::max(u,v)]==std::max(u,v);
}
