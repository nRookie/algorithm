#include<iostream>
#include<queue>

using namespace std;


typedef long long ll;
// f(x) = 0
// Q queries
// 1 a b 
// g(x) = f(x) + |x - a| + b , f(x) = g(x);
// query 2,  print x that minimizes f(x), and the minimum value of f(x). if there are  multiple such values of x, choose the minimum such value.
// 
int main() {
    priority_queue<int, vector<int>, less<int> > maxHeap;
    priority_queue<int, vector<int>, greater<int> > minHeap;

    ll sup = 0, sdown = 0, ans = 0;

    int q;
    cin >> q;

    while(q --) {
        int op, a, b;
        cin >> op;

        if (op == 1) {
            cin >> a >> b ;
            ans += b;

            if (maxHeap.empty() || a <= maxHeap.top()) {
                maxHeap.push(a);
                sdown += a;
            } else {
                minHeap.push(a);
                sup += a;
            }

            if (maxHeap.size() > minHeap.size() + 1) {
                int x = maxHeap.top();
                maxHeap.pop();
                sdown -= x, sup +=x;
                minHeap.push(x);
            }

            if (maxHeap.size() < minHeap.size()) {
                int x = minHeap.top();
                minHeap.pop();
                sdown += x, sup -=x;
                maxHeap.push(x);
            }
        } else {
            int mid = maxHeap.top();
            ll res = ans;
            res += (ll) mid * maxHeap.size() - sdown;
            res += sup - (ll) mid * minHeap.size();

            printf("%d %lld\n", mid, res);
        }
    }

}



/*
解释 res 的计算方法
在每次查询操作时，我们需要计算 
�
(
�
)
f(x) 的最小值。这里的关键是理解 
�
(
�
)
f(x) 是如何随着每次更新操作变化的。每次更新操作后，
�
(
�
)
f(x) 会增加一个绝对值项 
∣
�
−
�
∣
+
�
∣x−a∣+b。因此，
�
(
�
)
f(x) 实际上是所有 
∣
�
−
�
∣
+
�
∣x−a∣+b 项的和。

当我们选择 
�
=
�
�
�
x=mid 时（
�
�
�
mid 是中位数），
�
(
�
)
f(x) 的值是最小的，因为：

对于小于 
�
�
�
mid 的所有 
�
a，
�
(
�
)
f(x) 随 
�
x 增加而减少。
对于大于 
�
�
�
mid 的所有 
�
a，
�
(
�
)
f(x) 随 
�
x 减少而减少。
因此，
�
�
�
mid 是平衡左右两边 
∣
�
−
�
∣
∣x−a∣ 项的最佳选择，使得 
�
(
�
)
f(x) 达到最小。

接下来，我们来看 res 的计算：

sdown 是最大堆（小于等于 
�
�
�
mid 的 
�
a 值）的和。
sup 是最小堆（大于 
�
�
�
mid 的 
�
a 值）的和。
因此：

(ll) mid * maxHeap.size() - sdown 计算的是，对于所有小于等于 
�
�
�
mid 的 
�
a，
�
�
�
mid 与这些 
�
a 的差的和（即 
�
�
�
×
mid× 左侧 
�
a 的数量 
−
− 左侧 
�
a 的总和）。
sup - (ll) mid * minHeap.size() 计算的是，对于所有大于 
�
�
�
mid 的 
�
a，这些 
�
a 与 
�
�
�
mid 的差的和（即 右侧 
�
a 的总和 
−
�
�
�
×
−mid× 右侧 
�
a 的数量）。
将这两部分相加，就得到了所有 
∣
�
−
�
∣
∣x−a∣ 项的和，即 
�
(
�
)
f(x) 在 
�
=
�
�
�
x=mid 时除了所有 
�
b 项之和之外的部分。由于每次更新操作的 
�
b 项直接累加到了 ans 中，所以最终的 res 包括了所有 
�
b 项之和（ans）和所有 
∣
�
−
�
∣
∣x−a∣ 项的和。

这样，res 就是在 
�
=
�
�
�
x=mid 时 
�
(
�
)
f(x) 的最小值。
*/