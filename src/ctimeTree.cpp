#include "ctimeTree.h"

struct CoordinateSystem
{
	enum Type {
		_3DWorld,
		_2DCamera,
		_2DRightCamera,
		_3DCar
	};
};

typedef CoordinateSystem::Type CoordinateSystemType;

template< CoordinateSystemType CS >
struct CoordinateSystemDimension;

template<>
struct CoordinateSystemDimension< CoordinateSystem::_3DWorld >
{
	enum { Value = 3 };
};

template<>
struct CoordinateSystemDimension< CoordinateSystem::_2DCamera >
{
	enum { Value = 2 };
};

template<>
struct CoordinateSystemDimension< CoordinateSystem::_2DRightCamera >
{
	enum { Value = 2 };
};

template<>
struct CoordinateSystemDimension< CoordinateSystem::_3DCar >
{
	enum { Value = 3 };
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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


template<
	typename T1 = TypeListEnd,
	typename T2 = TypeListEnd,
	typename T3 = TypeListEnd,
	typename T4 = TypeListEnd
>
struct MakeTypeList
{
	typedef TypeListCons< T1, typename MakeTypeList< T2, T3, T4, TypeListEnd >::TypeList > TypeList;
};

template<>
struct MakeTypeList< TypeListEnd, TypeListEnd, TypeListEnd, TypeListEnd >
{
	typedef TypeListEnd TypeList;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//template <typename HEAD, typename TAIL>
//struct ValuesCons
//	: TAIL
//{
//	ValuesCons()
//		: TAIL()
//		, m_Head()
//	{
//	}
//
//	/*template<unsigned int IDX>
//	typename*/
//
//	HEAD m_Head;
//};

//struct 

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

	Head m_Head;
};

template <>
struct ValuesImpl< TypeListEnd >
{
};

template <
	typename T1 = TypeListEnd,
	typename T2 = TypeListEnd,
	typename T3 = TypeListEnd,
	typename T4 = TypeListEnd
>
struct Values
	: ValuesImpl< typename MakeTypeList< T1, T2, T3, T4 >::TypeList >
{
	typedef typename MakeTypeList< T1, T2, T3, T4 >::TypeList TypeList;
	typedef ValuesImpl< TypeList > Base;

	template <unsigned int IDX>
	typename TypeListTypeByIdx< TypeList, IDX >::Type &
		Get()
	{
		return ValuesImplGetHelper< Base, IDX >::Get(*this);
	}
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template<
	typename T1,
	typename T2 = TypeListEnd,
	typename T3 = TypeListEnd,
	typename T4 = TypeListEnd
>
struct Children
	: MakeTypeList< T1, T2, T3, T4 >::TypeList
{
};

template <CoordinateSystemType CS, typename CHILDREN = TypeListEnd>
struct TreeNode
{
	enum { CoordinateSystemValue = CS };
	typedef CHILDREN Children;
};



namespace TreeNodeHelper
{
	template< CoordinateSystemType CS >
	struct TaggedCoordinateSystem
	{
		enum { Value = CS };
	};

	//template<CoordinateSystemType CS, typename PATH>
	//struct ConcatPathIfNotEmpty
	//{
	//	typedef TypeListCons< TaggedCoordinateSystem< CS >, PATH > Result;
	//};

	//template<CoordinateSystemType CS>
	//struct ConcatPathIfNotEmpty< CS, TypeListEnd >
	//{
	//	typedef TypeListEnd Result;
	//};

	template <typename TREE, CoordinateSystemType DST>
	struct PathToDest;

	template< CoordinateSystemType CS, typename CHILDREN, CoordinateSystemType DST >
	struct ForAllChildren;

	template< CoordinateSystemType CS, typename HEAD, typename NEXT, typename PATH, CoordinateSystemType DST >
	struct ForAllChildrenReturnIfResult
	{
		typedef TypeListCons< TaggedCoordinateSystem< CS >, PATH > Result;
	};

	template< CoordinateSystemType CS, typename HEAD, typename NEXT, CoordinateSystemType DST >
	struct ForAllChildrenReturnIfResult< CS, HEAD, NEXT, TypeListEnd, DST >
	{
		typedef typename ForAllChildren< CS, NEXT, DST >::Result Result;
	};

	template< CoordinateSystemType CS, typename HEAD, typename NEXT, CoordinateSystemType DST >
	struct ForAllChildrenImpl : ForAllChildrenReturnIfResult< CS, HEAD, NEXT, typename PathToDest< HEAD, DST >::Result, DST >
	{
	};

	template< CoordinateSystemType CS, typename CHILDREN, CoordinateSystemType DST >
	struct ForAllChildren
		: ForAllChildrenImpl< CS, typename CHILDREN::Head, typename CHILDREN::Tail, DST >
	{
	};

	template< CoordinateSystemType CS, CoordinateSystemType DST >
	struct ForAllChildren< CS, TypeListEnd, DST >
	{
		typedef TypeListEnd Result;
	};

	template <CoordinateSystemType CS, typename CHILDREN, CoordinateSystemType DST>
	struct PathToDestImpl
	{
		typedef typename ForAllChildren< CS, CHILDREN, DST >::Result Result;
	};

	template <CoordinateSystemType DST, typename CHILDREN>
	struct PathToDestImpl< DST, CHILDREN, DST >
	{
		typedef TypeListCons< TaggedCoordinateSystem< DST >, TypeListEnd > Result;
	};

	template <CoordinateSystemType CS, typename CHILDREN, CoordinateSystemType DST>
	struct PathToDest< TreeNode< CS, CHILDREN >, DST >
	{
		typedef typename PathToDestImpl< CS, CHILDREN, DST >::Result Result;
	};

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void ctimeTreeRun()
{
	typedef
		TreeNode<
		CoordinateSystem::_2DCamera,
		Children<
		TreeNode< CoordinateSystem::_2DRightCamera >,
		TreeNode<
		CoordinateSystem::_3DCar,
		Children< TreeNode< CoordinateSystem::_3DWorld > >
		>
		>
		> TreeType;

	//tree.Edge< CoordinateSystem::CoordinateSystem3DWorld >();

	Values< int, double, float, char > values;

	float & f = values.Get< 2 >();
	f = 3.5f;

	//values.Get< 0 >();

	typedef TreeNodeHelper::PathToDest< TreeType, CoordinateSystem::_3DWorld >::Result PathToDestResult;

	PathToDestResult v;
}