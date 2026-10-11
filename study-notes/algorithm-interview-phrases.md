# Algorithm interview phrases

Use these as sentence patterns, not a script to memorize. Clear variable
meanings and reasons matter more than formal vocabulary. Both “iterate through
the array” and “loop through the array” are natural; “traverse the array” is
also correct. Always distinguish an index from the value stored there.

For binary-search reasoning, common explanation mistakes, and the lessons
across our exercises, see [Binary search cheatsheet](binary-search-cheatsheet.md).

## Describe the goal and approach

| Purpose | Natural phrasing |
| --- | --- |
| Restate the goal | “We need to find the largest h such that at least h papers each have at least h citations.” |
| Clarify a constraint | “Are we allowed to modify the input array?” |
| Introduce a baseline | “A straightforward approach is to sort the array first.” |
| Explain the cost | “Sorting dominates the running time, so this takes O(n log n).” |
| Motivate an improvement | “We only need the counts, so we may not need the full sorted order.” |
| State a bound | “Since there are n papers, the answer cannot exceed n.” |

## Describe traversal and variables

| Purpose | Natural phrasing |
| --- | --- |
| Traverse an array | “I’ll iterate through the array from left to right.” |
| Identify the position | “We’re currently at index i.” |
| Identify the value | “The value at index i is citations[i].” |
| Iterate over values | “Here, x is the citation count of the current paper.” |
| Distinguish a prefix | “The first i + 1 elements represent i + 1 papers.” |
| Describe descending order | “I’ll check candidate values from n down to zero, inclusive.” |
| Define a bucket | “count[c] stores the number of papers with exactly c citations.” |
| Define the last bucket | “The last bucket includes all papers with at least n citations.” |
| Initialize storage | “I’ll initialize every bucket to zero.” |
| Increment a count | “I’ll increment the corresponding bucket by one.” |
| Accumulate | “I’ll add this bucket’s count to the running total.” |

If x is a value in `for (x in citations)`, do not call it an index. In an
index-based loop, “the element at index i” is clearer than “the ith element,”
which may leave zero-based versus one-based numbering ambiguous.

## Prepositions for positions, ranges, and updates

Use **in** for membership and **at** for a specific position: “The element
at index i is in the array.” Distinguish index i from the value `nums[i]`.

| Word or phrase | Typical use | Natural example |
| --- | --- | --- |
| in | Membership in a collection or range | “The target is in the array.” |
| at | An exact position | “The value at index mid qualifies.” |
| before | Strictly earlier positions | “Every element before l is smaller than the target.” |
| after | Strictly later positions | “Every element after r is larger than the target.” |
| at or before | Include the named position | “All elements at or before mid are too small.” |
| at or after | Include the named position | “All elements at or after mid qualify.” |
| through | Up to and including an endpoint | “Discard everything through mid.” |
| from … to … | Direction or range | “Scan from left to right.” |
| within | Inside a specified region | “Search within the selected row.” |
| over | Traversal or search domain | “Iterate over the elements.” |
| with | Comparison counterpart | “Compare nums[mid] with the target.” |
| by | Method or amount of change | “Shrink the interval by moving r.” |
| to | Assignment destination | “Set l to mid + 1.” |
| between … and … | Two limits; clarify inclusion | “The answer lies between l and r, inclusive.” |

For numeric ranges, say “from a to b, inclusive” or “from a up to but not
including b” when endpoint membership matters. `[a, b]` includes both;
`[a, b)` excludes b. “Before l” excludes index l; “at or before l” includes
it. These are clearer than “on the left side of l.”

## Describe binary-search boundaries

| Purpose | Natural phrasing |
| --- | --- |
| State the first partition | “Values before the boundary are smaller than the target; values at or after it are greater than or equal to the target.” |
| State the last partition | “Values through the last qualifying index are less than or equal to the target; values after it are greater.” |
| Retain a candidate | “The middle index could be the answer, so I keep it.” |
| Discard a prefix | “Everything through mid is too small, so I set l to mid + 1.” |
| Discard a suffix | “Everything from mid onward is too large, so I set r to mid - 1.” |
| Justify the upper midpoint | “Since I keep mid when moving l, I use an upper midpoint to guarantee progress.” |
| State convergence | “The loop ends when the pointers meet.” |
| Distinguish convergence from success | “The remaining candidate must still be checked for equality.” |

For a sorted array, smaller values come first. Describe the second partition
as “values less than or equal to the target, followed by values greater than
the target.” Avoid reversing those portions.

> “I first find the first value greater than or equal to the target and
> verify that it equals the target. Then I find the last value less than
> or equal to the target. Because the target exists and the array is sorted,
> these are its first and last occurrences.”

Reference: [Find First and Last Position](../leetcode/34_find_first_and_last_position_of_element_in_sorted_array/EXPLANATION.md).

## Explain correctness and control flow

| Purpose | Natural phrasing |
| --- | --- |
| State an invariant | “After this update, papers is the number of papers with at least h citations.” |
| Justify an update | “These groups do not overlap, so we can add their counts.” |
| Check a candidate | “If the running total is at least h, then h is a valid candidate.” |
| Explain maximality | “Because we check candidates in descending order, the first valid one is the maximum.” |
| Describe failure | “The condition no longer holds.” |
| Describe loop completion | “If we reach the end without finding a failing candidate, we return n.” |
| Exit a loop | “I’ll save the answer and break out of the loop.” |
| Exit a function | “I can return h directly from inside the loop.” |
| State termination | “Each iteration decreases h by one, and zero is always a valid candidate.” |
| Analyze space | “The count array has n + 1 entries, so the extra space is O(n).” |
| Distinguish proof and example | “This example illustrates the update; the invariant explains why it works in general.” |

## Polish phrases from our H-Index discussion

| Original wording | Natural version |
| --- | --- |
| “non-increasing older” | “non-increasing order” or “descending order” |
| “current is the index of the paper of we are traversing” | “current is the index of the paper we’re examining.” |
| “current + 1 = the number of papers” | “current + 1 is the number of papers in the prefix we’ve examined.” |
| “count[c] is saving the paper count” | “count[c] stores the number of papers with exactly c citations.” |
| “the number of citation equals to c” | “the number of papers with exactly c citations” |
| “greater or equal to h” | “greater than or equal to h,” or simply “at least h” |
| “our condition not satisfy anymore” | “The condition no longer holds.” |
| “there is a loop invariant papers += count[h]” | “We update papers by adding count[h]. After the update, papers counts the papers with at least h citations.” |
| “counting 2 and 1 won’t help us find more higher h index” | “Once 3 is valid, checking smaller candidates cannot give us a larger answer.” |

The invariant rewrite also corrects a technical distinction: an assignment is
an operation, whereas an invariant states what remains true.

## A spoken H-Index explanation

> “A straightforward approach is to sort the citation counts in descending
> order. At index i, there are i + 1 papers in the prefix, and citations[i] is
> the smallest citation count in that prefix. If citations[i] is at least
> i + 1, that candidate is valid. This takes O(n log n) time.
>
> We can improve this because the h-index cannot exceed the total number of
> papers, n. I’ll create n + 1 buckets. Each bucket below n counts papers with
> exactly that many citations, and the last bucket counts papers with at least
> n citations.
>
> Then I’ll check h from n down to zero. At each step, I’ll add count[h] to a
> running total. After that update, the total is the number of papers with at
> least h citations. If the total is at least h, I can return h immediately.
> Since we check larger candidates first, this is the maximum valid answer.
> The algorithm takes O(n) time and O(n) extra space.”

For the full derivation and code, see
[H-Index](../leetcode/274_h_index/EXPLANATION.md).
