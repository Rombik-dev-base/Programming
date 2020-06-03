

#ifndef LABORATHORY7_CONTAINER_H
#define LABORATHORY7_CONTAINER_H
#pragma once
#include <iostream>
using namespace std;
template <class T> struct element;

template <class T>
class circular_buffer {
public:

    circular_buffer(unsigned capacity = 255)
            : capacity_(capacity)
    {
        start_ = new element<T>();
        end_ = start_;
        element<T>* cur = start_;
        for (int i = 1; i < capacity; i++) {
            cur->next = new element<T>();
            cur->next->prev = cur;
            cur = cur->next;
        }
        cur->next = new element<T>;
        cur->next->is_end = true;
        cur->next->next = start_;
        cur->next->prev = cur;
        start_->prev = cur->next;
    }

    circular_buffer(const circular_buffer<T>& other)
            : capacity_(other.capacity_)
    {
        start_ = new element<T>();

        element<T>* cur = start_;
        element<T>* other_cur = other.start_;

        bool content_end = other.end_ == other.start_;
        for (int i = 0; i < capacity_; i++) {
            if (!content_end)
                cur->value = other_cur->value;

            if (other_cur == other.end_) {
                end_ = cur;
                content_end = true;
            }
            cur->value = other_cur->value;

            cur->next = new element<T>();
            cur->next->prev = cur;

            cur = cur->next;
            other_cur = other_cur->next;
        }
        cur->next = new element<T>();
        cur->is_end = true;
        cur->next->prev = cur;
        cur->next->next = start_;
    }

