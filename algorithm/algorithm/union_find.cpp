// algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
using namespace std;
class UF
{

private:
    vector<int> id;
    int mCount;
public:
    UF(int N);
    void myunion(int p, int q);
    int find(int p);
    bool connected(int p, int q);
    int count();
};





UF::UF(int n)
{
    this->mCount = n;
    id.resize(n);
    for (int i = 0; i < n; i++) id[i] = i;
}


int UF::count()
{
    return mCount;
}

//quick find
//int UF::find(int p)
//{
//    return id[p];
//}
//
//void UF::myunion(int p, int q)
//{
//    //将p和q归并到相同的分量当中
//
//    int pID = find(p);
//    int qID = find(q);
//
//    //如果 p 和 q 已经在相同的分量之重，则不需要采取任何行动
//
//    if (pID == qID) return;
//
//    //将 p的分量重命名为q的名称
//
//    for (int i = 0; i < id.size(); i++)
//    {
//        if (id[i] == pID) id[i] = qID;
//    }
//
//    mCount--;
//}



// quick Union

int UF::find(int p)
{
    while (p != id[p]) p = id[p];
    return p;
}

void UF::myunion(int p, int q)
{
    //将p和q的根节点统一
    int pRoot = find(p);
    int qRoot = find(q);
    if (pRoot == qRoot) return;
    id[pRoot] = qRoot;

    mCount--;
}


bool UF::connected(int p, int q)
{
    return find(p) == find(q);
}



int main()
{
    int n;
    std::cin >> n;
    int p, q;
    UF uf(n);
    while (std::cin >> p >> q)
    {
        if (uf.connected(p, q)) continue;
        uf.myunion(p, q);
        std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << "component" << std::endl;

}
