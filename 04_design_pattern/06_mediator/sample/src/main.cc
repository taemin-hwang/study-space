#include <iostream>
#include <string>
#include <memory>
#include "diag_handler.h"

using namespace std;

int main() {
    std::unique_ptr<DiagHandler> diag_handler = std::make_unique<DiagHandler>();
    diag_handler->Initialize();
    diag_handler->Run();
    diag_handler->Shutdown();
}
