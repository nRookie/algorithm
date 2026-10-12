private fun isPrime(x: Int): Boolean {
    if (x < 2) return false
    var d = 2
    while (d <= x / d) {
        if (x % d == 0) return false
        d++
    }
    return true
}

fun main() {
    val solution = Solution()
    var expected = 0
    for (n in 0..2000) {
        if (isPrime(n - 1)) expected++
        check(solution.countPrimes(n) == expected) { "Mismatch at n=$n" }
    }
    check(solution.countPrimes(5_000_000) == 348_513)
    check(solution.countPrimes(3) == 1) // Repeated calls keep no stale state.
    println("Passed: all n=0..2000 against trial division, maximum bound, repeated call.")
}
