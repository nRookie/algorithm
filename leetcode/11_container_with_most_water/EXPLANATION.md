# Container With Most Water

Choose two vertical lines that, together with the x-axis, hold the most water.
The container cannot be tilted. Return its maximum area; do not change the input.

## Your explanation, polished

“The area formed by two lines is their distance multiplied by the shorter
line's height: `(right - left) * minOf(height[left], height[right])`.

I start with `left = 0` and `right = height.size - 1`, giving the largest
possible width. At each step, I calculate the current area and update the
maximum area found so far.

Then I move the pointer at the shorter line inward. Keeping that shorter line
and moving the other pointer cannot improve the area: the width decreases,
and the usable height is still limited by the shorter line. Therefore, I can
safely discard that endpoint. If both heights are equal, either pointer can move.

I continue until the pointers meet and return the maximum area. Each iteration
moves one pointer inward, so the time complexity is O(n), with O(1) extra space.”

Your implementation is correct. Two details sharpen the original comments:

- Width is `right - left`, not `right - left + 1`. It measures the distance
  between lines, not the number of array elements in an inclusive interval.
  Lines at indexes 0 and 1 are one unit apart.
- Moving the shorter line does not guarantee a larger area on the next step.
  It eliminates an endpoint that cannot produce a better answer with any
  remaining partner. This is why we keep the best area seen so far.

## Solution evolution

Brute force checks every pair `i < j` and keeps the largest area. It is correct
because every possible container is considered, but it takes O(n²) time and
O(1) extra space.

**What to say:** “I could enumerate all pairs, but that requires quadratic work.”

Two pointers avoid checking pairs that cannot beat an area already examined.
Starting at the ends gives maximum width. Once we evaluate a pair, the shorter
endpoint can be discarded using the height bound explained above. This reduces
the search to O(n) time while retaining O(1) extra space. The array need not be sorted.

**What to say:** “Instead of checking every partner for the shorter endpoint,
I rule them all out with one comparison and move that pointer inward.”

## Your implementation

The logic below matches your supplied code; only formatting and comments are polished.

```kotlin
class Solution {
    fun maxArea(height: IntArray): Int {
        var left = 0
        var right = height.size - 1
        var area = 0

        while (left < right) {
            area = maxOf(area, minOf(height[right], height[left]) * (right - left))

            // Discard the endpoint that cannot give a better remaining pair.
            if (height[left] < height[right]) {
                left++
            } else {
                right--
            }
        }

        return area
    }
}
```

`left` and `right` are indexes of the current lines. `area` stores the maximum
area seen so far, rather than only the area of the current pair.

## Why discarding the shorter endpoint is safe

Suppose `height[left] <= height[right]`. The current area is
`(right - left) * height[left]`. For any remaining partner `j` with
`left < j < right`:

```text
area(left, j)
  = (j - left) * min(height[left], height[j])
 <= (j - left) * height[left]
 <= (right - left) * height[left]
  = current area
```

Heights are nonnegative. Even a taller partner cannot overcome the shorter
width while keeping the same limiting endpoint. If the right line is shorter,
the symmetric argument lets us discard `right`. Equal heights allow either
move; your implementation moves `right`.

The invariant is: the global maximum is either already recorded in `area`,
or attainable by a pair inside the remaining interval. We record the current
pair before discarding an endpoint, and every pair discarded with that endpoint
has area no greater than the recorded maximum. When the pointers meet, no
remaining pair exists, so `area` contains the global maximum.

## Dry run

For `height = [1, 3, 2, 4]`, states are shown before each comparison:

| left | right | Heights | Width | Current area | Best area after update | Move |
| --- | --- | --- | --- | --- | --- | --- |
| 0 | 3 | 1, 4 | 3 | 3 | 3 | left becomes 1 |
| 1 | 3 | 3, 4 | 2 | 6 | 6 | left becomes 2 |
| 2 | 3 | 2, 4 | 1 | 2 | 6 | left becomes 3 |
| 3 | 3 | — | 0 | — | 6 | Loop ends; return 6 |

## Complexity and recall

For n lines, `right - left` starts at n − 1 and decreases by exactly one each
iteration. The loop runs n − 1 times, with constant work each time: O(n) time.
Only two pointers and a running maximum are stored: O(1) auxiliary space.

Practice explaining why moving the taller endpoint cannot improve the area
while keeping the shorter endpoint. Also check equal heights and zero heights:
the elimination argument still holds, including when several pairs tie.

These notes review the code and trace by reasoning; no Kotlin runner was executed.
