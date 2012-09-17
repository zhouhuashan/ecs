#include "virtual_controller.h"

#include <iostream>

#include "program_options.h"
#include "controller_parser.h"
#include "protocol_controller.h"
#include "functions_vdb.h"

using namespace std;
using namespace virt_dashboard;

static const int kReceiveDelay = 2 * 1000;
static const int kAnswerDelay = 1;

VirtualController::VirtualController(ProgramOptions& options) : options_(options)
{
    ConfigureConnection();

    CreateProtocol();
}

void VirtualController::ConfigureConnection()
{
    connection_.SetLocalPoint(options_.GetString(kIpLocal),
                              options_.GetInt(kPortLocal));
    connection_.SetRemotePoint(options_.GetString(kIpRemote),
                               options_.GetInt(kPortRemote));
}

void VirtualController::CreateProtocol()
{
    ControllerParser parser(options_.GetString(kScenario));

    protocol_ = new ProtocolController(parser.GetAnswers());
}

VirtualController::~VirtualController()
{
    delete protocol_;
}

void VirtualController::Start()
{
    ByteArray request;
    ByteArray answer;

    while( true )
    {
        usleep(kReceiveDelay);
        request = connection_.ReceiveData();

        if ( request.empty() )
            continue;

        cout << "main()" << endl;
        cout << "\trequest = ";
        PrintByteArray(request);

        usleep(kAnswerDelay);
        answer = protocol_->GetAnswer(request);

        cout << "\tanswer = ";
        PrintByteArray(answer);

        connection_.SendData(answer);
    }
}
