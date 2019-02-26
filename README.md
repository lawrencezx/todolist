# todolist

**todolist还处于测试阶段**

todolist是一个极简风格的待办事物列表,它包括两部分,一个是当天事物的待办列表,另外一个是长期的计划.

## 安装方法
```
sudo make install
sudo make uninstall
```

## 当天事物
增加,删除,交换顺序等功能都有
```
➜  todolist git:(master) ✗ todolist   
date:26, 2, 2019
I don't have anything to do yet!

 建立更好人际关系的三种方法：１寻找超棒的新人际关系。２改造你现有的人际关系。３改变你自己。 
➜  todolist git:(master) ✗ todolist -w
'q' to exit
<<读完一篇论文  
<<健身一小时
<<q
➜  todolist git:(master) ✗ todolist   
date:26, 2, 2019
I have 2 things to do today!

 List 1 => 读完一篇论文
 List 2 => 健身一小时

 简单的成功方程：成功＝快乐＋持续进步。 
➜  todolist git:(master) ✗ todolist -s 1 2
➜  todolist git:(master) ✗ todolist       
date:26, 2, 2019
I have 2 things to do today!

 List 1 => 健身一小时
 List 2 => 读完一篇论文

 有时，人们在无意之中卷入某种工作，而这却给他们带来了终极的满足感。 
➜  todolist git:(master) ✗ todolist -r 1
List 1 has been deleted!
➜  todolist git:(master) ✗ todolist     
date:26, 2, 2019
I have only one thing to do today!

 List 1 => 读完一篇论文

 有些时候，人们进入某种关系，完全是因为吸引力。 
```


## 长期计划
增加,删除,交换顺序等功能都有
```
➜  todolist git:(master) ✗ todolist -t 
date:26, 2, 2019
I don't have any target to achieve!

 我们都想被爱。我们都想去爱。我们都想有人能一起分享生活。 
➜  todolist git:(master) ✗ todolist -t w
Please input your target and the days to achieve your target
 'q' to exit
TARGET<<看一部电影
DAYS  <<0
TARGET<<学会做一道菜
DAYS  <<1
TARGET<<每周健身四次,每次一小时
DAYS  <<90
TARGET<<每天坚持11点前睡觉,7点左右起床
DAYS  <<365
TARGET<<q
➜  todolist git:(master) ✗ todolist -t  
date:26, 2, 2019
I have 4 targets to achieve!

 COUNTDOWN    TARGET
 deadline  => 看一部电影
    1 day  => 学会做一道菜
   90 days => 每周健身四次,每次一小时
  365 days => 每天坚持11点前睡觉,7点左右起床

 你最终获得了“你想要的一切”，但却无人可以分享。 
```
