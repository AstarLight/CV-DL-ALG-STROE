# 数学基础、机器学习、深度学习、计算机视觉知识点汇总

## 大数定律和中心极限定理的区别是什么？

大数定律是说，n只要越来越大，我把这n个独立同分布的数加起来去除以n得到的这个样本均值（也是一个随机变量）会依概率收敛到真值u，但是样本均值的分布是怎样的我们不知道。
中心极限定理是说，n只要越来越大，这n个数的样本均值会趋近于正态分布，并且这个正态分布以u为均值，<a href="https://www.codecogs.com/eqnedit.php?latex=\sigma^2/2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\sigma^2/2" title="\sigma^2/2" /></a>为方差。

中心极限定理指的是样本均值的抽样分布接近于期望为u的正态分布。

大数定理指的是当样本量无穷大时，样本均值接近于总体均值u。

综上所述，这两个定律都是在说样本均值性质。随着n增大，大数定律说样本均值几乎必然等于均值。中心极限定律说，他越来越趋近于正态分布。并且这个正态分布的方差越来越小。

## 线性代数中的特征值和特征向量的本质是什么？
定义里的公式：<a href="https://www.codecogs.com/eqnedit.php?latex=$A\alpha=\lambda\alpha$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$A\alpha=\lambda\alpha$" title="$A\alpha=\lambda\alpha$" /></a>

左边是用矩阵A将向量<a href="https://www.codecogs.com/eqnedit.php?latex=$\alpha$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\alpha$" title="$\alpha$" /></a>做了一个转换，右边是将向量<a href="https://www.codecogs.com/eqnedit.php?latex=$\alpha$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\alpha$" title="$\alpha$" /></a>拉伸了<a href="https://www.codecogs.com/eqnedit.php?latex=$\lambda$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\lambda$" title="$\lambda$" /></a>倍。说明A有这样一个功能：即对向量<a href="https://www.codecogs.com/eqnedit.php?latex=$\alpha$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\alpha$" title="$\alpha$" /></a>变换后，长度拉伸<a href="https://www.codecogs.com/eqnedit.php?latex=$\lambda$" target="_blank"><img src="https://latex.codecogs.com/gif.latex?$\lambda$" title="$\lambda$" /></a>倍，方向不变。需要注意的是：并不是所有的向量都可以被A通过变换拉伸而方向不变。能够被A拉伸且保持方向不变的向量就是A的特征向量，拉伸的倍数就是特征值。



矩阵乘法对应了一个变换，是把任意一个向量变成另一个方向或长度都大多不同的新向量。在这个变换的过程中，原向量主要发生旋转、伸缩的变化。如果矩阵对某一个向量或某些向量只发生伸缩变换，不对这些向量产生旋转的效果，那么这些向量就称为这个矩阵的特征向量，伸缩的比例就是特征值。

