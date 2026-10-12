import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.StringTokenizer

private class FastScanner {
    private val reader = BufferedReader(InputStreamReader(System.`in`))
    private var tokens = StringTokenizer("")

    fun next(): String {
        while (!tokens.hasMoreTokens()) {
            val line = reader.readLine()
                ?: throw NoSuchElementException("No more input")
            tokens = StringTokenizer(line)
        }
        return tokens.nextToken()
    }

    fun nextInt(): Int = next().toInt()
    fun nextLong(): Long = next().toLong()
    fun nextDouble(): Double = next().toDouble()
}

fun oddSum(nums : IntArray) : Int {
  var sum = 0
  for (i in nums.indices) {
    if ((i and 1) == 0) {
      sum += nums[i]
    }
  }
  return sum
}

fun main() {
    val fs = FastScanner()
    val out = System.out.bufferedWriter()

    // read N, then N integers, 
    val n = fs.nextInt()
    val nums = IntArray(n) { fs.nextInt() }
    
    val sum = oddSum(nums)
  

    out.write("$sum\n")
    out.flush()
}