    ~circular_buffer() {
        element<T>* cur = start_->next;
        while (cur != start_) {
            element<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        delete start_;
    }

    void push_back(T value) {
        if (end_->is_end) {
            start_ = start_->next;
            end_->is_end = false;
            end_->next->is_end = true;
        }

        end_ = end_->next;

        end_->prev->value = value;
    }

    T pop_back() {

        end_ = end_->prev;

        return end_->value;
    }

    void push_front(T value) {
        if (end_ == start_) {
            end_ = start_->next;
            start_->value = value;
            return;
        }
        else if (start_->prev == end_) {
            end_->is_end = false;
            end_ = end_->prev;
            end_->is_end = true;
        }

        start_->prev->is_end = false;
        start_->prev->prev->is_end = true;
        start_->prev->value = value;
        start_ = start_->prev;
    }

    T pop_front() {

        T value = start_->value;

        start_->prev->is_end = false;
        start_ = start_->next;
        start_->prev->is_end = true;

        return value;
    }

    T& front() {
        return start_->value;
    }

    T& back() {
        return end_->prev->value;
    }

    int size() {
        if (end_ == nullptr)
            return 0;
        element<T>* cur = start_;
        int size = 0;
        while (cur != end_) {
            size++;
            cur = cur->next;
        }
        return size;
    }

    unsigned capacity() {
        return capacity_;
    }

    bool empty() {
        return end_ == nullptr;
    }

    bool full() {
        return end_->is_end;
    }

    T& operator [] (unsigned idx) const {

        element<T>* cur = start_;
        for (int i = 0; i < idx; i++) {
            cur = cur->next;
        }


        return cur->value;
    };

        void resize(unsigned new_capacity) {

        if (new_capacity < capacity_) {
            for (int cur_capacity = capacity_; cur_capacity > new_capacity; cur_capacity--) {
                start_->prev->prev->prev->next = start_->prev;
                element<T>* del_el = start_->prev->prev;
                if (del_el == end_)
                    end_ = start_->prev;
                start_->prev->prev = start_->prev->prev->prev;
                delete del_el;
            }
        }
        else {
            for (int cur_capacity = capacity_; cur_capacity < new_capacity; cur_capacity++) {
                start_->prev->prev->next = new element<T>();
                start_->prev->prev->next->prev = start_->prev->prev;
                start_->prev->prev->next->next = start_->prev;
                start_->prev->prev = start_->prev->prev->next;
                if (start_->prev == end_)
                    end_ = start_->prev->prev;
            }
        }
        capacity_ = new_capacity;
    }


    friend istream& operator >> (istream& in, circular_buffer<T>& buffer) {
        T value;
        in >> value;
        buffer.push_back(value);
        return in;
    }

    friend ostream& operator << (ostream& out, circular_buffer<T>& buffer) {
        out << buffer.end_;
        return out;
    }

    void print_all() {
        if (end_ == start_) {
            cout << "Buffer is empty" << endl;
            return;
        }
        element<T> *cur = start_;
        do {
            if (!cur->is_end && cur != end_)
                cout << cur->value;

            cout << " ";
            cout.flush();
            cur = cur->next;
        } while (cur != start_);
    }
        template <class V>
        class buffer_iterator   : public iterator<random_access_iterator_tag, T> {
        public:
            buffer_iterator() = delete;

            buffer_iterator(element<T>* p) : _it(p) {}

            buffer_iterator(const buffer_iterator<T>& it) : _it(it._it) {}

            inline buffer_iterator<T>& operator ++ () {
                _it = _it->next;
                return *this;
            }

            inline buffer_iterator<T>& operator -- () {
                _it = _it->prev;
                return *this;
            }

            inline buffer_iterator<T>& operator ++ (int) {
                auto& tmp(*this);
                _it = _it->next;
                return tmp;
            }

            inline buffer_iterator<T>& operator -- (int) {
                auto& tmp(*this);
                _it = _it->prev;
                return tmp;
            }

            inline buffer_iterator<T> operator + (const int val) {
                buffer_iterator it(*this);
                it += val;
                return it;
            }

            inline buffer_iterator<T> operator - (const int val) {
                buffer_iterator it(*this);
                it -= val;
                return it;
            }

            inline buffer_iterator<T>& operator = (const T& value) {
                _it = *value;
                return *this;
            }

            inline buffer_iterator<T>& operator = (T* ptr) {
                _it = ptr;
                return *this;
            }

            inline buffer_iterator<T>& operator = (const buffer_iterator<T>& it) {
                _it = it._it;
                return *this;
            }

            inline T& operator * () const {
                return _it->value;
            }

            inline T* operator -> () const {
                return *(_it->value);
            }

            inline buffer_iterator<T>& operator += (const int& val) {
                for (int i = 0; i < val; i++)
                    _it = _it->next;
                return *this;
            }

            friend inline bool operator == (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                return it1._it == it2._it;
            }

            inline bool operator == (T* it) {
                return _it == it;
            }

            friend inline int operator - (buffer_iterator<T> it1, buffer_iterator<T> it2) {
                buffer_iterator<T> it = it1;
                int result1 = 0;
                while (!it._it->prev->is_end) {
                    it--;
                    result1++;
                }

                it = it2;
                int result2 = 0;
                while (!it._it->prev->is_end) {
                    it--;
                    result2++;
                }

                return result1 - result2;
            }
            inline buffer_iterator<T>& operator -= (const int& val) {
                for (int i = val; i > 0; i--)
                    _it = _it->prev;
                return *this;
            }

            friend inline int operator + (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                buffer_iterator<T> it = it1;
                int result1 = 0;
                while (!it.ptr_->prev->is_end) {
                    it--;
                    result1++;
                }

                it = it2;
                int result2 = 0;
                while (!it.ptr_->prev->is_end) {
                    it--;
                    result2++;
                }

                return result1 + result2;
            }

            friend inline buffer_iterator<T> operator + (const buffer_iterator<T>& it, const int& val) {
                return buffer_iterator(it + val);
            }

            friend inline buffer_iterator<T> operator - (const buffer_iterator<T>& it, const int& val) {
                return buffer_iterator(it - val);
            }

            friend inline bool operator > (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                buffer_iterator<T> it = it1;

                while (it != it2) {
                    if (it._it->is_end)
                        return true;
                    it++;
                }
                return false;
            }

            friend inline bool operator >= (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                return it1 > it2 || it1 == it2;
            }

            friend inline bool operator < (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                return it2 > it1;
            }

            friend inline bool operator <= (const buffer_iterator<T>& it1, const buffer_iterator<T>& it2) {
                return it2 > it1 || it2 == it1;
            }
            inline bool operator != (const buffer_iterator<T>& it) {
                return _it != it._it;
            }

            inline bool operator != (T* it) {
                return _it != it;
            }

        private:
            element<T>* _it;
        };
    buffer_iterator<T> begin() {
        return buffer_iterator<T>(start_);
    }

    buffer_iterator<T> end() {
        return buffer_iterator<T>(end_);
    }

    buffer_iterator<const T>  begin() const {
        return buffer_iterator<const T>(start_);
    }

    buffer_iterator<const T>  end() const {
        return buffer_iterator<const T>(end_);
    }

private:
    unsigned capacity_;

    element<T>* start_;
    element<T>* end_;
};

template <class T>
struct element {
    element* prev;
    element* next;
    T value;
    bool is_end = false;
};



#endif //LABORATHORY7_CONTAINER_H



// https://github.com/kuzznya - Гит лучшего чела в мире, совет от самого Rombik))
