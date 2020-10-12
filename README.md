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

a=14, b=125

满足a<15

func4：

```assembly
rsp-=8
eax=edx-esi
ecx=eax=14
ecx>>=31
eax+=ecx
eax>>=1
ecx=lea(rsi+rax)
ecx<=edi?
ecx>=edi?

```

