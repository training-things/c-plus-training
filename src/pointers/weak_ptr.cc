#include <assert.h> 
#include <memory.h>


using namespace std;

class Node final
{
public:
    using this_type = Node;

    // 注意这里，别名改用weak_ptr
    using shared_type = std::weak_ptr<this_type>;

public:
    shared_type next; // 因为用了别名，所以代码不需要改动
};

int main()
{
    auto n1 = make_shared<Node>(); // 工厂函数创建智能指针
    auto n2 = make_shared<Node>(); // 工厂函数创建智能指针

    n1->next = n2; // 两个节点互指，形成了循环引用
    n2->next = n1;

    assert(n1.use_count() == 1); // 因为使用了weak_ptr，引用计数为1
    assert(n2.use_count() == 1); // 打破循环引用，不会导致内存泄漏

    if (!n1->next.expired())
    {                               // 检查指针是否有效
        auto ptr = n1->next.lock(); // lock()获取shared_ptr
        assert(ptr == n2);
    }
}