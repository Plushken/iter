#include "List.h"
#include <iostream>
#include <time.h>

using namespace std;

unsigned counting(ListIterator* l)
{
    int t = 0;
    if (l->operator*())
    {
        cout << "Элементы: ";
        do 
        {
            t++;
            cerr << l->operator()() << " ";
        } 
        while (l->operator++());
    }
    else
        cerr << "Нет элементов!";
    cerr << endl;
    return t;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    int n, k;
    srand((unsigned)time(0));
    unsigned cap, count;
    cout << "Введите объём стека: ";
    cin >> cap;
    cout << "Введите количество элементов для заполнения стека: ";
    cin >> count;
    if (cap < count)
    {
      cout << "Переполнение стека";
      return 0;
    }
    List list(cap);
    for (auto i = 0; i < count; i++)
    {
        int p = rand() % 10;
        if (list.append(p))
            cout << p << " ";
    }
    ListIterator* list1;
    ListIterator* list2;
    cout << "Введите позицию числа, которую хотите вывести ";
    cin >> n;
    cout << "Введите число, которое хотите вывести ";
    cin >> k;
    try
    {
        list1 = list.createIterator(Iterators::STEP, n);
        list2 = list.createIterator(Iterators::VALUE, k);
    }
    catch (exception& ex)
    {
        cerr << ex.what();
        return 0;
    }
    cout << "Выведенных элементов" << endl;
    cout << counting((ListIteratorStep*)list1) << endl;
    cout << counting((ListIteratorValue*)list2) << endl;
}