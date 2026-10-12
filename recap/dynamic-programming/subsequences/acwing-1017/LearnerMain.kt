import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)
    val K = input.nextInt()

    repeat(K) {
        val n = input.nextInt()
        val h = IntArray(n) { input.nextInt() }
        // f[i]: longest decreasing subsequence length ending at i, moving backward.
        // g[i]: longest decreasing subsequence length ending at i, moving forward.
        val f = IntArray(n) { 1 }
        val g = IntArray(n) { 1 }

        // Move j -> i from right to left: j > i and h[j] > h[i].
        for (i in n - 1 downTo 0) {
            for (j in n - 1 downTo i + 1) {
                if (h[j] > h[i]) f[i] = maxOf(f[i], f[j] + 1)
            }
        }

        for (i in 0 until n) {
            for (j in 0 until i) {
                if (h[j] > h[i]) {
                    g[i] = maxOf(g[i], g[j] + 1)
                }
            }
        }

        var answer = 0
        for (i in 0 until n) {
            answer = maxOf(answer, f[i], g[i])
        }
        println(answer)
    }
}
