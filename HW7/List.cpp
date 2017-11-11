#include "List.h"

template<typename T>
List<T>::List() {init();}

template<typename T>
List<T>::~List() {
	clear();
    delete head;
	delete tail;
}

template<typename T>
List<T>::List(const List<T>& rhs) {
    init();
    for(auto itr = rhs.begin(); itr != rhs.end(); ++itr) {
        push_back(*itr);
    }
}

template<typename T>
const List<T>& List<T>::operator=(const List<T>& rhs) {
    if(this != &rhs){
        clear();
        for(auto itr = rhs.begin(); itr != rhs.end(); ++itr){
            push_back(*itr);
        }
    }
    return *this;
}

template<typename T>
List<T>::List(typename List<T>::const_iterator start, typename List<T>::const_iterator end) {
	init();
    for(auto itr = start; itr != end; ++itr) {
        push_back(*itr);
    }
}

template<typename T>
List<T>::List(typename std::initializer_list<T> iList) {
    init();
    for(auto itr = iList.begin(); itr != iList.end(); ++itr) {
        push_back(*itr);
    }
}

template<typename T>
List<T>& List<T>::operator=(typename std::initializer_list<T> iList) {
    init();
    for(auto itr = iList.begin(); itr != iList.end(); ++itr) {
        push_back(*itr);
    }
    return *this;
}

template<typename T>
int List<T>::size() const {
	return theSize;
}

template<typename T>
bool List<T>::empty() const {
	return size() == 0;
}

template<typename T>
void List<T>::clear() {
    while(!empty()) {
		pop_back();
	}
}

template<typename T>
T & List<T>::front() {
    return *begin();
}

template<typename T>
const T & List<T>::front() const {
    return *begin();
}

template<typename T>
T & List<T>::back() {
    return *(--end());
}

template<typename T>
const T & List<T>::back() const {
    return *(--end());
}

template<typename T>
void List<T>::push_front(const T & val) {
    insert(begin(), val);
}

template<typename T>
void List<T>::push_back(const T & val) {
    insert(end(), val);
}

template<typename T>
void List<T>::pop_front() {
    erase(begin());
}

template<typename T>
void List<T>::pop_back() {
    erase(--end());
}

template<typename T>
void List<T>::print(std::ostream & os, char delim) const {
    for(auto itr = begin(); itr != end(); ++itr) {
        os << *itr << delim;
    }
}

template<typename T>
typename List<T>::iterator List<T>::begin() {
    typename List<T>::iterator itr{head->next};
    return itr;
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const {
        typename List<T>::const_iterator const_itr{head->next};
        return const_itr;
}

template<typename T>
typename List<T>::iterator List<T>::end() {
    typename List<T>::iterator itr{tail};
	return itr;
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const {
    typename List<T>::const_iterator const_itr{tail};
	return const_itr;
}

template<typename T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator itr, const T & val) {
    try {
        auto* p = itr.current;
        theSize++;
        auto* nptr = new List<T>::Node{val, p->prev, p};
        p->prev->next = nptr;
        p->prev = nptr;
        typename List<T>::iterator iter{nptr};
        return iter;
    }
    catch (const std::bad_alloc& bA) {
        std::cerr << "Error occured during the insert() function\n";
        std::cerr << bA.what() << std::endl;
        throw;
    }
    catch (...) {
        throw;
    }
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator itr) {
    auto* p = itr.current;
    typename List<T>::iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator start, typename List<T>::iterator end) {
    for(auto itr = start; itr != end;) {
        itr = erase(itr);
    }
	return end;
}

template<typename T>
void List<T>::init() {
    try {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
    catch (const std::bad_alloc& bA) {
        delete head;
        std::cerr << "Error occured during the init() function\n";
        std::cerr << bA.what() << std::endl;
        throw;
    }
    catch (...) {
        throw;
    }
}

template<typename T>
bool operator==(const List<T> & lhs, const List<T> & rhs) {
	bool flag = true;
    if(lhs.size() == rhs.size()) {
		auto rhs_itr = rhs.begin();
        for(auto lhs_itr = lhs.begin(); lhs_itr !=lhs.end(); ++lhs_itr) {
            if(*lhs_itr != *rhs_itr) {
                flag = false; break;
           }
			++rhs_itr;
		}
		return flag;
    } else {
		return false;
    }
}

template<typename T>
bool operator!=(const List<T> & lhs, const List<T> & rhs) {
    return !(lhs == rhs);
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const List<T> & lst) {
    lst.print(os);
	return os;
}

template<typename T>
typename List<T>::iterator List<T>::find(const T & val) {
    auto itr = begin();
    while(itr != end()) {
        if(*itr == val) {
            return itr;
        }
        ++itr;
    }
    return itr;
}

template <typename T>
void List<T>::sort(bool (*yourCmp)(const T &, const T &)) {
    for (auto i = begin(); i != end(); i++) {
        for (auto j = begin(); j != i; j++) {
            if (yourCmp(*i, *j)) {
                auto tmp = *i;
                *i = *j;
                *j = tmp;
            }
        }
    }
}

template<typename T>
List<T> List<T>::operator+(const List<T> & rhs) {
    List<T> lhs(*this);
    for(auto rhs_itr = rhs.begin(); rhs_itr !=rhs.end(); ++rhs_itr) {
        lhs.push_back(*rhs_itr);
    }
    return lhs;
}

template<typename T>
List<T> List<T>::operator-(const List<T> & rhs) {
    List<T> lhs(*this);
    for(auto rhs_itr = rhs.begin(); rhs_itr !=rhs.end(); ++rhs_itr) {
        auto f_itr =  lhs.find(*rhs_itr);
        if (f_itr != lhs.end()) {
            lhs.erase(f_itr);
        }
    }
    return lhs;
}

template<typename T>
List<T> & List<T>::operator+=(const List<T> & rhs) {
    for(auto rhs_itr = rhs.begin(); rhs_itr !=rhs.end(); ++rhs_itr) {
        (*this).push_back(*rhs_itr);
    }
    return *this;
}

template<typename T>
List<T> & List<T>::operator-=(const List<T> & rhs) {
    for(auto rhs_itr = rhs.begin(); rhs_itr !=rhs.end(); ++rhs_itr) {
        auto f_itr =  (*this).find(*rhs_itr);
        if (f_itr != (*this).end()) {
            (*this).erase(f_itr);
        }
    }
    return *this;
}

template<typename T>
bool ascending_cmp(const T & a, const T & b) {
    return a < b;
}

template<typename T>
bool descending_cmp(const T & a, const T & b) {
    return a > b;
}