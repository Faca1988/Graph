#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

template<class Type>
class List
{
private:
    vector<Type> lista;
    int _size;
public:
    List();
    void Insert(Type item);
    void InsertAtTheTop(Type item);
    void ModifyItem(int pos, Type newElement);
    int GetSize();
    bool ItsEmpty();
    bool ItsFull();
    List<Type>* GetList();
    Type GetItem(int pos);
    int GetItemPos(Type item);
    void EraseItem(int pos);
};
template<class Type>
List<Type>::List()
{
    _size = 0;
};

template<class Type>
void List<Type>::Insert(Type item)
{
    _size ++;
    lista.push_back(item);
};

template<class Type>
void List<Type>::InsertAtTheTop(Type item)
{
    _size ++;
    lista.insert( lista.begin(), item );
};

template<class Type>
void List<Type>::ModifyItem(int pos, Type newItem)
{
    lista[pos] = newItem;
};

template<class Type>
bool List<Type>::ItsEmpty()
{
    return ( (int)lista.size() == 0);
};

template<class Type>
bool List<Type>::ItsFull()
{
    return ( (int) lista.max_size() >= _size );
};

template<class Type>
List<Type>* List<Type>::GetList()
{
    return this->lista;
};

template<class Type>
Type List<Type>::GetItem(int pos)
{
    Type aux;
    if ( _size > 0 )
    {
        aux = lista[pos];
    }
    return aux;
};

template<class Type>
int List<Type>::GetSize()
{
    return _size;
};

template<class Type>
int List<Type>::GetItemPos(Type item)
{
    int targetPos;
    for (int idx = 0; idx < _size; idx++)
    {
        if ( lista[idx] == item )
        {
           targetPos = idx;
        };
    };

    return targetPos;
}

template<class Type>
void List<Type>::EraseItem(int pos)
{
    if ( !ItsEmpty() )
    {
        lista.erase( lista.begin() + pos );
        _size--;
    };
};
#endif // LIST_H_INCLUDED
