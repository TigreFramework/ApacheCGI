//
// Created by pedrosoares on 5/24/18.
//

#include "RequestEvent.h"

RequestEvent::RequestEvent(std::string name) : name(name) {

}

RequestEvent::RequestEvent(std::string name, Request* request) : name(name), request(request) {

}

RequestEvent::RequestEvent(std::string name, Response* response) : name(name), response(response) {

}

RequestEvent::RequestEvent(std::string name, Request* request, Response* response)
        : name(name), request(request), response(response) {

}