#include "template/State.h"
#include "template/StatePool.h"

template <class State>
class StateOwner {
public:
    using Handle = typename State::Handle;
    using Context = typename State::Context;

    StateOwner(StatePool<State>& state_pool, Handle handle)
        : state_pool_(state_pool), state_(state_pool.GetState(handle)) {}

    StateOnwer(const StateOwner&) = delete;
    StateOnwer& operator=(const StateOwner&) = delete;
    StateOnwer(StateOwner&&) = delete;
    StateOnwer& operator=(StateOwner&&) = delete;

    virtual~StateOwner() = default;

    State* GetState() { return state_; }
    State Const* GetState() const { return state_; }

    virtual Context& GetContext() = 0;

    // \brief Tries to change current state to state associated to given handle
    // \param handle: handle of the state to which change is requested
    bool TryChangeState(const Handle handle) {
        bool ret_value = false;
        if(state_->IsValidChange(handle)) {
            state_->OnLeave(GetContext());
            state_ = state_pool_.GetState(handle);
            state_->OnEnter(GetContext());
            ret_value = true;
        }

        return ret_value;
    }

private:
    StatePool<State>& state_pool_;
    State* state_;
}
