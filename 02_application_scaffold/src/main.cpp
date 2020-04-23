#include "application.h"
#include "application_scaffold.h"

using namespace std;

int main(int argc, char** argv) {
    return ApplicationScaffold<App>::Launch(argc, argv);
}
