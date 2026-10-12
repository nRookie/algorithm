class Solution {
    fun countPrimes(n: Int): Int {
        if (n <= 2) return 0

        val st = BooleanArray(n)
        val primes = mutableListOf<Int>()

        for (i in 2 until n) {
            if (!st[i]) primes.add(i)

            for (p in primes) {
                // Check before multiplying to avoid Int overflow.
                if (p > (n - 1) / i) break
                st[p * i] = true
                // Mark first, then stop at i's smallest prime factor.
                if (i % p == 0) break
            }
        }
        return primes.size
    }
}
