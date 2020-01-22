#ifndef TIGREFRAMEWORK_APACHERESPONSESTREAM_H
#define TIGREFRAMEWORK_APACHERESPONSESTREAM_H

#include <TigreFramework/Core/Kernel/ResponseStream.h>
#include <TigreFramework/Core/Kernel/Application/Configurable.h>
#include <string>

class ApacheResponseStream : public ResponseStream, public Configurable {

    public:
        void write(std::string data);

};


#endif //TIGREFRAMEWORK_APACHERESPONSESTREAM_H
