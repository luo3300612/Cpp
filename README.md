# GA
## 遗传算法求解TSP问题
这是一个使用**遗传算法**解决**TSP问题**的程序，城市的位置内置在变量中，直接运行可以得到一个路径
## 细节
### 1.编码
采用实数编码，一串实数经过排列之后得到的排序索引为一条路径
### 2.适应度函数
适应度函数直接使用目标函数，即一条路径的总长
### 3.初始种群生成
设定的种群规模为N，则初始种群生成的法则是，随机生成N个个体中选择最好的一个，重复生成N次
### 4.选择
直接选择最优秀的前N个个体
### 5.交叉
普通的交叉
### 6.变异
第一种变异方式为更改一个基因位的值
第二种变异方式为调换两个基因位的值
### 7.迭代
3000轮
## 特点
1.种群规模，城市个数，变异率，杂交长度都是可以直接在最开头的全局变量中更改的

2.代码最后有两个Matlab代码，第一个可以画出最优解，第二个当你将每次迭代后最优解输出到output.txt后，能画出动态求解过程

3.我也很想直接用Matlab编写，但是老师非要我c++编然后用Matlab画图，我也很绝望