#pragma once
#include <list>
using namespace std;
class ListIterator;

enum class Iterators 
{
    STEP,
    VALUE
};

class List
{
public:
    list <int> stack;
    list <int>::iterator pos;
public:
    friend class ListIterator;

    List(size_t aSize)
    {
        stack.resize(aSize);
        pos = stack.begin();
    }

    virtual ~List() {}

    bool append(int q) 
    {
        if (pos != stack.end())
        {
            stack.emplace(pos, q);
            pos++;
            if (pos == stack.end())
            {
                auto e = pos;
                e--;
                stack.erase(e);
                return true;
            }
            auto e = pos;
            pos++;
            stack.erase(e);
            pos--;
            return true;
        }
            return false;
    }

    ListIterator* createIterator(Iterators its, const int aStep) const;
};

class ListIterator
{
protected:
    friend class List;
    const List* pList;
    list <int>::iterator hd;
    virtual int currentItem()
    {
        return *(hd);
    }
    virtual bool first() = 0;
    virtual bool next() = 0;
public:
    ListIterator(const List* aPList) : pList(aPList), hd(pList->pos)
    {
        if (pList->pos != pList->stack.begin())
            hd--;
        else
            throw exception("Список пуст!");
    }
    bool operator++()
    {
        return next();
    }
    int operator*()
    {
        return first();
        }
    bool operator()()
    {
        return currentItem();
    }
};

class ListIteratorStep : public ListIterator
{   
private:
    int step;

    bool first() override 
    {
        hd = pList->pos;
        hd--;
        int i = 0;

        while (i < step)
        {
            if (hd == pList->stack.begin())
                return false;
            hd--;
            i++;
        }
        return true;
    }
    bool next() override
    {
        if (hd != pList->stack.begin())
        {
            hd--;
            int i = 0;

            while (i < step)
            {
                if (hd == pList->stack.begin())
                    return false;
                hd--;
                i++;
            }
            return true;
        }
            return false;
        
    }
public:
    ListIteratorStep(const List* aPList, int aStep = 1) : ListIterator(aPList)
    {
        if (aStep <= 0)
            throw exception("Неправильный шаг!");
        step = --aStep;
    }
};

class ListIteratorValue : public ListIterator
{
private:
    int value;

    bool first() override
    {
        hd = pList->pos;
        hd--;
        while (*hd != value)
        {
            if (hd == pList->stack.begin())
                return false;
            hd--;
        }
        return true;
    }
    bool next() override
    {
        if (hd != pList->stack.begin())
        {
         hd--;
         while (*hd != value)
        {
            if (hd == pList->stack.begin())
                return false;
            hd--;
        }
         return true;
        }
        return false;
    }    
 
public:
    ListIteratorValue(const List* aPList, int aValue) : ListIterator(aPList)
    {
        value = aValue;
    }
};

ListIterator* List::createIterator(Iterators its, const int aStep) const 
{
    if (its == Iterators::STEP)
        return new ListIteratorStep(this, aStep);
    if (its == Iterators::VALUE)
        return new ListIteratorValue(this, aStep);
    return nullptr;
}