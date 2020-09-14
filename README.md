### 编译方法
Visual Studio中选择 文件->新建->从现有代码创建项目，输入自定义项目路径和项目名，点击下一步，选择控制台应用程序项目，然后点击完成即可。
### Task 1
##### 实现思路
由于OrderBook需要根据价格排序，并且一个价格可以对应多个order，因此很自然地想到使用std::multimap来存储。

Ask和Bid分别需要升序和降序排列，因此将Ask和Bid的数据结构定义为
```
std::multimap<double, Order, std::less<double>> ask_map;
std::multimap<double, Order, std::greater<double>> bid_map;
```

同时，为了根据orderid快速查找和删除某一个order，需要维持orderid到multimap中的order的映射关系，这里选择使用multimap的iterator作为value。具体定义如下：
```
std::unordered_map<std::string, std::multimap<double, Order>::iterator> id_iter_map;
```

##### 时间复杂度
删除一个order: O(1)

新增一个order：如果是Buy的order，首先需要遍历ask_map，撮合trade，理论上最差为O(n)。插入一个新的order为O(log n)

### Task 2
##### 实现思路
要用最小的步骤将现有的orders变为目标orders，首先要将两者相同的部分去掉（相同是指价格和数量都相同）。因此将order放入std::multiset中，并定义比较函数。
```
std::multiset<Order> cur_order_set;
std::multiset<Order> desired_order_set;
```

这样所有order就根据价格和数量完成了排序。此时同时用两个iterator遍历两个multiset，找到相同的order并删掉。

最后再次遍历两个multiset，根据两者价格和数量的不同，生成A、X、M的order
##### 时间复杂度
构造multiset：O(nlog n)

两次遍历multiset：O(2n)
