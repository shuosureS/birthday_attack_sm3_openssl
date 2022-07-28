# Project: implement the naïve birthday attack of reduced SM3

### 刘硕-202000460043-shuosureS

##  简介

本实验实现了生日攻击并通过调用openssl中的sm3来验证生日攻击是否成功，并测试不同位数所用的时间。生日攻击是一种密码学攻击手段，所利用的是概率论中生日问题的数学原理。这种攻击手段可用于滥用两个或多个集团之间的通信。此攻击依赖于在随机攻击中的鸽巢原理。

## 代码实现

首先固定了所要攻击的输入tinput，并调用openssl中sm3来得到tagart得到hash值。

```c_cpp
    unsigned char tinput[256] = "abcddef123456908213456a";
    int tlen = 23;
    unsigned char tagart[32];
    sm3_openssl(tinput, tlen, tagart);
```

然后初始化生日攻击的input，output，进行生日攻击，通过判断output和tagart的前目标位是否相同判断攻击是否成功并记录时间，这里对tagart数组的前4项进行了比较也就是32bit的生日攻击。

```c_cpp
    unsigned char input[256] = "";
    int ilen = 0;
    unsigned char output[32];
    int i=0;
    int start, end;
    start = clock();
    while (1) {
        ilen=inttohex(i, input);        
        sm3_openssl(input, ilen, output);
        
        if (output[0]==tagart[0] &&output[1]==tagart[1]&&output[2]==tagart[2] && output[3] == tagart[3])
        {
            end = clock();
            printf("攻击成功\n");
            printf("time=%dms\n", end - start);
            
            break;
        }
        i++;
    }
```

## 结果

|bit数|时间|
|--|--|
|32|664535ms|
|24|7813ms|
|16|32ms|

![image]()

![截图]()

![截图]()
