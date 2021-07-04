{
    class widget
    {
    private:
        int *data;

    public:
        widget(const int size) { data = new int[size]; } // acquire
        ~widget() { delete[] data; }                     // release
        void do_something() {}
    };

    void functionUsingWidget()
    {
        // w 拥有内存资源，因此必须在其析构函数中包含代码以删除内存。
        // 自 c + + 11 起，有一种更好的方法来编写前面的示例：使用标准库中的智能指针。 智能指针处理其拥有的内存分配和删除操作。 使用智能指针，无需在 widget 类中使用显式析构函数。
        widget w(1000000); // lifetime automatically tied to enclosing scope
                           // constructs w, including the w.data member
        w.do_something();

    } // automatic destruction and deallocation for w and w.data
};

{
    class widget1
    {
    private:
        gadget g; // lifetime automatically tied to enclosing object
    public:
        void draw();
    };

    void functionUsingWidget()
    {
        //  w的简单对象。 它在函数作用域的堆栈上声明，并在函数块的末尾被销毁。 对象 w 不拥有任何资源（如堆分配的内存）
        widget1 w; // lifetime automatically tied to enclosing scope
                   // constructs w, including the w.g gadget member
        // ...
        w.draw();
        // ...
    } // automatic destruction and deallocation for w and w.g
      // automatic exception safety,
      // as if "finally { w.dispose(); w.g.dispose(); }"
};