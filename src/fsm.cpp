

#include "fsm.h"
#include "typelist.h"

#include <cassert>
#include <iostream>

struct EnterSignal {};
struct ExitSignal {};

struct CloseSignal {};
struct OpenSignal {};

struct SensorSignal
{
	SensorSignal(bool closed, bool opened)
		: m_closed(closed)
		, m_opened(opened)
	{
		assert(!(closed && opened));
	}

	bool IsClosed() const
	{
		return m_closed;
	}

	bool IsOpened() const
	{
		return m_opened;
	}

private:
	bool m_closed;
	bool m_opened;
};

struct DummyState
{
	template<typename Sig>
	void operator()(const Sig &) const
	{
		// Should never be called!
		assert(false);
	}
};

template<typename TypeList, unsigned int N, bool INRANGE>
struct TypeListGetterImpl
{
	typedef typename TypeListTypeByIdx< TypeList, N >::Type RetType;

	RetType & DoGet(ValuesImpl< TypeList > & values)
	{
		return Get< N >(values);
	}

};

template<typename TypeList, unsigned int N>
struct TypeListGetterImpl< TypeList, N, false>
{
	typedef DummyState RetType;

	RetType & DoGet(ValuesImpl< TypeList > &)
	{
		return m_dummy;
	}

private:
	DummyState m_dummy;
};

template <typename TypeList, unsigned int N>
struct TypeListGetter
{
	enum {
		Size = TypeListSize< TypeList >::Size
	};

	static const bool InRange = N < Size;

	typedef TypeListGetterImpl< TypeList, N, InRange > GetterType;
	typedef typename GetterType::RetType RetType;

	static
	RetType & Get(ValuesImpl< TypeList > & values)
	{
		GetterType getter;
		return getter.DoGet(values);
	}
};

template <typename Derived, typename StatesTypeList>
struct FsmBase
{
	enum {
		TypeListSize = TypeListSize< StatesTypeList >::Size
	};

public:
	FsmBase()
		: m_currentState(TypeListSize)
		, m_nextState(TypeListSize)
		, m_states(static_cast<Derived&>(*this))
	{
	}

	template <typename SIG>
	void Signal(const SIG & sig)
	{
		assert(IsInitialized());
		Dispatch(sig);
		DoTransitions();
	}

	template<typename State>
	void SwitchTo()
	{
		assert(IsInitialized());
		const unsigned int nextState = TypeListIdxByType< StatesTypeList, State >::Idx;
		assert(nextState < TypeListSize);
		assert(m_nextState == m_currentState || nextState == m_nextState);
		m_nextState = nextState;
	}

protected:
	
	bool IsInitialized() const
	{
		return m_currentState < TypeListSize && m_nextState < TypeListSize;
	}

	void Init()
	{
		assert(!IsInitialized());
		m_currentState = 0;
		m_nextState = 0;
		Dispatch(EnterSignal());
		DoTransitions();
	}

	void DeInit()
	{
		assert(IsInitialized());
		Dispatch(ExitSignal());
		// Don't do any transitions at this point as we are exiting...
		
		// Set current and next state to invalids.
		m_currentState = TypeListSize;
		m_nextState = TypeListSize;
	}

private:

	void DoTransitions()
	{
		while (m_nextState != m_currentState) {
			Dispatch(ExitSignal());
			m_currentState = m_nextState;
			Dispatch(EnterSignal());
		}
	}

	template <unsigned int N, typename Sig>
	void DispatchSignalToState(const Sig & sig)
	{
		(TypeListGetter<StatesTypeList, N>::Get(m_states))(sig);
	}

	template <typename Sig>
	void Dispatch(const Sig & sig)
	{
		static_assert(TypeListSize <= 20, "More switch statements are needed");

		switch (m_currentState)
		{
		case 0: DispatchSignalToState< 0 >(sig); break;
		case 1: DispatchSignalToState< 1 >(sig); break;
		case 2: DispatchSignalToState< 2 >(sig); break;
		case 3: DispatchSignalToState< 3 >(sig); break;
		case 4: DispatchSignalToState< 4 >(sig); break;
		case 5: DispatchSignalToState< 5 >(sig); break;
		case 6: DispatchSignalToState< 6 >(sig); break;
		case 7: DispatchSignalToState< 7 >(sig); break;
		case 8: DispatchSignalToState< 8 >(sig); break;
		case 9: DispatchSignalToState< 9 >(sig); break;
		case 10: DispatchSignalToState< 10 >(sig); break;
		case 11: DispatchSignalToState< 11 >(sig); break;
		case 12: DispatchSignalToState< 12 >(sig); break;
		case 13: DispatchSignalToState< 13 >(sig); break;
		case 14: DispatchSignalToState< 14 >(sig); break;
		case 15: DispatchSignalToState< 15 >(sig); break;
		case 16: DispatchSignalToState< 16 >(sig); break;
		case 17: DispatchSignalToState< 17 >(sig); break;
		case 18: DispatchSignalToState< 18 >(sig); break;
		case 19: DispatchSignalToState< 19 >(sig); break;
		default:
			assert(false);
		};
	}

private:
	unsigned int					m_currentState;
	unsigned int					m_nextState;
	ValuesImpl< StatesTypeList >	m_states;

};

struct Fsm;

struct Initialize
{
	Initialize(Fsm & fsm) : m_fsm(fsm) { }

	void operator()(const EnterSignal & init) const;

