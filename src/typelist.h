#pragma once

struct TypeListEnd {};

template< typename HEAD, typename TAIL >
struct TypeListCons
{
	typedef HEAD Head;
	typedef TAIL Tail;
};

template <typename TYPELIST, unsigned int IDX>
struct TypeListTypeByIdx
{
	typedef typename TypeListTypeByIdx< typename TYPELIST::Tail, IDX - 1 >::Type Type;
};

template <typename TYPELIST>
struct TypeListTypeByIdx<TYPELIST, 0>
{
	typedef typename TYPELIST::Head Type;
};

template <unsigned int IDX>
struct TypeListTypeByIdx< TypeListEnd, IDX >
{
	// Shouldn't static assert throw when TypeListByIdx is instantiated for the first time?
	static_assert(IDX >= 0, "Index out of range");
};

template <typename HEAD, typename TAIL, typename KEYTYPE, unsigned int N >
struct TypeListIdxByTypeImpl
	: TypeListIdxByTypeImpl< typename TAIL::Head, typename TAIL::Tail, KEYTYPE, N + 1 >
{
};

template <typename HEAD, typename TAIL, unsigned int N >
struct TypeListIdxByTypeImpl< HEAD, TAIL, HEAD, N >
{
	enum {
		Idx = N
	};
};

template <typename TYPELIST, typename KEYTYPE >
struct TypeListIdxByType
	: TypeListIdxByTypeImpl< typename TYPELIST::Head, typename TYPELIST::Tail, KEYTYPE, 0 >
{
};

template <typename HEAD, typename TAIL, unsigned int N>
struct TypeListSizeImpl : TypeListSizeImpl< typename TAIL::Head, typename TAIL::Tail, N + 1 >
{
};

template <typename HEAD, unsigned int N>
struct TypeListSizeImpl< HEAD, TypeListEnd, N >
{
	enum {
		Size = N
	};
};

template<typename TYPELIST>
struct TypeListSize : TypeListSizeImpl< typename TYPELIST::Head, typename TYPELIST::Tail, 1 >
{
};

template<>
struct TypeListSize<TypeListEnd>
{
	enum { Size = 0 };
};

template<
	typename T1 = TypeListEnd,
	typename T2 = TypeListEnd,
	typename T3 = TypeListEnd,
	typename T4 = TypeListEnd,
	typename T5 = TypeListEnd,
	typename T6 = TypeListEnd,
	typename T7 = TypeListEnd
>
struct MakeTypeList
{
	typedef TypeListCons< T1, typename MakeTypeList< T2, T3, T4, T5, T6, T7, TypeListEnd >::TypeList > TypeList;
};

template<>
struct MakeTypeList< TypeListEnd, TypeListEnd, TypeListEnd, TypeListEnd, TypeListEnd, TypeListEnd, TypeListEnd >
{
	typedef TypeListEnd TypeList;
};


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

template<typename TYPELIST>
struct ValuesImpl;

template <typename VALUES, unsigned int IDX>
struct ValuesImplGetHelper;

template<typename TYPELIST, unsigned int IDX>
struct ValuesImplGetHelper< ValuesImpl< TYPELIST >, IDX >
{
	static
		typename TypeListTypeByIdx< TYPELIST, IDX >::Type &
		Get(ValuesImpl< TYPELIST > & values)
	{
		return ValuesImplGetHelper< ValuesImpl< typename TYPELIST::Tail >, IDX - 1 >::Get(values);
	}
};

template <typename TYPELIST>
struct ValuesImplGetHelper< ValuesImpl< TYPELIST >, 0 >
{
	static
		typename TypeListTypeByIdx< TYPELIST, 0 >::Type &
		Get(ValuesImpl< TYPELIST > & values)
	{
		return values.m_Head;
	}
};

template <typename TYPELIST>
struct ValuesImpl
	: ValuesImpl< typename TYPELIST::Tail >
{
	typedef typename TYPELIST::Head Head;
	typedef ValuesImpl< typename TYPELIST::Tail > Base;

	ValuesImpl()
		: Base()
		, m_Head()
	{
	}

	template <typename ARG>
	ValuesImpl(ARG & a1)
		: Base(a1)
		, m_Head(a1)
	{
	}

	Head m_Head;
};

template <>
struct ValuesImpl< TypeListEnd >
{

	ValuesImpl()
	{
	}

	template <typename ARG>
	ValuesImpl(ARG & )
	{
	}
};

template <unsigned int IDX, typename TypeList>
typename TypeListTypeByIdx< TypeList, IDX >::Type &
Get(ValuesImpl< TypeList > & values)
{
	return ValuesImplGetHelper< ValuesImpl< TypeList >, IDX >::Get(values);
}

template <
	typename T1 = TypeListEnd,
	typename T2 = TypeListEnd,
	typename T3 = TypeListEnd,
	typename T4 = TypeListEnd,
	typename T5 = TypeListEnd,
	typename T6 = TypeListEnd,
	typename T7 = TypeListEnd
>
struct Values
	: ValuesImpl< typename MakeTypeList< T1, T2, T3, T4, T5, T6, T7 >::TypeList >
{
	typedef typename MakeTypeList< T1, T2, T3, T4 >::TypeList TypeList;
	typedef ValuesImpl< TypeList > Base;

	Values()
		: Base()
	{
	}

	template <typename ARG>
	Values(ARG & a1)
		: Base(a1)
	{
	}


};