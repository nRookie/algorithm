import java.util.StringTokenizer

private class FastScanner {
    private val reader = System.`in`.bufferedReader()
    private var tokens = StringTokenizer("")

    fun next(): String {
        while (!tokens.hasMoreTokens()) {
            val line = reader.readLine()
                ?: throw NoSuchElementException("Unexpected end of input")
            tokens = StringTokenizer(line)
        }
        return tokens.nextToken()
    }

    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
    fun nextDouble(): Double = next().toDouble()
}

fun main() {
    val input = FastScanner()
    val out = System.out.bufferedWriter()

    // Example problem: read n integers and print their sum.
    // Replace this section with the judge's actual problem logic.
    val n = input.nextInt()
    var sum = 0L
    repeat(n) {
        sum += input.nextLong()
    }
    out.write("$sum\n")

    out.flush()
}
