#include <iostream>

template <class Item>
class List {
public:
    List(long size =  DEFAULT_LIST_CAPACITY);
    long Count() const;
    Item& Get(long index) const;
    // ...
};

template <class Item>
class Iterator {
public:
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() const = 0;
    virtual Item CurrentItem() const = 0;
protected:
    Iterator();
};

template <class Item>
class ListIterator : public Iterator<Item> {
public:
    ListIterator(const List<Item>* aList)  : _list(aList), _current(0) { }
    virtual void First() {
        _current = 0;
    }
    virtual void Next() {
        _current++;
    }
    virtual bool IsDone() const {
        return _current >= _list->Count();
    }
    virtual Item CurrentItem() const {
        if (IsDone()) {
            throw IteratorOutofBounds;
        }
        return _list->Get(_current);
    }
private:
    const List<Item>* _list;
    long _current;
};

template <class Item>
class IteratorPtr {
public:
    IteratorPtr(Iterator<Item>* i)  : _i(i) { }
    ~IteratorPtr() { delete _i; }

    Iterator<Item>* operator->() { return _i; }
    Iterator<Item>& operator*() { return  *_i; }
private:
    // Запрет копирования и присваивания
    IteratorPtr(const IteratorPtr&);
    IteratorPtr& operator=(const IteratorPtr&);
private:
    Iterator<Item>* _i;
};

int main(){
    List<Employee*>* employees;
    ListIterator<Employee*> i(employees);
    for (i.First(); !i.IsDone(); i.Next()) {
        i.CurrentItem()->Print();
    }

    return 0;
}
