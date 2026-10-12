# Source and judge mapping

User reference: [AcWing memo](https://www.acwing.com/file_system/file/content/whole/index/content/4331/).
The page could not be retrieved on 2026-10-12. The supplied memo and Go code
are the source for this recap; no AcWing problem number or numeric constraints
are inferred from the URL. The embedded Evernote resource was not accessible.

Verified target: [LeetCode 56 — Merge Intervals](https://leetcode.com/problems/merge-intervals/description/),
Medium. Its statement was publicly accessible. It matches the supplied Go
function's objective: return merged intervals, with touching endpoints merged.
Equivalence is to the supplied code, not an independently retrieved AcWing statement.

## Original memo

1. 按区间的左端点排序
2. 扫描整个区间，扫描的过程当中，把所有可能有交集的区间合并。

```text
st_______________ed // 当前扫描的区间
假设当前扫描的是第i个区间
那么第i个区间和当前这个区间的关系有以下几种
1. 区间i与当前区间有交集 // 更新区间右端点
2. 区间i与当前区间没有交集 // 将当前区间放到结果里面，把 i区间当成当前区间
```

Original image reference:
`evernotecid://251D1A67-CA41-416B-BF84-A58D319CBC7B/appyinxiangcom/25393691/ENResource/p1929`

## Original Go implementation

```go
func merge(intervals [][]int) [][]int {
    // st, ed
    //

    sort.SliceStable(intervals, func(i, j int) bool {
        return intervals[i][0] < intervals[j][0]
    })
    n := len(intervals)

    var res [][]int
    st := intervals[0][0]
    ed := intervals[0][1]
    for i := 1; i < n; i ++ {
        if intervals[i][0] <= ed{
            ed = max(intervals[i][1], ed)
        } else {
            res = append(res, []int{st, ed})
            st = intervals[i][0]
            ed = intervals[i][1]
        }
    }

    res = append(res, []int{st, ed})
    return res
}

func max(a, b int) int {
    if a < b {
        return b
    }

    return a
}
```
