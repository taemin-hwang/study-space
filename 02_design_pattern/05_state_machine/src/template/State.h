template <typename StateHandle, class Context>
class State {
public:
    explicit State(const StateHandle handle) : handle_(handle) {}
    virtual ~State() = default;

    virtual void OnEnter(Context& context) = 0;
    virtual void OnLeave(Context& context) = 0;
    virtual bool IsValidChange(const StateHandle handle) const = 0;
    const StateHandle GetHandle() const { return handle_; }

    State(const State&) = delete;
    State& opreate=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

private:
    const StateHandle handle_;
};
