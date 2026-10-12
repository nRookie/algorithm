# Kotlin input/output with built-in Scanner

Use [Main.kt](Main.kt) as a simple starting point for console judges such as
AcWing and AtCoder. It currently reads AcWing 104's input; implement the
algorithm and print the answer before submitting. Choose a Kotlin/JVM language
option supported by the judge.

## Methods to memorize

```kotlin
import java.util.Scanner

fun main() {
    val input = Scanner(System.`in`)

    val number: Int = input.nextInt()
    val bigNumber: Long = input.nextLong()
    val decimal: Double = input.nextDouble()
    val word: String = input.next()

    println(number)          // Print a value and a newline.
    print("$word ")         // Print without a newline.
}
```

Each read consumes the next whitespace-delimited token. Spaces, tabs, and
newlines are skipped automatically. No custom scanner, splitting, or Regex
is needed. The four reads above accept, for example:

```text
42 10000000000
3.14 hello
```

`nextDouble()` follows the scanner's locale. If a judge uses a decimal point
and you want to make that explicit, add `import java.util.Locale` and call
`input.useLocale(Locale.US)` after creating the scanner.

## Read collections

```kotlin
val n = input.nextInt()
val numbers = MutableList(n) { input.nextInt() }
```

For other types, replace the read inside the initializer:

```kotlin
val longs = MutableList(n) { input.nextLong() }
val doubles = MutableList(n) { input.nextDouble() }
val words = MutableList(n) { input.next() }
```

These are alternatives. Running all four would consume four groups of n
values. Read only what the problem's input format specifies.

## Read a whole line

```kotlin
val line = input.nextLine()
```

`next()` reads one word; `nextLine()` reads the rest of the current line,
including spaces. Token reads leave the following line separator pending.
If an integer occupies its own line and the next line is a sentence:

```kotlin
val n = input.nextInt()
input.nextLine()              // Consume the remainder of the integer's line.
val sentence = input.nextLine()
```

Only discard that remainder when the input format says nothing needed remains
on that line. Otherwise you would skip real input.

## Output

```kotlin
println(answer)
println(if (possible) "Yes" else "No")
println(numbers.joinToString(" "))
```

These are separate examples using variables defined in your solution. Match
the problem's capitalization and spacing. Do not print input prompts or debug
messages to standard output when submitting.

## Practice with AcWing 104

```text
4
6 2 9 1
```

The starter reads `n = 4` and `positions = [6, 2, 9, 1]`. It intentionally
prints nothing until you implement the solution. The completed solution's
expected output for this input is `12`.

From this folder, compile and run:

```sh
kotlinc Main.kt -include-runtime -d /tmp/kotlin-scanner-io.jar
java -jar /tmp/kotlin-scanner-io.jar < sample.in
```

To practice, type the import, scanner construction, n read, collection read,
and `println` from memory. Keep the same input setup across problems and
adapt the reads to each statement.

Scanner is convenient but can be slow for large input under tight limits.
The separate [buffered input template](../console-io/README.md) remains
available if needed. LeetCode function-only submissions do not need console I/O.
