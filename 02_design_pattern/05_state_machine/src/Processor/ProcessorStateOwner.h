#include "template/StateOwner"

class ProcessorStateOwner : public StateOwner<ProcessorState> {
public:
    ProcessorStateOwner(StatePool<ProcessorState> state_pool,
                        ProcessorContext& context, ProcessorStateHandle initial_state);
    ~ProcessorStateOwner() = default;

    ProcessorStateContext& GetContext() { return context_; }

private:
    ProcessorStateContext& context_;
};
