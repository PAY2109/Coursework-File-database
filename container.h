#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string.h>
using namespace std;

struct Elem
{
    //int data; // данные
    string name;
    string extension;
    int size;
    string path;
    Elem * next, * prev;
};

class List
{
    // Голова, хвост
    Elem * Head, * Tail;
    // Количество элементов
    int Count;

public:

    // Конструктор
    List();
    // Конструктор копирования
    List(const List&);
    // Деструктор
    ~List();

    // Получить количество
    int GetCount();
    // Получить элемент списка
    Elem* GetElem(int);

    // Удалить весь список
    void DelAll();
    // Удаление элемента, если параметр не указывается,
    // то функция его запрашивает
    void Del(int pos = 0);
    // Вставка элемента, если параметр не указывается,
    // то функция его запрашивает
    void Insert(int pos = 0);

    // Добавление в конец списка
    void AddTail(string n, string ext,int s,string pa);

    // Добавление в начало списка
    void AddHead(string n, string ext,int s,string pa);

    // Печать списка
    void Print();
    // Печать определенного элемента
    void Print(int pos);
    void InsertWithConditions(int pos, string n, string ext,int s,string pa); // Insert element by the index
    string getName(int pos); //returns name of the element
    string getExtension (int pos); //returns extension of the element
    int getSize(int pos); //returns size of the element;
    string getPath (int pos); //returns path of the element

    void setName(int pos, string newName); // sets name of the element
    void setExtension(int pos, string newExtension); // sets extension of the element
    void setSize (int pos, int newSize); // sets size of the element
    void setPath (int pos, string newPath); // sets path of the element


    List& operator = (const List&);
    // сложение двух списков (дописывание)
    List operator + (const List&);

    // сравнение по элементам
    bool operator == (const List&);
    bool operator != (const List&);
    bool operator <= (const List&);
    bool operator >= (const List&);
    bool operator < (const List&);
    bool operator > (const List&);

    // переворачивание списка
    List operator - ();
};

#endif // CONTAINER_H
