

#include <iostream>
#include<vector>
using namespace std;
class weightedQuickUnionUF
{

private:
    vector<int> id;
    vector<int> sz;
    int mCount;
public:
    weightedQuickUnionUF(int N);
    void myunion(int p, int q);
    int find(int p);
    bool connected(int p, int q);
    int count();
};




weightedQuickUnionUF::weightedQuickUnionUF(int n)
{
    this->mCount = n;
    id.resize(n);
    for (int i = 0; i < n; i++) id[i] = i;
    sz.resize(n);

    for (int i = 0; i < n; i++) sz[i] = 1;
}


int weightedQuickUnionUF::count()
{
    return mCount;
}



// quick Union

int weightedQuickUnionUF::find(int p)
{
    //���������ҵ����ڵ�
    while (p != id[p]) p = id[p];
    return p;
}

void weightedQuickUnionUF::myunion(int p, int q)
{

    //��p��q�ĸ��ڵ�ͳһ
    int pRoot = find(p);
    int qRoot = find(q);
    if (pRoot == qRoot) return;

    //��С���ĸ��ڵ����ӵ������ĸ��ڵ�
    if (sz[qRoot] < sz[pRoot])
    {
        id[qRoot] = pRoot; sz[qRoot] += sz[pRoot];
    }
    else {
        id[pRoot] = qRoot; sz[pRoot] += sz[qRoot];
    }

    mCount--;
}


bool weightedQuickUnionUF::connected(int p, int q)
{
    return find(p) == find(q);
}

