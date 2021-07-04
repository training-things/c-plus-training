# 构造函数

## 默认构造函数

```cpp
class Box {
public:
    // Default constructor
    Box() {}

    // Initialize a Box with equal dimensions (i.e. a cube)
    explicit Box(int i) : m_width(i), m_length(i), m_height(i) // member init list
    {}

    // Initialize a Box with custom dimensions
    Box(int width, int length, int height)
        : m_width(width), m_length(length), m_height(height)
    {}

    int Volume() { return m_width * m_length * m_height; }

private:
    // Will have value of 0 when default constructor is called.
    // If we didn't zero-init here, default constructor would
    // leave them uninitialized with garbage values.
    int m_width{ 0 };
    int m_length{ 0 };
    int m_height{ 0 };
};
```

## 复制构造函数和复制赋值运算符


复制构造函数可能具有以下其中一个签名：

```cpp
    Box(Box& other); // Avoid if possible--allows modification of other.
    Box(const Box& other);
    Box(volatile Box& other);
    Box(volatile const Box& other);

    // Additional parameters OK if they have default values
    Box(Box& other, int i = 42, string label = "Box");

// 尽可能创建复制构造函数的参数 const 类名的类型 & 。 这可防止复制构造函数意外更改从中复制它的对象。 它还允许从 const 对象复制。

```

定义复制构造函数时，还应将复制赋值运算符定义 (=) 

可以通过将复制构造函数定义为已删除，阻止复制对象：

```cpp
    Box (const Box& other) = delete;
```


## 移动构造函数和移动赋值运算符



## 委托构造函数


