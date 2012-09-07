#include <iostream>

#include "program_options.h"

using namespace std;
using namespace virt_dashboard;

int main(int argc, char* argv[])
{
    ProgramOptions options(argc, argv);

    if ( ! options.IsComplete() )
    {
        cout << options.GetDescription() << "\n";
        return 1;
    }

    return 0;
}
