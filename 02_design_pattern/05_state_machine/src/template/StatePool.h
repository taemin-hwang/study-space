template <class State>
class StatePool {
public:
    using Handle = typename State::StateHandle;

    virtual ~StatePool() = default;

    virtual State* GetState(const Handle handle) = 0;
    virtual bool IsValid(const Handle handle) const = 0;
}
