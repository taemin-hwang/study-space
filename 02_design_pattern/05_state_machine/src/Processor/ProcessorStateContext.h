#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class ProcessorStateOwner;

class ProcessorStateContext {
public:
    ProcessorStateContext(Database& database) : database_{database} {}
    virtual ~ProcessorStateContext() = default;

    virtual void ChangeState(ProcessorStateHandle handle) = 0;
private:
    Database database_;
};
