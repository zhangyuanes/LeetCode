### 1723.Find-Minimum-Time-to-Finish-All-Jobs

#### 解法1：状态压缩DP
考虑到只有不超过12件jobs，可以用大小不超过4096的01二进制bit来表示任何jobs的组合状态。我们令dp[i][state]表示使用i个工人、分配state所代表的jobs时，可以得到的the minimum possible maximum working time。突破口是第i个工人做了哪些工作？我们可以枚举state的子集subset作为第i个工人的分配任务，那么状态转移方程
```cpp
dp[i][state] = min{max(dp[i-1][state-subset], time[subset])} for all subsets.
```

#### 解法2：二分搜值+状态压缩DFS
解法1虽然写法简单，但是效率并不高。事实上很多dp[i][state]的状态其实早早对应了某个工人被分配了过长的时间，但是我们没有剪枝，而是暴力把这个二维循环统统计算了出来。

高效的办法就是用二分搜值来假设单个工人的时间上限threshold。然后判断在th的前提下，能否DFS搜索出一个可行解。这里依然可以用状态压缩的DFS。初始状态是(1<<n)-1，每一个回合就减去一个subset（注意这个subset的总时间必须小于等于th）。经过k个回合（分配了k个工人）看看是否能将状态减至0，代表所有的任务都已经安排完毕。

#### 解法3：二分搜值+常规DFS
常规的DFS也可以写，而且剪枝比状态压缩更灵活。我们令workers数组表示k个工人每人分配的时长。在递归函数dfs(i)里，我们试图分配第i个工作。只要当前workers[j]不超过th，那么我们就可以把第i个工作分配给第j个工人，然后继续递归下去。直至所有的任务都分配完。

我们用两个剪枝来优化时间。第一，我们优先分配时间较长的工作，这样能更早的触发限制，及早终止不必要的探索。第二，在某一层递归中，我们我们已经尝试过把第i个工作分配给某个空闲的工人，那么我们就不用再尝试把第i个工作分配给其他空闲的工人，因为效果是等价的。
