DL 的本质就是，找到一个最佳参数组合也就是(Wi, Xi) 的组合，使得lost function 最小，也就是越接近预测的真实值

那其中最终要的一点就是找到当中每一个参数的d(导数), 有了这个导数，我们能调整影响

其中的方法就是 backpropagation(反向传播算法) 其实就是一个递归调用链式法则

that's it

The rest is optimization
