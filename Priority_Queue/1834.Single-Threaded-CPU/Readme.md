### 1834.Single-Threaded-CPU

我们将所有的tasks按照入列时间从早到晚排序。同时维护一个curTime表示当前的时间，初始为0。

如果curTime晚于目前最早待入列的任务，那么我们就将该任务放入任务池。如果curTime早于目前最早待入列的任务，就在已经任务池（一个优先队列）里面挑选可以启动的任务，挑选的原则按照题目的要求：先看处理时长，再看ID大小。所以显然，任务池的数据结构就是一个优先队列。

每处理完一个任务，curTime就更新变得更大。直至curTime大于等于当前最早待入列的任务。然后重复之前的操作，直至所有任务入列，以及所有任务池里的任务完成。
