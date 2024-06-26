### 3139.Minimum-Cost-to-Equalize-Array

首先，我们令cost2=min(cost1*2, cost2)，保证使用第二种操作不会比第一种操作更亏。这样变换之后，我们知道应该尽量使用cost2更合算。

其次要注意，并不是操作的次数越少，付出的代价就越少。比如说nums=[1,4,4]，我们可以使用三次cost1，使得所有元素最终变为4；也可以使用六次cost2，使得最终所有元素变成7. 哪种方案更好，取决于cost1和cost2的大小关系。因此本题的最优策略，不一定是将所有的元素都变成max(nums)，而是可能一个更大的数字，我们记做limit。假如limit是已知量，我们如何计算需要用的最小代价呢？

既然我们需要将所有元素都增至limit，那么将数组排序后，每个元素离目标还差{diff0, diff1, diff2, ...., 0}。记所有的diff之和为`diff_all`。我们容易理解这样一个结论：如果在所有的diff里面存在一个超过`diff_all`一半的绝对多数，那它必然就是diff0. 我们为了尽可能多地利用第二种操作，必然是每增加nums0的同时搭配一个增加其他的元素。最终我们会进行cost2的操作共`diff_all-diff0`次。剩下来还没增至limit的只是nums0，还差`limit-(diff_all-diff0)`，这就需要用cost1来实现。于是总共的代价为`(diff_all-diff0)*cost2 + (limit-(diff_all-diff0))*cost1`.

相反，如果{diff}里面不存在一个绝对多数，根据Boyer-Moore Majority Voting的原理，那么我们必然可以持续找到一对pair进行增一操作，且它们来自两个不同的元素。最终直至所有元素都增至limit，或者只差一次增一操作故无法找到pair了。这种情况下，我们的cost2操作了`diff_all/2`次，并且根据diff_all的奇偶性，可能再增加一次cost1的操作。

以上我们知道当limit已知时，如何计算最小代价。但是limit该如何确定呢？我们发现，随着limit的增长，{diff}数组整体变大，越来越不可能出现第一种情况。而一旦{diff}进入第二种情况时，就已经将cost2用到了极致（即只会用最多一次cost1），再增长limit就没有意义。那什么时候{diff}会进入第二种情况呢？显然，至少当limit变成`2*max(nums)`，{diff}里面肯定不会出现绝对多数了（当n>=3时）：这是因为diff0小于2m，而其他每个diff都大于m。

所以我们只需要穷举limit的范围`[m, 2m]`，对于给定的limit我们计算最小代价，全局再取最小即可。考虑到m是1e6，这是可以暴力实现的。


