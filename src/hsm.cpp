
#include <cassert>
#include <memory>

class CStateHelper
{
public:
    template<typename State>
    static
    typename State::Parent & getParent(State & state)
    {
        return state.getParent();
    }

    template<typename State>
    static
    void stop(State & state)
    {
        state.stop();
    }

    template<typename NextState, typename State>
    static
    void setNextState(State & state)
    {
        state.setNextState<NextState>();
    }

    template<typename State>
    static
    void clearCurrentState(State & state)
    {
        state.clearCurrentState();
    }
};


class CState
{
public:
    virtual ~CState()
    {
    }

    virtual void handle() = 0;

    virtual void dispatch() = 0;
};

typedef std::unique_ptr< CState > CStateUniquePtr;

template <typename CurrentState, typename SwitchState>
class TIsDirectChild : public std::is_same< CurrentState, typename SwitchState::Parent >
{
};

template<typename CurrentState, typename SwitchState>
class TStateSwitchParent;

template
<
    typename CurrentState,
    typename SwitchState,
    bool CommonParent = TIsDirectChild< CurrentState, SwitchState>::value
>
class TStateSwitchOther
{
public:
    static_assert(!std::is_same<typename CurrentState::Parent, CurrentState>::value, "Impossible transition");

    static void doSwitch(CurrentState & currentState)
    {
        CStateHelper::stop(currentState);
        TStateSwitchParent< typename CurrentState::Parent, SwitchState >::doSwitch(CStateHelper::getParent(currentState));
    }
};

template <typename CurrentState, typename SwitchState>
class TStateSwitchOther< CurrentState, SwitchState, true >
{
public:
    static void doSwitch(CurrentState & currentState)
    {
        CStateHelper::setNextState<SwitchState>(currentState);
    }
};

template<typename CurrentState, typename SwitchState>
class TStateSwitchParent : public TStateSwitchOther< CurrentState, SwitchState >
{
};

template<typename CurrentState>
class TStateSwitchParent< CurrentState, CurrentState >
{
public:
    static void doSwitch(CurrentState & currentState)
    {
        CStateHelper::clearCurrentState(currentState);
    }
};

template
<
    typename CurrentState,
    typename SwitchState,
    bool DirectChild = TIsDirectChild< CurrentState, SwitchState >::value
>
class TStateSwitchChild : public TStateSwitchParent< CurrentState, SwitchState >
{
};

template<typename CurrentState, typename SwitchState>
class TStateSwitchChild< CurrentState, SwitchState, true >
{
public:
    static void doSwitch(CurrentState & currentState)
    {
        CStateHelper::setNextState<SwitchState>(currentState);
    }
};

template<typename CurrentState, typename SwitchState>
class TStateSwitch : public TStateSwitchChild< CurrentState, SwitchState >
{
};

template<typename CurrentState>
class TStateSwitch< CurrentState, CurrentState >
{
public:
    static void doSwitch(CurrentState & currentState)
    {
        // a noop, we remain where we are
        // we can assert that there is no current state
        // we can also raise a static assert as this is strange operation
    }
};


template<typename CurrentState, typename ParentState = typename CurrentState::Parent>
class TStateStop
{
public:
    static void doStop(CurrentState & currentState)
    {
        CStateHelper::stop(currentState);
        TStateStop< ParentState >::doStop(CStateHelper::getParent(currentState));
    }
};

template<typename ParentState>
class TStateStop< ParentState, ParentState >
{
public:
    static void doStop(ParentState & currentState)
    {
        CStateHelper::stop(currentState);
    }
};


template<typename StateDef>
class TStateBase : public CState
{
    friend class CStateHelper;

public:
    typedef typename StateDef::State State;
    typedef typename StateDef::Parent Parent;

    TStateBase(Parent & parent)
        : m_parent(parent)
        , m_handleCount()
        , m_currentState()
        , m_nextState()
        , m_haveNext()
        , m_done()
    {
    }

    ~TStateBase()
    {
        assert(m_nextState == nullptr);
        assert(!m_haveNext);
        assert(!m_done);
    }

    virtual void dispatch()
    {
        assert(!m_done);
        do
        {
            if (m_currentState != nullptr)
            {
                m_currentState->dispatch();   
            }
            else
            {
                ++m_handleCount;
                handle();
            }

            if (m_haveNext)
            {
                assert(m_currentState != nullptr || m_nextState != nullptr);
                m_currentState = std::move(m_nextState);
                m_haveNext = false;
            }
            assert(m_nextState == nullptr);
        } while (!m_done);

        m_done = false;
    }
    
protected:
    unsigned int getHandleCount() const
    {
        return m_handleCount;
    }

    template<typename NextState>
    void switchTo()
    {
        TStateSwitch< State, NextState >::doSwitch(static_cast<State&>(*this));
    }

