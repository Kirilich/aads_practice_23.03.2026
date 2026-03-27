#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <stdexcept>
#include <cstddef>
namespace topit {
  template < class T >
  struct Vector
  {
    Vector();
    Vector(size_t s, const T& v);
    ~Vector();

    Vector(const Vector<T>&) = delete;
    Vector<T>& operator=(const Vector<T>&) = delete;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    void push_back(const T& val); //вот это и выше тоже сделать дома

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;
   private:
    T* data_;
    size_t size_, capacity_;
    explicit Vector(size_t s);
  };
  template<class T>
  bool operator==(const Vector<T>& lhs, const Vector<T>& rhs); //написать дома
  template<class T>
  bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);
}

template < class T >
topit::Vector<T>::Vector(size_t size, const T& val):
  Vector(size) //делегируем данные
{
  for (size_t i = 0; i < size; ++i) {
    try { //они уже не нужны, потому что в начале написали vector(size) но я не буду удалять бе
      data_[i] = val;
    }
    catch (...) {
      delete[] data_;
      throw;
    }
    
  }
}

template < class T >
T& topit::Vector<T>::at(size_t id)
{
  //return const_cast<T&>(static_cast<const Vector<T>*>(this)->at(id)); //если не охота дублировать код для const
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template < class T >
const T& topit::Vector<T>::at(size_t id) const
{
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template < class T >
topit::Vector<T>::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template < class T >
topit::Vector<T>::Vector() :
  data_(nullptr),
  size_(0),
  capacity_(0)
{}
template < class T >
topit::Vector<T>::~Vector()
{
  delete[] data_;
}
template< class T >
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}
template< class T >
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}

#endif
