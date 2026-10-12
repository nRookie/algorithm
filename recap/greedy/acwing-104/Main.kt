import java.util.Scanner
import kotlin.math.abs

fun main() {
    val input = Scanner(System.`in`)

    val n = input.nextInt()
    val positions = MutableList(n) { input.nextInt() }

    positions.sort()

    val median = positions[n / 2] // Upper median when n is even.
    var distance = 0
    for (position in positions) {
        distance += abs(position - median)
    }

    println(distance)
}
