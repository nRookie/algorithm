import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)

    val n = input.nextInt()
    val h = IntArray(n) { input.nextInt() }

    val f = IntArray(n) { 1 } // Longest strictly increasing subsequence length ending at i.
    val g = IntArray(n) { 1 } // Longest strictly decreasing subsequence length starting at i.

    for (i in 0 until n) {
        for (j in 0 until i) {
            if (h[i] > h[j]) {
                f[i] = maxOf(f[i], f[j] + 1)
            }
        }
    }
    for (i in n - 1 downTo 0) {
        for (j in n - 1 downTo i + 1) {
            if (h[i] > h[j]) {
                g[i] = maxOf(g[i], g[j] + 1)
            }
        }
    }
    var answer = 0
    for (i in 0 until n) {
        answer = maxOf(answer, f[i] + g[i] - 1)
    }
    println(answer)
}
