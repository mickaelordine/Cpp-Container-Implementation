#pragma once

#include <assert.h>
#include <utility>
#include <new>    
#include <cassert>

// blank struct to represent no value
struct NullOpt {};

template<typename T>
class Optional
{
public:
    constexpr Optional() noexcept : _hasValue(false) {}
    constexpr Optional(NullOpt) noexcept : _hasValue(false) {}

    Optional(const T& value) : _hasValue(true) {
        new (&_value) T(value); // Costruisce T nello spazio della union
    }

    Optional(T&& value) : _hasValue(true) {
        new (&_value) T(std::move(value));
    }
    
    Optional(const Optional& other) : _hasValue(other._hasValue) {
        if (_hasValue) new (&_value) T(other._value);
    }
    
    ~Optional() {
        reset();
    }
    
    Optional& operator=(NullOpt) noexcept {
        reset();
        return *this;
    }

    Optional& operator=(const Optional& other) {
        if (this != &other) {
            reset();
            if (other._hasValue) {
                new (&_value) T(other._value);
                _hasValue = true;
            }
        }
        return *this;
    }

    Optional& operator=(Optional&& other) noexcept {
        if (this != &other) {
            reset();
            if (other._hasValue) {
                new (&_value) T(std::move(other._value));
                _hasValue = true;
                other.reset(); 
            }
        }
        return *this;
    }
    
    void reset() noexcept {
        if (_hasValue) {
            _value.~T(); 
            _hasValue = false;
        }
    }

    constexpr const T& GetValue()
    {
        // bring UB if no value is set
        return _value;
    }


    constexpr const bool IsSet()
    {
        return _hasValue;
    }
    
    constexpr explicit operator bool() const noexcept { return _hasValue; }
    constexpr bool has_value() const noexcept { return _hasValue; }
    
    // C++23
    template<class F> constexpr auto and_then(F&&) &{}

    template<class F> constexpr auto transform(F&&) &{}

    // template<class F> constexpr Optional or_else(F&&) const&{}
    // template<class F> constexpr Optional or_else(F&&) &&{}
    
    
    T* operator->() noexcept {
        assert(_hasValue);
        return &_value;
    }

    const T* operator->() const noexcept {
        assert(_hasValue);
        return &_value;
    }
    
    T& operator*() & {
        assert(_hasValue);
        return _value;
    }

    const T& operator*() const& {
        assert(_hasValue);
        return _value;
    }

    T& value() {
        if (!_hasValue) throw std::bad_alloc(); 
        return _value;
    }

private:
    bool _hasValue;
    union {
        T _value; 
    };
};