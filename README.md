# CSAPP Labs

## 1. Data Lab

1. 使用位运算判断大小

首先是使用位运算判断正负（也就是判断符号位），然后只需要做减法（用位运算转换为补码加法）就可以转换为正负判断了

2. 使用位运算实现条件语句`x ? y : z`

构造一个函数$f(x)$，使得时$f(0)=0,f(x)_{x\neq0}=0xffffffff$，这样就可以使得这个语句等于$f(x)\&x\space\|\space\sim f(x)\&z$

3. `howManyBits()`

关键是要获得一个整数的最高位的1的位置。可以先分组为4个Byte，最后算出在哪一位。我的做法似乎需要特判0和-1的情况。最好刚好卡在90个运算符...

4. 浮点数*2

判断规约形式

5. 浮点数转整数

循环即可~~（能用循环真好）~~

**总结**：`howManyBits()`卡了非常久。最后3个浮点数函数难度不大，主要是要熟悉浮点数格式和一些细节

## 2. Bomb Lab

函数调用参数传递：rdi, rsi, rdx, rcx, r8, r9

1. Phase 1

对phasa_1打断点之后发现调用了strcmp函数来进行比较，比较的字符串地址在0x402400，直接查看这一段内存

```
b phase_1
(lldb) x/90cb 0x402400
0x00402400: Border relations with Canada hav
0x00402420: e never been better.\0\0\0\0Wow! You
0x00402440: 've defused the secret sta
```

得到第一个密码`Border relations with Canada have never been better.`

2. Phase 2

发现是scanf输入6个整数，然后应该是依次判断

首先是第二个整数是第一个整数的2倍

```
Process 5976 stopped
* thread #1, name = 'bomb', stop reason = instruction step over
    frame #0: 0x0000000000400f17 bomb`phase_2 + 27
bomb`phase_2:
->  0x400f17 <+27>: movl   -0x4(%rbx), %eax
    0x400f1a <+30>: addl   %eax, %eax
    0x400f1c <+32>: cmpl   %eax, (%rbx)
    0x400f1e <+34>: je     0x400f25                  ; <+41>
```

然后是`eax=a[1]*2,eax==a[2]`，所以第三个整数又得是第二个整数的2倍

然后是一样的逻辑，所以直接`1 2 4 8 16 32`，不过如果输入6个0会过不了，因为对`a[0]>0`做了判断（

```
b phase_2
(lldb) x/90cb 0x4025C3
0x004025c3: %d %d %d %d %d %d\0Error: Prematu
0x004025e3: re EOF on stdin\0GRADE_BOMB\0Error
0x00402603: : Input line too long\0%d %

1 8 
```

3. Phase 3

7 327

4. Phase 4

a=7, b=0

`sscanf(line, "%d %d", &a, &b);`

a=rdx, b=rcx

满足a<15

`func4(edx=14, esi=0, edi=a)`：要求func4返回值等于0

```assembly
eax=edx-esi=14
ecx=eax=14
ecx>>=31;逻辑右移，只取符号位，ecx=0
eax+=ecx;eax=14
eax>>=1;eax=7
ecx=lea(rsi+rax)=7
要求ecx>=edi==a && ecx<=edi==a，即输入为7即可
```

之后还有一个判断b==0的条件

5. Phase 5

首先判断字符串长度==6，之后进行了查表，将长度代入一个数组中得到目标字符串，最后和flyers相比较，所以反向查表：9, 15, 14, 5, 6, 7，也就是输入的字符串&15的结果IONEFG

```assembly
开了20个字节的栈
ecx=s[1]
rax=0...5
rsp[rax]=cl=s[0]
rdx=rsp[rax]&0xf
edx=arr[edx]
rsp[rax]=dl
;arr[]="madu iers nfot vbyl So you think you can stop the bomb with ctrl-c, do you?" "Curses, you\ve fou"
rsp[10...15]和"flyers"比较
```

6. Phase 6

仍然调用了读入6个整数的函数，6个整数放在了栈中

每一个数小于等于6，且和前面的数字不相等（即互不相等）

1 2 3 4 5 6

```assembly
eax=rsp[0]-1
eax<=5

r12d=1
ebx=r12d=1

rax=ebx
eax=rsp[rax]=rsp[1]
eax!=rsp[0]

ebx++
ebx<=5?

r13+=4

```

每个数都变为7-x

```assembly
rsi=rsp+0x18
rax=rsp
ecx=7
edx=ecx-rsp[0]=7-rsp[0]
rsp[0]=edx=7-rsp[0]
rax+=4

```

```assembly
esi=0
ecx=rsp[0]
ecx<=1?NO;由于每个数都小于等于5，所以7-x必定大于等于2
eax=1
edx=0x6032d0
rdx=arr+8=0x6032d8
eax++
eax==ecx?
```

关键在于链表：

```
(gdb) x/12xg 0x6032d0
0x6032d0 <node1>:	0x000000010000014c	0x00000000006032e0
0x6032e0 <node2>:	0x00000002000000a8	0x00000000006032f0
0x6032f0 <node3>:	0x000000030000039c	0x0000000000603300
0x603300 <node4>:	0x00000004000002b3	0x0000000000603310
0x603310 <node5>:	0x00000005000001dd	0x0000000000603320
0x603320 <node6>:	0x00000006000001bb	0x0000000000000000
```

发现是比较后面那8位，所以顺序是3,4,5,6,1,2；由于前面进行了7-x操作，所以答案是`4 3 2 1 6 5`