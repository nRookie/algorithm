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

fun run(str : String, n: Int) : Int {
  // use dp
  // dp[i] is the longestRainyStreak we can have from day 0 to day i if i is the rainy day, otherwise dp[i] is 0
  // dp[0] = if(str[0] == 'S') 0 else 1
  // from 0.. n -1 we have invariant that
  // if (str[i] =='R') dp[i] = dp[i - 1] + 1
  // else dp[i] = 0
  // when the iteration finished, we need to loop through the dp find the longest rainy streak
  // 
  val dp = IntArray(n)
  var res = 0
  for (i in 0 until n) {
    if(str[i] == 'R') { 
      dp[i] = if(i> 0) dp[i - 1] + 1 else 1
      res = maxOf(dp[i], res)
    }
    else dp[i] = 0
  }
  return res
  
}

fun main() {
    val fs = FastScanner()
    val out = System.out.bufferedWriter()

    // read N, then N integers, 
    val n = fs.nextInt()  // 10
    val s = fs.next()     // "SSSSSSSSSS"
    
    val res = run(s, n)
  

    out.write("$res\n")
    out.flush()
}



