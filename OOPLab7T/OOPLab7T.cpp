#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <ctime>

using namespace std;

// Завдання 1

template <class T>
void findMax(T arr[], int size, T& maxValue, int& count)
{
    maxValue = arr[0];
    count = 1;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] > maxValue)
        {
            maxValue = arr[i];
            count = 1;
        }
        else if (arr[i] == maxValue)
        {
            count++;
        }
    }
}

template<>
void findMax(char* arr[], int size, char*& maxValue, int& count)
{
    maxValue = arr[0];
    count = 1;

    for (int i = 1; i < size; i++)
    {
        int cmp = strcmp(arr[i], maxValue);

        if (cmp > 0)
        {
            maxValue = arr[i];
            count = 1;
        }
        else if (cmp == 0)
        {
            count++;
        }
    }
}

// Завдання 2

template<class T>
void quickSort(T arr[], int left, int right)
{
    int i = left;
    int j = right;

    T pivot = arr[(left + right) / 2];

    while (i <= j)
    {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j)
        {
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j);

    if (i < right)
        quickSort(arr, i, right);
}

template<>
void quickSort(char* arr[], int left, int right)
{
    int i = left;
    int j = right;

    char* pivot = arr[(left + right) / 2];

    while (i <= j)
    {
        while (strcmp(arr[i], pivot) < 0)
            i++;

        while (strcmp(arr[j], pivot) > 0)
            j--;

        if (i <= j)
        {
            char* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(arr, left, j);

    if (i < right)
        quickSort(arr, i, right);
}

// Завдання 3

template<class T>
class Stack
{
private:
    T* data;
    int top;
    int size;

public:

    Stack(int s = 10)
    {
        size = s;
        data = new T[size];
        top = -1;
    }

    ~Stack()
    {
        delete[] data;
    }

    void push(T value)
    {
        if (top < size - 1)
        {
            top++;
            data[top] = value;
        }
        else
            cout << "Стек переповнений\n";
    }

    T pop()
    {
        if (top >= 0)
        {
            return data[top--];
        }

        cout << "Стек порожній\n";
        return T();
    }

    bool empty()
    {
        return top == -1;
    }

    void print()
    {
        for (int i = top; i >= 0; i--)
            cout << data[i] << " ";

        cout << endl;
    }
};

// Завдання 4

template<class T>
class TreeNode
{
public:
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

template<class T>
class BinaryTree
{
private:

    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, T value)
    {
        if (node == NULL)
            return new TreeNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else
            node->right = insert(node->right, value);

        return node;
    }

public:

    BinaryTree()
    {
        root = NULL;
    }

    void insert(T value)
    {
        root = insert(root, value);
    }

    TreeNode<T>* getRoot()
    {
        return root;
    }
};


template<class T>
class TreeIterator
{
private:

    Stack<TreeNode<T>*> st;

public:

    TreeIterator(TreeNode<T>* root) :st(20)
    {
        while (root)
        {
            st.push(root);
            root = root->left;
        }
    }

    bool hasNext()
    {
        return !st.empty();
    }

    T next()
    {
        TreeNode<T>* current = st.pop();

        T value = current->data;

        TreeNode<T>* temp = current->right;

        while (temp)
        {
            st.push(temp);
            temp = temp->left;
        }

        return value;
    }
};



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(0));

    int choice;

    do
    {
        cout << "\n========== МЕНЮ ==========\n";
        cout << "1 - Завдання 1 (максимум і кількість)\n";
        cout << "2 - Завдання 2 (швидке сортування)\n";
        cout << "3 - Завдання 3 (стек)\n";
        cout << "4 - Завдання 4 (бінарне дерево)\n";
        cout << "0 - Вихід\n";

        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice)
        {

        case 1:
        {
            const int n = 10;
            int arr[n];

            int source;

            cout << "\nСпосіб введення:\n";
            cout << "1 - Клавіатура\n";
            cout << "2 - Файл\n";
            cout << "3 - Випадкові числа\n";

            cin >> source;

            if (source == 1)
            {
                for (int i = 0; i < n; i++)
                {
                    cout << "arr[" << i << "]=";
                    cin >> arr[i];
                }
            }

            else if (source == 2)
            {
                ifstream file("input.txt");

                for (int i = 0; i < n; i++)
                    file >> arr[i];

                file.close();
            }

            else if (source == 3)
            {
                for (int i = 0; i < n; i++)
                {
                    arr[i] = rand() % 100;
                }
            }

            cout << "\nМасив:\n";

            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";

            cout << endl;

            int maxValue;
            int count;

            findMax(arr, n, maxValue, count);

            cout << "\nМаксимальне значення: "
                << maxValue << endl;

            cout << "Кількість: "
                << count << endl;

            break;
        }


        case 2:
        {
            const int n = 10;

            int arr[n];

            for (int i = 0; i < n; i++)
            {
                arr[i] = rand() % 100;
            }

            cout << "\nДо сортування:\n";

            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";

            quickSort(arr, 0, n - 1);

            cout << "\n\nПісля сортування:\n";

            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";

            cout << endl;

            break;
        }


        case 3:
        {
            Stack<int> s(5);

            int x;

            cout << "\nВведіть 5 елементів:\n";

            for (int i = 0; i < 5; i++)
            {
                cin >> x;
                s.push(x);
            }

            cout << "\nСтек:\n";
            s.print();

            cout << "\nВидалено: "
                << s.pop() << endl;

            cout << "\nСтек після видалення:\n";

            s.print();

            break;
        }


        case 4:
        {
            BinaryTree<int> tree;

            int x;

            cout << "\nВведіть 7 елементів:\n";

            for (int i = 0; i < 7; i++)
            {
                cin >> x;
                tree.insert(x);
            }

            TreeIterator<int> it(
                tree.getRoot()
            );

            cout << "\nОбхід дерева:\n";

            while (it.hasNext())
            {
                cout << it.next() << " ";
            }

            cout << endl;

            break;
        }


        case 0:
            cout << "\nПрограма завершена\n";
            break;


        default:
            cout << "\nПомилка!\n";
        }

    } while (choice != 0);

    return 0;
}