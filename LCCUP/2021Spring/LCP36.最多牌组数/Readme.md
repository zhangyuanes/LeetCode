### LCP36.最多牌组数

我们令dp[i][j]表示当我们处理完牌面x-1时，手头存有的牌面为x-2的有i张、牌面为x-1的有j张时，所能够构建的最多牌组数，并且在相同牌组数的情况下取顺子最少的方案。类似地，当我们处理完牌面x后，我们目的是推导出新的dp2[jj][kk]，表示当我们处理完牌面为x时，且手头存有的牌面为x-1的有jj张、牌面为x的有kk张时，所能够构建的最多牌组数。由此我们不断地处理完所有牌面。最终答案在dp[n-1][n]中取最大值。

这里解释一下“在相同牌组数的情况下取顺子最少的方案”。比如说我们手头有x-2的牌3张，x-1的牌3张，x的牌3张。我们会构建三组```(x-2,x-2,x-2)，(x-1,x-1,x-1)，(x,x,x)```，而非三组```(x-2,x-1,x)```。

接下来我们查看dp的这两个维度的范围，我们断言只需要考虑i与j的范围不超过4（精确地说i不需要超过2）. 为什么呢？假设我们在处理牌面x前，手头有牌面为x-2的有3张，那么这三张x-2该怎么和后续的牌发挥组合作用呢？显然只有一种途径，那就是在x-1和x都至少有三张牌的前提下，我们可以打出三组```(x-2,x-1,x)```；否则这三张x-2等于没有用。但是即使很幸运，x-1和x都很给力，可以组成三组```(x-2,x-1,x)```，但是这就违反了我们之前的约定：“在相同牌组数的情况下取顺子最少的方案”，我们事实上只会构建三组刻子。那么意味着如果牌面为x-2的剩余三张或以上的话，其实并不会与后续牌面组合起实质性作用，不如在当初就早早打出```(x-2,x-2,x-2)```.这就告诉我们，dp[i][j]中的i其实超过2是没有意义的，即dp[3][j]其实就是dp[0][j]+1, dp[4][j]其实就是dp[1][j]+1 ... 

同理我们可以分析dp[i][j]中的j其实超过4是没有意义的。所以我们在读取或者更新dp[i][j]时始终只考虑i,j<=4的情况。

接下来的转移方程就比较容易想了。我们遍历i和j的取值，表示当前存有i张牌面x-2，j张牌面x-1，同时有牌面x的个数是freq。

我们先考虑可以构造多少```(x-2,x-1,x)```。这个组数就是```a = min(i,j,freq)```. 确定了这个组合，那么此时牌面x-2剩下i-a张，牌面x-1剩下j-a张，牌面x剩下freq-a张。

这个时候我们计算下一轮的dp2[jj][kk]，表示如果处理完牌面x之后，如果保留x-1的牌面jj张，x的牌面kk张（供以后使用），那么此时收获多少组合？那么就是```dp[i][j] + a + (i-a)/3 + (j-a-jj)/3 + (freq-a-kk)/3```.最后三项就是刻子的组合数。

本题还有一个很重要的边界条件。就是如果处理当前牌面x时，发现没有牌面x-1怎么办？注意：这样的话上一轮的dp[i][j]其实并不能用来推导这一轮的dp2[jj][kk]。但是有一项是例外的，就是dp[0][0]，我们虚拟的认为此时存有0张牌面x-2、0张牌面x-1，但注意dp[0][0]的值应该取当前dp[?][?]里的最大值。虽然dp[i][j]不能用来推导新的dp，但是它们代表了之前已经构造的最大组数，需要将这个信息保留。
