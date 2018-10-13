//
// Created by pedrosoares on 5/24/18.
//

#ifndef TIGREFRAMEWORK_REQUESTEVENT_H
#define TIGREFRAMEWORK_REQUESTEVENT_H


#include <TigreFramework/Core/Event/Event.h>
#include <TigreFramework/Core/Kernel/Request.h>
#include <TigreFramework/Core/Kernel/Response.h>

class RequestEvent : public Event {

    public:
        RequestEvent(std::string name);
        RequestEvent(std::string name, Request* request);
        RequestEvent(std::string name, Response* response);
        RequestEvent(std::string name, Request* request, Response* response);

    private:
        std::string name;
        Request* request;
        Response* response;
};


#endif //TIGREFRAMEWORK_REQUESTEVENT_H
