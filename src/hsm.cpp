

#include <cassert>
#include <memory>


struct StateBase
{
    virtual void handle() = 0;

    virtual void dispatch() = 0;
};

typedef std::unique_ptr< StateBase > StateBaseUniquePtr;

template <typename>
struct Machine;


template<typename ParentState, typename CurrentState, typename SwitchState>
struct StateSwitcher
{
    static void doSwitch(CurrentState & currentState)
    {
        assert(!currentState.m_done);
        currentState.m_done = true;
        StateSwitcher< ParentState, typename CurrentState::Parent, SwitchState>::doSwitch(currentState.m_parent);
    }
};

template<typename ParentState, typename SwitchState>
struct StateSwitcher<typename ParentState, typename ParentState, typename SwitchState>
{
    static void doSwitch(ParentState & currentState)
    {
        currentState.setNextState<SwitchState>();
    }
};

template<typename Derived, typename CurrentState, typename SwitchState>
struct StateSwitcher<Machine<Derived>, CurrentState, SwitchState>
{
    static void doSwitch(CurrentState & currentState)
    {
        static_assert(false, "Impossible transition");
    }
};

template<typename CurrentState>
struct StateStopper
{
    static void doStop(CurrentState & currentState)
    {
        currentState.m_done = true;
        StateStopper< typename CurrentState::Parent >::doStop(currentState.m_parent);
    }
};

template<typename Derived>
struct StateStopper< Machine< Derived > >
{
    static void doStop(Machine< Derived > & currentState)
    {
    }
};


template<typename Parent>
struct StateCommon : StateBase
{
    typedef Parent Parent;

    StateCommon(Parent & parent)
        : m_parent(parent)
        , m_done()
    {
    }

    ~StateCommon()
    {
        assert(!m_done);
    }

    template<typename NextState>
    void switchTo()
    {
        typedef typename NextState::Parent NextStateParent;
        m_done = true;
        StateSwitcher< NextStateParent, Parent, NextState >::doSwitch(m_parent);
    }

    virtual void dispatch()
    {
        assert(!m_done);
        while (!m_done)
        {
            handle();
        }

        m_done = false;
    }

    void signalStop()
    {
        StateStopper< StateCommon >::doStop(*this);
    }

    Parent &            m_parent;

    bool                m_done;
};

template<typename Derived, typename Parent>
struct StateContainer : StateCommon< Parent >
{
    typedef Parent Parent;

    StateContainer(Parent & parent)
        : StateCommon< Parent >(parent)
        , m_currentState()
        , m_nextState()
    {
    }

    ~StateContainer()
    {
        assert(m_nextState == nullptr);
    }

    // !non public
    virtual void dispatch()
    {
        assert(!m_done);
        while (!m_done && m_currentState == nullptr)
        {
            handle();
        }

        if (!m_done && m_currentState != nullptr)
        {
            while (!m_done)
            {
                m_currentState->dispatch();
                if (m_nextState != nullptr)
                {
                    m_currentState = std::move(m_nextState);
                }
            }
        }

        m_done = false;
    }

    template<typename State>
    void setInitialState()
    {
        // add static assert
        assert(!m_done);

        assert(m_currentState == nullptr);
        m_currentState.reset(new State(static_cast<Derived&>(*this)));
    }

    // !non public
    template <typename State>
    void setNextState()
    {
        // add static assert
        assert(!m_done);

        assert(m_nextState == nullptr);
        m_nextState.reset(new State(static_cast<Derived&>(*this)));
    }

    // !non public
    StateBaseUniquePtr  m_currentState;
    StateBaseUniquePtr  m_nextState;

};

template<typename Derived>
struct Machine : StateContainer< Derived, Machine< Derived > >
{
    typedef StateContainer< Derived, Machine > Base;

    Machine()
        : Base(*this)
    {
    }

};

struct LeafState;
struct LeafStateTwo;
struct MiddleState;
struct LeafStateThree;
struct TopState;

struct LeafState : StateCommon< MiddleState >
{
    LeafState(MiddleState & state)
        : StateCommon<MiddleState>(state)
    {
    }

    virtual void handle()
    {
        switchTo< LeafStateTwo >();
        signalStop();
    }
};


struct LeafStateTwo : StateCommon< MiddleState >
{
    LeafStateTwo(MiddleState & state)
        : StateCommon<MiddleState>(state)
    {
    }

    virtual void handle()
    {
        //switchTo< LeafStateThree >();
        switchTo<MiddleState>();
        signalStop();
    }
};


struct MiddleState : StateContainer< MiddleState, TopState >
{
    typedef StateContainer< MiddleState, TopState > Base;

    MiddleState(TopState & state)
        : Base(state)
    {
    }

    virtual void handle()
    {
        //setInitialState< LeafState >();
        //signalStop();
        switchTo<LeafStateThree>();
    }
};

struct LeafStateThree : StateCommon< TopState >
{
    typedef StateCommon< TopState > Base;

    LeafStateThree(TopState & state)
        : Base(state)
    {
    }

    virtual void handle()
    {
        switchTo<LeafStateThree>();
        signalStop();
    }
};

struct TopState : Machine< TopState >
{
    typedef Machine< TopState > Base;

    TopState()
        : Base()
    {
    }

    virtual void handle()
    {
        setInitialState<MiddleState>();
    }
};



void hsmRun()
{
    TopState machine;

    machine.dispatch();
    machine.dispatch();
    machine.dispatch();
}