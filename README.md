# todolist

**todolist还处于测试阶段**

todolist是一个极简风格的待办事物列表,它包括两部分,一个是当天事物的待办列表,另外一个是长期的计划.

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
