# Supplied linear-sieve memo

Source: learner's pasted memo, recapped on 2026-10-11. The original problem
number was not supplied. The snippet counts primes up to and including `n`.
The original Chinese text and code are retained here for provenance; the
English review and corrections are in [EXPLANATION.md](EXPLANATION.md).

```c
if (i % primes[j] == 0) break; // 成立的时候 primes[j] 一定是i的最小质因子
```

### 算法

我们是从小到大枚举的质数
n只会被最小质因子筛掉

1. i % pj == 0
pj 一定是i的最小质因子， pj一定是pj\*i 的最小质因子

2. i % pj != 0
pj 一定小于i的所有质因子， pj 也一定是pj \*i 的最小质因子

对于一个合数x， 假设pj 是x的最小质因子，当i枚举到 x/pj 的时候,
合数就被筛掉，这个数是最小质因子，每个数只会被筛一次，
因此他是线性的。

```text
x = 4
primes[j] = 2
x / primes[j] = 2
4 / 2 = 2
i %primes[j]== 0
st[primes[j] = true
```

## 实现

```cpp
void get_primes(int n) {
    for (int i = 2; i <= n; i ++) {
        if (!st[i]) primes[cnt ++] = i;
        for (int j = 0; primes[j] <= n / i; j ++ ) {
        // primes[j] <= n / i 等同于 【primes[j] * i】 <= n，而【primes[j] * i】就是所有要筛除的合数。
            st[primes[j] * i ] = true;
            if (i % primes[j] == 0) break; // primes[j] 一定是i 的最小质因子
        }
    }
}

int main() {
    int n;
    cin >> n;
    get_primes(n);

    cout << cnt << endl;
}
```

## 时间复杂度

Original image reference (image content unavailable):
`evernotecid://251D1A67-CA41-416B-BF84-A58D319CBC7B/appyinxiangcom/25393691/ENResource/p1924`

The supplied snippet omits headers, namespace, global storage declarations,
and initialization. It is preserved as a reference, not a standalone program.


## Learner's Kotlin attempts from the follow-up discussion

Preserved as supplied. The first has an integer-division boundary bug; the
second is correct but allocates and may mark one unnecessary endpoint.
See the explanation for the corrected final version.

### First attempt

```kotlin
class Solution {
    fun countPrimes(n: Int): Int {
        val st = BooleanArray(n)
        val primes = mutableListOf<Int>()
        for (i in 2 until n) {
            if (!st[i]) primes.add(i)

            for (p in primes) {
                if (p >= n /i ) break
                st[p * i] = true
                if (i % p == 0) break
            }
        }

        return primes.size
    }
}
```

### Second attempt

```kotlin
class Solution {
    fun countPrimes(n: Int): Int {
        val st = BooleanArray(n + 1)
        val primes = mutableListOf<Int>()
        for (i in 2 until n) {
            if (st[i] == false) primes.add(i)

            for (p in primes) {
                if (p > n /i ) break
                st[p * i] = true
                if (i % p == 0) break
            }
        }
        return primes.size
    }
}
```
