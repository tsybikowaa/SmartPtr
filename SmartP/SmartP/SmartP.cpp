// SmartP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <memory>
#include <iostream>
using namespace std;

//using auto_cleanup = unique_ptr<T, function<void(T*)>>; //уникальный

class Ptr
{
private:
    int d;

public:
    // Конструктор
    Ptr(int _d) : d(_d) { }

    // Методы доступа
    int Get() { return d; }
    void Set(int _d)
    {
        d = _d;
    }

    void Print(string msg)
    {
        cout << msg.c_str() << d << endl;
    }
};

// Класс умного указателя на обобщенный тип T
template <typename T>

class SmartPtr
{
private:
    T* p; // указатель на обобщенный тип T
    int count; // количество копий

public:
 
    SmartPtr(T* _p = nullptr) //кон
    {
        count = 0;
        p = _p;
    }

    SmartPtr(const SmartPtr& obj) //кон коп
    {

        p = obj.p;
        count++;
    }

    // Оператор копирования
    SmartPtr operator=(const SmartPtr& obj)
    {
        p = obj.p;
        count++;
        return *this;
    }

    // Деструктор - уничтожает объект-оригинал
    ~SmartPtr()
    {
        // Если есть объект и нету копий,то просто уничтожаем это объект.
        if ((p != nullptr) && (count == 0))
        {
            cout << "Delete object" << endl;
            delete[] p;
        }
        else
        {
            // иначе, просто уничтожается копия
            cout << "Delete copy" << endl;
            count--; // уменьшить счетчик копий
        }
    }


    T& operator*()
    {
        return *p;
    }
    T* operator->()
    {
        return p;
    }
  
    T& operator[](unsigned int index)
    {
        return p[index];
    }
};
int main()
{
    try {
        
        Ptr* obj1 = new Ptr(1);
        obj1->Print("obj1: ");

        auto_ptr<int> ap1(new int(5));
        auto_ptr<int> ap2(ap1);

        // Инициализировать умный указатель
        SmartPtr<Ptr> ptr(obj1);
        ptr->Print("ptr->obj: ");

        SmartPtr<Ptr> ptr2 = ptr; 
        ptr2->Print("ptr2->obj: ");

        SmartPtr<Ptr> ptr3;
        ptr3 = ptr2;
        ptr3->Print("ptr3->obj: ");
    
    }
    catch (int ff) {
        cout << "error: " << ff <<endl;
    }
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
