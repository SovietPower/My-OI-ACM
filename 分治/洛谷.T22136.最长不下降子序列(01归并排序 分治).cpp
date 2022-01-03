/*
$Description$
给定一个长为n的序列，每次可以反转 $[l,r]$ 区间，代价为 $r-l+1$。要求在$4*10^6$代价内使其LIS长度最长，并输出需要操作的数量及每个反转操作。
$n\leq32000$。
$Solution$
显然，需要在4e6的代价内将$1\sim n$尽可能排好序。(而且不一定要反转一大段区间，可以交换相邻元素实现一个元素的移动)
**Subtask2** $n\leq1000$
可以用冒泡排序将每个元素放到应放的位置上，每次交换相邻元素，代价$O(1)$，总复杂度$O(\frac{n(n-1)}{2})$，代价与复杂度相同 
可以看出，程序排序所消耗时间可近似看做代价 
**Subtask3** 值域$[0,5]$
考虑值域仅为$[0,1]$时应怎么做，序列是由几堆$00,11$构成的，用01归并排序 每次将一堆$0$与左边的一堆$1$互换位置 
最后形成$00001111$这样的序列，这样可以把$0,1$区分出来。01归并排序自带$1/2$常数 
每次区分两个不同数，一共需要$5$次，复杂度/代价为 $O(2.5nlogn)$ 
**Total**
参考上一个做法，对所有数字进行分治，选择一个值$mid$，将$\geq mid$的数设为$0$，$<mid$的数设为$1$，每次01归并排序可以区分两堆数。
分治在$O(\log n)$层一定会结束。可以按照二进制从高位到低位进行分治。
复杂度/代价为 $O(0.5nlog^2n)$，满打满算 $3.6*10^6$ 
-----
**[Update]**
另外有一种贪心，就是每次交换相邻的两段$01$，比如：`10101010->01010101->00101011...`。直接这样复杂度是$n^2$的。
考虑仍是每次交换相邻的两段$01$，但间隔一段$01$：`10101010->01100110->00011110->00001111`。可以发现开头$0$的个数呈几何增长（~~我没发现~~），所以复杂度$O(n\log n)$。但是应该比上面那个难写...但是这个思想应该（可能）很常用。
*/
#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define gc() getchar()
#define pr std::pair<int,int>
#define mp std::make_pair
const int N=32010;

int n,A[N];
bool B[N];
std::vector<pr> ans;

inline int read()
{
	int now=0;register char c=gc();
	for(;!isdigit(c);c=gc());
	for(;isdigit(c);now=now*10+c-'0',c=gc());
	return now;
}
void Rev(int l,int r)
{
	std::reverse(A+l,A+r+1), std::reverse(B+l,B+r+1);
	ans.push_back(mp(l,r));
}
void Solve_01(int l,int r)//将当前[l,r]的01归并排序 
{
	if(l==r) return;
	int mid=l+r>>1;
	Solve_01(l,mid), Solve_01(mid+1,r);//将左右子区间化为有序(0011)
	int p1=0,p2=0;//现在[l,r]为0011,0011，找到左边最左的1，右边最右的0，将这一区间交换 
	//[l,r] (0)1,0(1)也是有可能的 
	for(int i=l; i<=mid; ++i)
		if(B[i]) {p1=i; break;}
	for(int i=r; i>mid; --i)
		if(!B[i]) {p2=i; break;}
	if(p1 && p2) Rev(p1,p2);
}
void Solve_Num(int l,int r,int d)//将当前[l,r]的数按照第d位分为0/1，记录在B中 
{
	if(l>r||d==-1) return;
	for(int i=l; i<=r; ++i) B[i]=(A[i]>>d)&1;//按照第d位是否为1分01 
	Solve_01(l,r);//以当前01归并 
	int p=r;//p为第一个1的位置(如果有) 
	//01归并后的序列有三种情况：1.0000；2.1111；3.000111
	//对于1.2显然继续[l,r],d-1的分治排序即可，对于3，只需对0,1的区间分别进行归并即可 
	for(int i=l; i<=r; ++i)
		if(B[i]) {p=i-1; break;}
	Solve_Num(l,p,d-1), Solve_Num(p+1,r,d-1);
}

int main()
{
	n=read();
	for(int i=1; i<=n; ++i) A[i]=read();
	Solve_Num(1,n,14);
	printf("%d\n",ans.size());
	for(int i=0; i<ans.size(); ++i) printf("%d %d\n",ans[i].first,ans[i].second);

	return 0;
}
