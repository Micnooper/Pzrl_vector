#include "Vector.h"

//! Конструктор с параметрами

Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
{
    _size = size;
    _capacity = static_cast<size_t>(size*coef);
    _data = new ValueType[_capacity];
    for (size_t i = 0; i < size; ++i)
    {
        _data[i] = rawArray[i];
    }
    _multiplicativeCoef = coef;
}

//! Конструктор копирования
//! \param other - копируемый объект

explicit Vector::Vector(const Vector& other)
{
    _size = other._size;
    _capacity = other._capacity;
    _data = new ValueType[_capacity];
    _multiplicativeCoef = other._multiplicativeCoef;

    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
}

//! Оператор присваивания копированием
//! \param other - копируемый объект

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = new ValueType[_capacity];
    _multiplicativeCoef = other._multiplicativeCoef;

    for (size_t i = 0; i < _size; ++i) 
    {
        _data[i] = other._data[i];
    }
    return *this;
}

//! Конструктор перемещения
//! \param other - перемещаемый объект

explicit Vector::Vector(Vector&& other) noexcept
{
    _size = other._size;
    _capacity = other._capacity;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
    other._multiplicativeCoef = 0;
}

//! Оператор присваивания перемещением
//! \param other - перемещаемый объект

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other)
        return *this;
    delete[] _data;

    _size = other._size;
    _capacity = other._capacity;
    _data = other._data;
    _multiplicativeCoef = other._multiplicativeCoef;

    other._size = 0;
    other._capacity = 0;
    other._data = nullptr;
    other._multiplicativeCoef = 0;

    return *this;
}

//! Деструктор
Vector::~Vector()
{
    delete[] _data;
}

//! Количество элементов
size_t Vector::size() const
{
    return _size;
}

//! Максимальное количество элементов
size_t Vector::capacity() const
{
    return _capacity;
}

//! Фактор загруженности
double Vector::loadFactor() const
{
    if (_capacity == 0)
    {
        return 0;
    }
    return static_cast<double>(_size) / _capacity;
}

//! Доступ к элементу по индексу

ValueType& Vector::operator[](size_t idx)
{
    return _data[idx];
}

//! Доступ к элементу по индексу

const ValueType& Vector::operator[](size_t idx) const
{
    return _data[idx];
}

//! Поиск первого вхождения значения
//! \return - индекс элемента

long long Vector::find(const ValueType& value) const
{
    for (size_t i = 0; i < _size; ++i)
    {
        if (_data[i] == value)
        {
            return static_cast<long long>(i);
        }
    }
    return -1;
}
    
//! Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
void Vector::reserve(size_t capacity)
{
    if (!_data)
    {
        _data = new ValueType[capacity];
        _capacity = capacity;
        return;
    }

    if (capacity > _capacity) 
    {
        ValueType* _data1 = new ValueType[capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            _data1[i] = _data[i];
        }
        delete[] _data;
        _data = _data1;
        _capacity = capacity;
    }
}


//! Уменьшить capacity до size
void Vector::shrinkToFit()
{
    _capacity = _size;

    if (!_data)
    {
        _data = new ValueType[_capacity];
        return;
    }

    ValueType* _data1 = new ValueType[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        _data1[i] = _data[i];
    }
    delete[] _data;
    _data = _data1;
}

//! Вставка в конец

void Vector::pushBack(const ValueType& value)
{
    if (!_data)
    {
        _data = new ValueType[static_cast<size_t>(_multiplicativeCoef)];
        _capacity = static_cast<size_t>(_multiplicativeCoef);
    }

    if (_capacity == _size) 
    {
        ValueType* _data1 = new ValueType[static_cast<size_t>(_capacity*_multiplicativeCoef)];
        for (size_t i = 0; i < _size; ++i)
        {
            _data1[i] = _data[i];
        }
        delete[] _data;
        _data = _data1;
        _capacity = static_cast<size_t>(_capacity*_multiplicativeCoef);
    }

    _data[_size] = value;
    _size++;
}

//! Вставка в начало

void Vector::pushFront(const ValueType& value)
{
    if (!_data)
    {
        _data = new ValueType[static_cast<size_t>(_multiplicativeCoef)];
        _capacity = static_cast<size_t>(_multiplicativeCoef);
    }

    if (_capacity == _size) 
    {
        ValueType* _data1 = new ValueType[static_cast<size_t>(_capacity*_multiplicativeCoef)];
        for (size_t i = 0; i < _size; ++i)
        {
            _data1[i] = _data[i];
        }
        delete[] _data;
        _data = _data1;
        _capacity = static_cast<size_t>(_capacity*_multiplicativeCoef);
    }

    for (size_t i = _size; i > 0; --i)
    {
        _data[i] = _data[i-1];
    }

    _data[0] = value;
    _size++;
}

//! Вставка элемента value в позицию pos

void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "pos > _size" << std::endl;
        return;
    }

    if (!_data)
    {
        _data = new ValueType[static_cast<size_t>(_multiplicativeCoef)];
        _capacity = static_cast<size_t>(_multiplicativeCoef);
    }

    if (_capacity == _size) 
    {
        ValueType* _data1 = new ValueType[static_cast<size_t>(_capacity*_multiplicativeCoef)];
        for (size_t i = 0; i < _size; ++i)
        {
            _data1[i] = _data[i];
        }
        delete[] _data;
        _data = _data1;
        _capacity = static_cast<size_t>(_capacity*_multiplicativeCoef);
    }

    for (size_t i = _size; i > pos; --i)
    {
        _data[i] = _data[i-1];
    }

    _data[pos] = value;
    _size++;
}

