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
}


int UF::count()
{
    return mCount;
}


int UF::find(int p)
{
    return id[p];
}

void UF::myunion(int p, int q)
{
    //将p和q归并到相同的分量当中

    int pID = find(p);
    int qID = find(q);

    //如果 p 和 q 已经在相同的分量之重，则不需要采取任何行动

    if (pID == qID) return;

    //将 p的分量重命名为q的名称

    for (int i = 0; i < id.size(); i++)
    {
        if (id[i] == pID) id[i] = qID;
    }

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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
