### 2170.Minimum-Operations-to-Make-the-Array-Alternating

我们将所有偶数位的数字和所有奇数位的数字分别进行频率统计，保存至数组Map1和Map2，并且按照频率从大到小排序。

如果Map1和Map2分别词频最高的数字不相同，那么意味着最优方案就是保留这两种数字。如果Map1和Map2分别词频最高的数字相同，那么要么保留Map1最高频的数字+Map2次高频的数字，或者保留Map1次高频的数字+Map2最高频的数字。

特别注意，Map1和Map2保存的数字种类可能只有1种，需要特别处理。