    void signalStop()
    { 
        TStateStop< State >::doStop(static_cast<State&>(*this));
    }

private:
    template <typename NextState>
    void setNextState()
    {
        // Not always true, could be that we have multiple switchTo<>
        // calls and this one is most recent.
        //assert(!m_haveNext);
        //assert(m_nextState == nullptr);

        m_nextState.reset(new NextState(static_cast<State&>(*this)));
        m_haveNext = true;
    }

    void clearCurrentState()
    {
        // This function can't simply go about and delete current state
        // because could be that we have multiple states nested doing some work/cleanups.
        //
        // So the strategy is to delegate the responsability to its parent(this) in order to after
        // exiting.

        // We always have a current state.
        assert(m_currentState != nullptr);

        // Not always true, could be that we have multiple switchTo<>
        // calls and this one is most recent.
        //assert(!m_haveNext);
        //assert(m_nextState == nullptr);

        m_haveNext = true;
        m_nextState.reset();
    }

    void stop()
    {
        m_done = true;
    }

    Parent & getParent() const
    {
        return m_parent;
    }

protected:
    Parent &            m_parent;

private:
    unsigned int        m_handleCount;

    CStateUniquePtr     m_currentState;
    CStateUniquePtr     m_nextState;
    bool                m_haveNext;
    bool                m_done;
};

struct LeafState;
struct LeafStateTwo;
struct MiddleState;
struct MiddleStateTwo;
struct LeafStateThree;
struct LeafStateFour;
struct TopState;

struct LeafStateDef
{
    typedef LeafState       State;
    typedef MiddleState     Parent;
};

struct LeafState : TStateBase< LeafStateDef >
{
    typedef TStateBase< LeafStateDef > Base;

    LeafState(MiddleState & parent)
        : Base(parent)
    {
    }

    virtual void handle()
    {
        //switchTo< LeafStateFour >();
        switchTo< LeafStateTwo >();
        signalStop();
    }

};

struct LeafStateTwoDef
{
    typedef LeafStateTwo        State;
    typedef MiddleState         Parent;
};

struct LeafStateTwo : TStateBase< LeafStateTwoDef >
{
    typedef TStateBase< LeafStateTwoDef > Base;

    LeafStateTwo(MiddleState & parent)
        : Base(parent)
    {
    }

    virtual void handle()
    {
        switchTo<MiddleState>();
        signalStop();
    }

};

struct MiddleStateDef
{
    typedef MiddleState State;
    typedef TopState Parent;
};

struct MiddleState : TStateBase< MiddleStateDef >
{
    typedef TStateBase< MiddleStateDef > Base;

    MiddleState(TopState & parent)
        : Base(parent)
    {
    }

    virtual void handle()
    {
        if (getHandleCount() < 10)
        {
            switchTo<LeafState>();
        }
        else
        {
            switchTo<LeafStateThree >();
        }
    }
};

struct MiddleStateTwoDef
{
    typedef MiddleStateTwo      State;
    typedef MiddleState         Parent;
};

struct MiddleStateTwo : TStateBase< MiddleStateTwoDef >
{
    typedef TStateBase< MiddleStateTwoDef > Base;
    MiddleStateTwo(MiddleState & parent)
        : Base(parent)
    {

    }

    virtual void handle()
    {
        switchTo< LeafStateFour >();
    }
};

struct LeafStateThreeDef
{
    typedef LeafStateThree      State;
    typedef TopState            Parent;
};

struct LeafStateThree : TStateBase< LeafStateThreeDef >
{
    typedef TStateBase< LeafStateThreeDef > Base;

    LeafStateThree(TopState & parent)
        : Base(parent)
    {
    }

    virtual void handle()
    {
        if (getHandleCount() < 30)
        {
            switchTo<LeafStateThree>();
            signalStop();
        }
        else
        {
            switchTo< TopState >();

        }
    }
};

struct LeaftStateFourDef
{
    typedef LeafStateFour       State;
    typedef MiddleStateTwo      Parent;
};

struct LeafStateFour : TStateBase< LeaftStateFourDef >
{
    typedef TStateBase< LeaftStateFourDef > Base;

    LeafStateFour(MiddleStateTwo & parent)
        : Base(parent)
    {
    }

    virtual void handle()
    {
        //switchTo< LeafStateTwo >();
        switchTo< LeafStateTwo >();
        signalStop();
    }
};

struct TopStateDef
{
    typedef TopState            Parent;
    typedef TopState            State;
};

struct TopState : TStateBase< TopStateDef >
{
    typedef TStateBase< TopStateDef > Base;

    TopState()
        : Base(*this)
    {
    }

    virtual void handle()
    {
        switchTo<MiddleState>();
    }
};

void hsmRun()
{
    TopState machine;

    for (unsigned int i = 0u; i < 100u; ++i)
    {
        machine.dispatch();
        machine.dispatch();
        machine.dispatch();
    }
}