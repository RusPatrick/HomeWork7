#ifndef LIST
#define LIST

#include <iostream>
#include <exception>
#include <algorithm>

template <typename T>
class List {
    private:
        struct Node {
            T data;
            Node* prev;
            Node* next;

            Node(const T & d = T{}, Node* p = nullptr, Node* n = nullptr)
                : data(d), prev(p), next(n) {}
        };
    public:
        class const_iterator {
            public:
                const_iterator();
                const T & operator*() const;

                const_iterator & operator++();
                const_iterator operator++(int);
                const_iterator & operator--();
                const_iterator operator--(int);

                bool operator==(const const_iterator & rhs) const;
                bool operator!=(const const_iterator & rhs) const;
            protected:
                Node* current;
                const_iterator(Node* p);
                friend class List<T>;
        };
        class iterator : public const_iterator {
            public:
                iterator();
                T & operator*();

                iterator & operator++();
                iterator operator++(int);
                iterator & operator--();
                iterator operator--(int);
            protected:
                iterator(Node* p);
                friend class List<T>;
        };
    public:
        List();
        ~List();
        List(const List & rhs);
        const List & operator=(const List & rhs);
        List(const_iterator start, const_iterator end);
        List(std::initializer_list<T> iList);
        List & operator=(std::initializer_list<T> iList);

        int size() const;
        bool empty() const;
        void clear();

        T & front();
        const T & front() const;
        T & back();
        const T & back() const;

        void push_front(const T & val);
        void push_back(const T & val);
        void pop_front();
        void pop_back();

        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        iterator insert(iterator itr, const T & val);
        iterator erase(iterator itr);
        iterator erase(iterator start, iterator end);

        void print(std::ostream & os, char delim = ' ') const;

        iterator find(const T & val);

        void sort(bool (*yourCmp)(const T &, const T &));

        List<T> operator+(const List<T> & rhs);
        List<T> operator-(const List<T> & rhs) ;
        List<T> & operator+=(const List<T> & rhs);
        List<T> & operator-=(const List<T> & rhs);
	private:
        int theSize;
        Node* head;
        Node* tail;
        void init();
};

template<typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs);

template<typename T>
bool operator!=(const List<T> & lhs, const List<T> & rhs);

template<typename T>
std::ostream & operator<<(std::ostream & os, const List<T> & lst);

struct MyStruct {
    int key;
    std::string stringValue;
    MyStruct(int k = 0, const std::string& s = "") : key(k), stringValue(s) {}
};

template<typename T>
bool ascending_cmp(const T & a, const T & b);

template<typename T>
bool descending_cmp(const T & a, const T & b);

#endif
