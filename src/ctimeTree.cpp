#include "ctimeTree.h"

#include "typelist.h"

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


	//values.Get< 0 >();

	typedef TreeNodeHelper::PathToDest< TreeType, CoordinateSystem::_3DWorld >::Result PathToDestResult;

	PathToDestResult v;
}