
在网络上传输数据时，由于数据传输的两端可能对应不同的硬件平台，采用的存储字节顺序也可能不一致，
因此 TCP/IP 协议规定了在网络上必须采用 网络字节顺序(也就是大端模式)  。
网络传输一般采用大端序，也被称之为网络字节序，或网络序。IP协议中定义大端序为网络字节序。
Berkeley套接字定义了一组转换函数，用于16和32bit整数在网络序和本机字节序之间的转换。htonl，htons用于本机序转换到网络序；ntohl，ntohs用于网络序转换到本机序。



总结：
大端是高字节存放到内存的低地址   这是人类读写数值的方法。
小端是高字节存放到内存的高地址

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9pbWFnZXMwLmNuYmxvZ3MuY29tL2Jsb2cvMjI4MDI0LzIwMTMwNi8wODE2NTI1OS0zMzQ4OTM3YTQ5ZjM0Y2JjOTk2OTU5ZmYyYjIzNTY4ZS5qcGc?x-oss-process=image/format,png)

![](https://images0.cnblogs.com/blog/468825/201403/051626057689256.png)


什么是大小端？如何确定大小端？ https://zh.wikipedia.org/wiki/%E5%AD%97%E8%8A%82%E5%BA%8F
https://blog.csdn.net/wwwlyj123321/article/details/100066463
https://www.ruanyifeng.com/blog/2016/11/byte-order.html



为什么会有小端字节序？
答案是，计算机电路先处理低位字节，效率比较高，因为计算都是从低位开始的。所以，【计算机的内部处理都是小端字节序】。
但是，人类还是习惯读写大端字节序。所以，除了计算机的内部处理，其他的场合几乎都是【大端字节序，比如网络传输和文件储存】。


处理器体系
- x86、MOS Technology 6502、Z80、VAX、PDP-11等处理器为小端序；
- Motorola 6800、Motorola 68000、PowerPC 970、System/370、SPARC（除V9外）等处理器为大端序；
- ARM、PowerPC（除PowerPC 970外）、DEC Alpha、SPARC V9、MIPS、PA-RISC及IA64的字节序是可配置的。