#include <iostream>
#include <string>

using namespace std;

enum
{
    sizeOfBuffer = 132
};

// Define a binary tree structure.
struct BTree
{
    char *szText;
    BTree *Left;
    BTree *Right;
};

// Define a pointer to the root of the tree.
BTree *btRoot = 0;

int Add1(BTree **Root, char *szToAdd); // 指向指针的指针
int Add2(BTree *&Root, char *szToAdd); // 对指针的引用
void PrintTree(BTree *btRoot);


// 函数 Add1 和 Add2 在功能上是等效的，尽管它们不是以相同方式调用的。 
// 不同之处是 Add1 使用双间接寻址，但 Add2 使用对指针的引用的便利性。

int main(int argc, char *argv[])
{

    cout << "argc: " << argc << endl;

    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " [1 | 2]"
             << "\n";
        cerr << "\nwhere:\n";
        cerr << "1 uses double indirection\n";
        cerr << "2 uses a reference to a pointer.\n";
        cerr << "\nInput is from stdin. Use ^Z to terminate input.\n";

        return 1;
    }

    cout << "argv[0]: " << argv[0] << endl;
    cout << "argv[1]: " << argv[1] << endl;

    char *szBuf = new char[sizeOfBuffer];

    if (szBuf == NULL)
    {
        cerr << "Out of memory!\n";
        return -1;
    }

    // Read a text file from the standard input device and
    //  build a binary tree.
    while (!cin.eof())
    {
        cin.get(szBuf, sizeOfBuffer, '\n');
        cin.get();

        if (strlen(szBuf))
        {
            switch (*argv[1])
            {
            case '1':
                /* code */
                Add1(&btRoot, szBuf);
                break;
            case '2':
                Add2(btRoot, szBuf);
                break;
            default:
                cerr << "Illegal value '"
                     << *argv[1] << "' supplied for add method. Choose 1 or 2" << endl;
                break;
            }
        }
        /* code */
    }

    // Display the sorted list.
    PrintTree(btRoot);
}

// PrintTree: Display the binary tree in order.
void PrintTree(BTree *MybtRoot)
{
    // Traverse the left branch of the tree recursively.
    if (MybtRoot->Left)
        PrintTree(MybtRoot->Left);

    // Print the current node.
    cout << MybtRoot->szText << "\n";

    // Traverse the right branch of the tree recursively.
    if (MybtRoot->Right)
        PrintTree(MybtRoot->Right);
}

// Add1: Add a node to the binary tree.
//       Uses double indirection.
int Add1(BTree **Root, char *szToAdd)
{
    if ((*Root) == 0)
    {
        (*Root) = new BTree;
        (*Root)->Left = 0;
        (*Root)->Right = 0;
        (*Root)->szText = new char[strlen(szToAdd) + 1];
        strlcpy((*Root)->szText, szToAdd, (strlen(szToAdd) + 1));

        return 1;
    }
    else
    {
        if (strcmp((*Root)->szText, szToAdd) > 0)
            return Add1(&((*Root)->Left), szToAdd);
        else
            return Add1(&((*Root)->Right), szToAdd);
    }
}

// Add2: Add a node to the binary tree.
//       Uses reference to pointer
int Add2(BTree *&Root, char *szToAdd)
{
    if (Root == 0)
    {
        Root = new BTree;
        Root->Left = 0;
        Root->Right = 0;
        Root->szText = new char[strlen(szToAdd) + 1];
        strlcpy(Root->szText, szToAdd, (strlen(szToAdd) + 1));
        return 1;
    }
    else
    {
        if (strcmp(Root->szText, szToAdd) > 0)
            return Add2(Root->Left, szToAdd);
        else
            return Add2(Root->Right, szToAdd);
    }
}