	void operator()(const ExitSignal & exit) const { }

	template <typename SIG>
	void operator()(const SIG & s) const { assert(false); }

private:
	Fsm & m_fsm;
};

struct Closing
{
	Closing(Fsm & fsm) : m_fsm(fsm) { }

	void operator()(const EnterSignal & enter) const;

	void operator()(const ExitSignal & exit) const { }

	void operator()(const OpenSignal & open) const;

	void operator()(const CloseSignal & open) const { }

	void operator()(const SensorSignal & sensor) const;

	template <typename SIG>
	void operator()(const SIG & s) const;

private:
	Fsm & m_fsm;
};

struct Closed
{
	Closed(Fsm & fsm) : m_fsm(fsm) { }

	void operator()(const EnterSignal & enter) const { }

	void operator()(const ExitSignal & exit) const { }

	void operator()(const OpenSignal & open) const;

	void operator()(const CloseSignal & close) const { }

	void operator()(const SensorSignal & sensor) const;

	template <typename SIG>
	void operator()(const SIG & s) const;

private:
	Fsm & m_fsm;
};

struct Opening
{
	Opening(Fsm & fsm) : m_fsm(fsm) { }

	void operator()(const EnterSignal & enter) const;

	void operator()(const ExitSignal & exit) const { }

	void operator()(const OpenSignal & open) const { }

	void operator()(const CloseSignal & close) const;

	void operator()(const SensorSignal & sensor) const;

	template <typename SIG>
	void operator()(const SIG & s) const;

private:
	Fsm & m_fsm;
};

struct Opened
{
	Opened(Fsm & fsm) : m_fsm(fsm) { }

	void operator()(const EnterSignal & enter) const { }

	void operator()(const ExitSignal & exit) const { }

	void operator()(const OpenSignal & open) const { }

	void operator()(const CloseSignal & close) const;

	void operator()(const SensorSignal & sensor) const;

	template <typename SIG>
	void operator()(const SIG & s) const;

private:
	Fsm & m_fsm;
};

typedef MakeTypeList< Initialize, Closing, Closed, Opening, Opened >::TypeList StatesTypeList;

struct Fsm : FsmBase< Fsm, StatesTypeList >
{
	Fsm()
		: FsmBase< Fsm, StatesTypeList >()
	{
		Init();
	}

	~Fsm()
	{
		DeInit();
	}

	void PowerOpening()
	{
		std::cout << "Drive motor to open...\n";
	}

	void PowerClosing()
	{
		std::cout << "Drive motor to close...\n";
	}

	void Stop()
	{
		std::cout << "Stop motor...\n";
	}
};


void Initialize::operator()(const EnterSignal & init) const
{
	std::cout << "Initialize(EnterSignal)\n";
	m_fsm.SwitchTo< Closing >();
}

void Closing::operator()(const EnterSignal & init) const
{
	std::cout << "Closing(EnterSignal)\n";
	m_fsm.PowerClosing();
}

void Closing::operator()(const OpenSignal & open) const
{
	std::cout << "Closing(OpenSignal)\n";
	m_fsm.SwitchTo<Opening>();
}

void Closing::operator()(const SensorSignal & sensor) const
{
	std::cout << "Closing(SensorSignal)\n";
	if (sensor.IsClosed()) {
		m_fsm.SwitchTo<Closed>();
	}
}

void Closed::operator()(const OpenSignal & open) const
{
	std::cout << "Closed(OpenSignal)\n";
	m_fsm.SwitchTo<Opening>();
}

void Closed::operator()(const SensorSignal & sensor) const
{
	std::cout << "Closed(SensorSignal)\n";
	if (!sensor.IsClosed()) {
		std::cout << "Surprize!!! We got a strange sensor signal saying door is not closed!\n";
		std::cout << "Close it\n";
		m_fsm.SwitchTo< Closing >();
	}
}

void Opening::operator()(const EnterSignal & enter) const
{
	std::cout << "Opening(EnterSignal)\n";
	m_fsm.PowerOpening();
}

void Opening::operator()(const CloseSignal & close) const
{
	std::cout << "Opening(CloseSignal)\n";
	m_fsm.SwitchTo< Closing >();
}

void Opening::operator()(const SensorSignal & sensor) const
{
	std::cout << "Opening(SensorSignal)\n";
	if (sensor.IsOpened()) {
		m_fsm.SwitchTo< Opened >();
	}
}

void Opened::operator()(const CloseSignal & close) const
{
	std::cout << "Opened(CloseSignal)\n";
	m_fsm.SwitchTo< Closing >();
}

void Opened::operator()(const SensorSignal & sensor) const
{
	std::cout << "Opened(SensorSignal)\n";
	if (!sensor.IsOpened()) {
		std::cout << "Surprize!!! We got a strange sensor signal saying door is not opened!\n";
		std::cout << "Open it\n";
		m_fsm.SwitchTo< Opening >();
	}
}


void fsmRun()
{
	Values< int, double, float, char > values;

	float & f = Get< 2 >(values);
	f = 3.5f;

	Fsm fsm;

	fsm.Signal(OpenSignal());
	fsm.Signal(OpenSignal());
	fsm.Signal(OpenSignal());
	fsm.Signal(SensorSignal(false, true));
	fsm.Signal(OpenSignal());
	fsm.Signal(CloseSignal());
	fsm.Signal(CloseSignal());
	fsm.Signal(OpenSignal());
}