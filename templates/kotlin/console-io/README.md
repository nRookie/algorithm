# Kotlin console input/output template

Use [Main.kt](Main.kt) for standard-input/standard-output problems on AtCoder
and similar judges. It is a complete runnable example: read n integers and
print their sum. Replace that example section for each problem. LeetCode
function-only problems supply their own harness and do not need this template.

## The part to memorize

```kotlin
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
}

fun main() {
    val input = FastScanner()
    val out = System.out.bufferedWriter()

    // Read input, solve the problem, write the answer here.

    out.flush()
}
```

Remember the sequence: **reader → tokens → refill while empty → take one token**.
Then: **read → solve → write → flush**. `nextDouble()` is optional.

## Why each part exists

- ``System.`in` `` is standard input. Kotlin's `in` is a keyword, so the Java
  field name needs backticks.
- `bufferedReader()` reads text efficiently without loading all input at once.
- `StringTokenizer` splits a line into whitespace-separated tokens. Repeated
  spaces and tabs do not produce empty tokens.
- The initial tokenizer is empty, so the first `next()` reads the first line.
- The `while` loop refills whenever no tokens remain. It also skips empty or
  whitespace-only lines; a single `if` would not handle those reliably.
- `readLine()` returns null at end of input. Throwing there makes an unexpected
  missing value clear rather than looping forever. Read the number of values
  specified by the problem, not more.
- `nextToken()` consumes one token. The conversion helpers reuse that logic.
- `out.write(...)` writes text. `\n` separates output lines, and `flush()` sends
  any buffered output before the program ends.

## Common input shapes

These snippets go inside main; use only the input shape in the statement.

```kotlin
val n = input.nextInt()
val k = input.nextLong()
val word = input.next()                // One whitespace-delimited string
val values = MutableList(n) { input.nextInt() }
```

For a grid with no spaces inside each row:

```kotlin
val h = input.nextInt()
val w = input.nextInt()
val grid = List(h) { input.next() }
// grid[row][col] is a Char; each row is expected to have w characters.
```

For n − 1 edges with node labels 1 through n:

```kotlin
val n = input.nextInt()
val graph = MutableList(n + 1) { mutableListOf<Int>() }
repeat(n - 1) {
    val a = input.nextInt()
    val b = input.nextInt()
    graph[a].add(b)
    graph[b].add(a)
}
```

For multiple test cases, read a test count only if the statement supplies one:

```kotlin
val t = input.nextInt()
repeat(t) {
    val n = input.nextInt()
    // Read and solve this case; reset case-specific state here.
}
```

## Common output shapes

```kotlin
out.write("$answer\n")
out.write(if (possible) "Yes\n" else "No\n")
out.write(values.joinToString(" "))
out.newLine()
```

These are independent examples; define answer, possible, or values in your
problem logic. Match the judge's exact capitalization and separators. Do not
print prompts such as “Enter n” or debugging logs to standard output.

## Token boundaries versus line boundaries

For token input, these inputs are equivalent:

```text
4
10 -2 7 5
```

```text
4 10

-2     7
5
```

Calls return `4`, `10`, `-2`, `7`, `5` in both cases. After consuming `4`, the
next read uses any remaining token on that line before loading another line.
For this example, the output is `20`.

This scanner is for whitespace-delimited input. It does not preserve spaces
inside a full text line or meaningful empty lines. For a line-based problem,
use a single BufferedReader directly and read according to that statement;
do not mix this scanner with another reader on standard input.

This is a readable general-purpose template, not a guarantee against every
time limit. Very large input with tight limits may need a byte-based scanner.
For interactive problems, flush after each query rather than only at the end.
Numeric conversion does not prevent arithmetic overflow: use Long operands
before multiplication when the problem's bounds require it.

## Practice by typing

1. Type the scanner and main function from memory, then run the sum example.
2. Reformat the same input across lines, spaces, tabs, and blank lines. The
   result should remain 20.
3. Replace the sum logic with reading a list and printing it space-separated.
4. Reuse it in the next problem, changing only the read/solve/write section.

Focus on explaining the refill loop while typing it; that is the only stateful
part of the input handler. You do not need to memorize every example above.

## Run locally

From this folder:

```sh
kotlinc Main.kt -include-runtime -d /tmp/kotlin-console-io.jar
java -jar /tmp/kotlin-console-io.jar < sample.in
```

Expected output: `20`. To submit, copy Main.kt with your actual solution logic.
