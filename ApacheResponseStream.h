//
// Created by pedrosoares on 4/28/18.
//

#ifndef TIGREFRAMEWORK_APACHERESPONSESTREAM_H
#define TIGREFRAMEWORK_APACHERESPONSESTREAM_H

#include <TigreFramework/Core/Kernel/ResponseStream.h>
#include <string>

class ApacheResponseStream : public ResponseStream {

    public:
        void write(std::string data);

};


#endif //TIGREFRAMEWORK_APACHERESPONSESTREAM_H
