import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)
    val k = input.nextInt()
    repeat(k) {
        val n = input.nextInt()
        val h = MutableList(n) { input.nextInt() }
        println(longestGlide(h))
    }
}
