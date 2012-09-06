#include "scenario_conclusion.h"

#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace virt_dashboard;

void ScenarioConclusion::ExitSuccess()
{
    cout << "conclusion - SUCCESS" << endl;
    exit(0);
}

void ScenarioConclusion::ExitFail()
{
    cout << "conclusion - FAILURE" << endl;
    exit(1);
}

void ScenarioConclusion::Exit()
{
    exit(1);
}
