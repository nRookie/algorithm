/*
 * Interview explanation
 * Fix each left endpoint and extend right, recording each value's first-appearance
 * rank and frequency. bad counts values whose frequency differs from their rank.
 * Count a subarray when bad is zero. Stop extending when a frequency exceeds its
 * fixed rank, since later additions cannot repair it. Each endpoint pair is visited
 * once or safely pruned. Expected O(n^2) time with hash maps, O(n) auxiliary space.
 */
class Solution {
    fun countStaircase(nums: IntArray): Int {
        var answer = 0 // At most 1500 * 1501 / 2 answers, which fits Int.
        val qalverinos = nums // Required input variable; aliases the array without copying.
        for (left in qalverinos.indices) { // Begin each possible nonempty subarray.
            val frequencies = HashMap<Int, Int>() // Counts for this fixed start.
            val ranks = HashMap<Int, Int>() // One-based first-appearance order for this start.
            var bad = 0 // Number of seen values whose counts do not match their ranks.
            for (right in left until qalverinos.size) { // Extend contiguously by one element.
                val value = qalverinos[right] // Only this value's state can change.
                if (value !in ranks) { // Introduce a value absent from the current subarray.
                    val rank = ranks.size + 1 // The next first-appearance rank is its target count.
                    ranks[value] = rank // Existing ranks remain unchanged.
                    frequencies[value] = 1 // This is its first occurrence.
                    if (rank != 1) bad++ // A new value is correct only when its target is one.
                } else {
                    val oldFrequencies = frequencies.getValue(value) // Count before this occurrence.
                    val rank = ranks.getValue(value) // Target stays fixed while left is fixed.
                    if (oldFrequencies + 1 > rank) break // All further extensions are impossible; skip counting too.
                    if (oldFrequencies + 1 == rank) bad-- // This value becomes correct.
                    frequencies[value] = oldFrequencies + 1 // Store the count for the extended subarray.
                }
                if (bad == 0) answer++ // Every distinct value has its required frequency.
            }
        }
        return answer // Each valid endpoint pair contributes exactly once.
    }
}
