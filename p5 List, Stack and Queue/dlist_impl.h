#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H
#include <iostream>
#include "dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const
{
    if (first==nullptr) return 1;
    else return 0;
}

template <class T>
void Dlist<T>::insertFront(T *op)
{
    node* np=new node;
    np->op=op;
    np->prev=nullptr;
    np->next=nullptr;
    if (isEmpty())
    {
        first=np;
        last=np;
        return;
    }
    first->prev=np;
    np->next=first;
    first=np;
    return;
}

template <class T>
void Dlist<T>::insertBack(T* op)
{
    node* np=new node;
    np->op=op;
    np->prev=nullptr;
    np->next=nullptr;
    if (isEmpty())
    {
        first=np;
        last=np;
        return;
    }
    last->next=np;
    np->prev=last;
    last=np;
}

template <class T>
void Dlist<T>::removeAll()
{
    if (isEmpty())
        return;
    else {
        node *victim = first;
        while (victim != last) {
            victim = victim->next;
            delete victim->prev->op;
            delete victim->prev;
        }
        delete victim->op;
        delete victim;
        first=nullptr;
        last=nullptr;
    }
}


template <class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    removeAll();
    if (!isEmpty()) return;
    else 
    {
        node *np = l.first;
        if (np!=nullptr)
        {
            T *object = new T;
            (*object) = (*(np->op));
            first=new node({nullptr, nullptr, object});
            last=first;
            np=np->next;
        }
        while (np!=nullptr)
        {
            T *object = new T;
            (*object) = (*(np->op));
            last->next = new node({nullptr, last, object});
            last = last->next;
            np = np->next;
        }
    }
}

template <class T>
Dlist<T>::Dlist() : first(nullptr), last(nullptr) {}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l)
{
    first=nullptr;
    last=nullptr;
    copyAll(l);
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l)
{
    if (this!=&l) copyAll(l);
    return *this;
}

template <class T>
T *Dlist<T>::removeFront()
{
    if (isEmpty()) throw emptyList();
    if (first==last) 
    {
        T *result=first->op;
        delete first;
        first=nullptr;
        last=nullptr;
        return result;
    }
    else 
    {
        T *result=first->op;
        node* np=first;
        first=first->next;
        first->prev=nullptr;
        delete np;
        return result;
    }
}

template <class T>
T *Dlist<T>::removeBack()
{
    if (isEmpty()) throw emptyList();
    T *result = last->op;
    if (first==last)
    {
        delete last;
        first=nullptr;
        last=nullptr;
        return result;
    }
    else
    {
        node *np=last;
        last=last->prev;
        last->next=nullptr;
        delete np;
        return result;
    }
}

template <class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref)
{
    if (isEmpty())
        return nullptr;
    else if (cmp(first->op, ref))
        return removeFront();
    else if (cmp(last->op, ref))
        return removeBack();
    else if (!first->next)
        return nullptr;
    else {
        node *np= first->next;
        while (np!= last) {
            if (cmp(np->op, ref)==1) {
                T *result=np->op;
                np->next->prev=np->prev;
                np->prev->next=np->next;
                delete np;
                return result;
            }
            np=np->next;
        }
        return nullptr;
    }
}
#endif 