//! Вставка массива элементов типа ValueType в позицию pos

void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (pos > _size)
    {
        return;
    }
    if (!_data)
    {
        _data = new ValueType[static_cast<size_t>(size*_multiplicativeCoef)];
        _capacity = static_cast<size_t>(size*_multiplicativeCoef);
        for (size_t i = 0; i < size; ++i)
        {
            _data[i] = values[i];
        }
        _size = size;
        return;
    }

    if (_capacity <= _size + size) 
    {
        ValueType* _data1 = new ValueType[static_cast<size_t>((_capacity + size) * _multiplicativeCoef)];
        for (size_t i = 0; i < pos; ++i)
        {
            _data1[i] = _data[i];
        }
        for (size_t i = pos, j = 0; i < size+pos && j < size; ++i, ++j)
        {
            _data1[i] = values[j];
        }
        if (pos < _size)
        {
            for (size_t i = size + pos, j = pos; i < _size+size && j < _size; ++i, ++j)
            {
                _data1[i] = _data[j];
            }
        }
        delete[] _data;
        _data = _data1;
        _capacity = static_cast<size_t>((_capacity + size) * _multiplicativeCoef);
        _size = _size + size;
    }
    else
    {
        for (size_t i = _size; i > pos; --i)
        {
            _data[i + size - 1] = _data[i - 1];
        }
        for (size_t i = 0; i < size; ++i)
        {
            _data[pos + i] = values[i];
        }
        _size = _size + size;
    }
}

//! Вставка содержимого вектора в позицию pos

void Vector::insert(const Vector& vector, size_t pos)
{
    if (pos > _size)
    {
        return;
    }
    if (!_data)
    {
        _data = new ValueType[static_cast<size_t>(vector.size()*_multiplicativeCoef)];
        _capacity = static_cast<size_t>(vector.size()*_multiplicativeCoef);
        for (size_t i = 0; i < vector.size(); ++i)
        {
            _data[i] = vector[i];
        }
        _size = vector.size();
        return;
    }

    if (_capacity <= _size + vector.size()) 
    {
        ValueType* _data1 = new ValueType[static_cast<size_t>((_capacity + vector.size()) * _multiplicativeCoef)];
        for (size_t i = 0; i < pos; ++i)
        {
            _data1[i] = _data[i];
        }
        for (size_t i = pos, j = 0; i < vector.size() + pos && j < vector.size(); ++i, ++j)
        {
            _data1[i] = vector[j];
        }
        if (pos < _size)
        {
            for (size_t i = vector.size() + pos, j = pos; i < _size + vector.size() && j < _size; ++i, ++j)
            {
                _data1[i] = _data[j];
            }
        }
        delete[] _data;
        _data = _data1;
        _capacity = static_cast<size_t>((_capacity + vector.size()) * _multiplicativeCoef);
        _size = _size + vector.size();
    }
    else
    {
        for (size_t i = _size; i > pos; --i)
        {
            _data[i + vector.size() - 1] = _data[i - 1];
        }
        for (size_t i = 0; i < vector.size(); ++i)
        {
            _data[pos + i] = vector[i];
        }
        _size = _size + vector.size();
    }
}

//! Удаление с конца
void Vector::popBack()
{
    if (_size == 0)
    {
        return;
    }

    _size--;
}

//! Удаление из начала
void Vector::popFront()
{
    if (_size == 0) 
    {
        return;
    }

    for (size_t i = 0; i < _size - 1; ++i)
    {
        _data[i] = _data[i + 1];
    }
    _size--;
}

/*!
    \brief Удалить элемент(ы) из вектора
    \param pos: позиция начала удаляемого участка
    \param count: количество удаляемых элементов
    если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
*/
void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size || count == 0)
    {
        return;
    }
    if (pos + count > _size)
    {
        _size = pos; 
    }
    else 
    {
        for (size_t i = pos; i < _size - count; ++i)
        {
            _data[i] = _data[i+count];
        }
        _size -= count;
    }
}

/*!
    \brief Удалить элемент(ы) из вектора
    \param beginPos: позиция начала удаляемого участка
    \param endPos: позиция окончания удаляемого участка
    Все элементы интервала [beginPos, endPos) должны быть удалены:
    [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
    если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
*/
void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (beginPos >= _size || endPos < beginPos)
    {
        return;
    }
    if (endPos > _size)
    {
        _size = beginPos; 
    }
    else 
    {
        for (size_t i = beginPos; i < _size - (endPos - beginPos); ++i)
        {
            _data[i] = _data[i + (endPos - beginPos)];
        }
        _size -= endPos - beginPos;
    }
}

//! Класс, реализующий итератор

explicit Vector::Iterator::Iterator(ValueType* ptr)
{
    _ptr = ptr;
}

ValueType& Vector::Iterator::operator*()
{
    return *_ptr;
}

const ValueType& Vector::Iterator::operator*() const
{
    return *_ptr;
}

ValueType* Vector::Iterator::operator->()
{
    return _ptr;
}

const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    ++ _ptr;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator ptr = *this;
    ++ _ptr;
    return ptr;
}

bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
}

//! Получить итератор на начало вектора
Vector::Iterator Vector::begin()
{
    return Iterator(_data);
}

//! Получить итератор на элемент вектора, следующий за последним
Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
}