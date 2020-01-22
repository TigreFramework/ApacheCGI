#ifndef TIGREFRAMEWORK_APACHEHTTPCORE_H
#define TIGREFRAMEWORK_APACHEHTTPCORE_H


#include <TigreFramework/Core/Kernel/HttpCore.h>
#include <TigreFramework/Core/Kernel/Application/Configurable.h>

class ApacheHttpCore : public HttpCore, public Configurable {

    public:
        void handle() override;
        std::map<std::string, std::string> getHeaders();

};


#endif //TIGREFRAMEWORK_APACHEHTTPCORE_H
