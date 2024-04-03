/**
\file atomic_operations.hpp
\brief �++ ��������� ��������
������������� ������������ ����������� ��� atomic_count_type ��� ������ � ���������� ���������.
� ������ ������������� ������� ���� �� Unix �� ������������� ������ ���������
���� ������� � ������������ ���������� ��� ������ � ���������� ����������. �������� ��������.
�.�.:
1)��� 64 bit ������ Unix/Linux ����������� ����������� ��� �������� ������������� ������
  ��� 64 bit ������ (long).
2)��� 32 bit ������ Unix/Linux ����������� ����������� ��� �������� ������������� ������
  ��� 32 bit ������ (long).
3)��� Windows ������������� �������������� ������ �� ��������. ��������� ������ 32 � 64 bit.

� ��������� �������� ������������� ���������� ����������� �� void* ������. ��� �������������
������������� ������ �������� ������ ������������ BUS_ERROR, ������� �������� � ����������
���������� ����������. � ������ ������� (_DEBUG) ��� ��������������� � ������� assert.
*/
#pragma once

#include "platform.h"

#ifdef _WIN32
#pragma warning (push)
#pragma warning (disable:4311)
#pragma warning (disable:4312)
#include <intrin.h>
#endif

#include <cassert>

namespace common_api { namespace atomic
{
#ifdef _WIN32

#ifndef _WIN64
  typedef LONG atomic_count_type;
#else
  typedef __int64 atomic_count_type;
#endif

#else

  typedef long atomic_count_type;

#endif

#ifdef _WIN32

template <int ArgSize>
  struct ChooseType
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      //static_assert(false, "Unsipported");
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      //static_assert(false, "Unsipported");
    }
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      //static_assert(false, "Unsipported");
    }
  };

template <>
  struct ChooseType<4>
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      return (D)_InterlockedExchangeAdd((LONG volatile *)&destination, (LONG)increment);
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      return (D)_InterlockedCompareExchange((LONG volatile *)&destination, (LONG)exchange, (LONG)comparand);
    }
#ifndef _WIN64
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      static_assert(sizeof(C*) == 4, "Type unsupported");
      static_assert(sizeof(E*) == 4, "Type unsupported");
      assert(  (((LONG) destination) & 3) == 0 ) ;
      return((D*)(LONG_PTR)_InterlockedCompareExchange((LONG volatile *)&destination, (LONG)(LONG_PTR)exchange, (LONG)(LONG_PTR)comparand));
    }
#endif
  };

  template <>
  struct ChooseType<8>
  {
    template <class D, class I>
    inline static D atomic_exchange_add(volatile D& destination, I increment)
    {
      return (D)_InterlockedExchangeAdd64((__int64 volatile *)&destination, (__int64)increment);
    }
    template <class D, class C, class E>
    inline static D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
    {
      return (D)_InterlockedCompareExchange64((__int64 volatile *)&destination, (__int64)exchange, (__int64)comparand);
    }
#ifdef _WIN64
    template <class D, class C, class E>
    inline static D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
    {
      static_assert(sizeof(C*) == 8, "Type unsupported");
      static_assert(sizeof(E*) == 8, "Type unsupported");
      assert(  (((__int64) destination) & 7) == 0 ) ;
      return((D*)(LONG_PTR)_InterlockedCompareExchange64((__int64 volatile *)&destination, (__int64)(__int64*)exchange, (__int64)(__int64*)comparand));
    }
#endif
  };
#endif

  template <class D, class I>
  inline D atomic_exchange_add(volatile D& destination, I increment)
  {
#ifndef _WIN32

    return __sync_fetch_and_add(&destination, increment);

#else
    return ChooseType<sizeof(D)>::atomic_exchange_add(destination,increment);

#endif
  }

  template <class D>
  inline D atomic_get(const volatile D& destination)
  {
    return atomic_exchange_add<D>(const_cast<D&>(destination), 0);
  }

  template <class D>
  inline D atomic_inc(volatile D& destination)
  {
    return atomic_exchange_add<D>(destination, 1);
  }

  template <class D>
  inline D atomic_dec(volatile D& destination)
  {
    return atomic_exchange_add<D>(destination, -1);
  }

  template <class D, class C, class E>
  inline D atomic_compare_and_swap(volatile D& destination, C comparand, E exchange)
  {
#ifndef _WIN32

    return __sync_val_compare_and_swap(&destination, comparand, exchange);

#else

    return ChooseType<sizeof(D)>::atomic_compare_and_swap(destination, comparand, exchange);

#endif
  }

  template <class D, class C, class E>
  inline D *atomic_compare_and_swap(D * volatile &destination, C *comparand, E *exchange)
  {
#ifdef _WIN32

    return ChooseType<sizeof(D*)>::atomic_compare_and_swap(destination, comparand, exchange);

#else

#if LONG_MAX == LLONG_MAX

    // 64 bit
    assert(  (((long) destination) & 7) == 0 ) ;

#else

    // 32 bit
    assert(  (((long) destination) & 3) == 0 ) ;

#endif

    return __sync_val_compare_and_swap(&destination, comparand, exchange);

#endif
  }

  template <class D, class E>
  inline D atomic_exchange(volatile D& destination, E exchange)
  {
    D pv;

    do
    {
      pv = destination;
    } while (pv != atomic_compare_and_swap(destination, pv, exchange));
    
    return pv;
  }

  template <class D, class E>
  inline D atomic_set(volatile D& destination, E exchange)
  {
    return atomic_exchange<D, E>(destination, exchange);
  }

#ifdef _WIN32

  template <class D, class E>
  inline D *atomic_set(D * volatile &destination, E *exchange)
  {
    D *pv;

    do
    {
      pv = destination;
    } while (pv != atomic_compare_and_swap(destination, pv, exchange));
    
    return pv;
  }

#endif

  struct scoped_counter
  {
    volatile atomic_count_type& _v;
    scoped_counter(volatile atomic_count_type& v)
      : _v(v)
    {
      atomic_inc(_v);
    }
    ~scoped_counter()
    {
      atomic_dec(_v);
    }
  };
} }

#ifdef _WIN32
#pragma warning (pop)
#endif
