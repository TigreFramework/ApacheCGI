//
// Created by pedrosoares on 4/29/18.
//

#ifndef TIGREFRAMEWORK_APACHEHTTPCORE_H
#define TIGREFRAMEWORK_APACHEHTTPCORE_H


#include <TigreFramework/Core/Kernel/HttpCore.h>

class ApacheHttpCore : public HttpCore {

    public:
        void handle() override;
        void addHeader(std::string name, std::string value) override;
        std::string getHeaders() override;
        std::string getPostData() override;
        std::map<std::string, std::string> getRequestHeaders();

    private:
        std::vector<std::string> headers;
        std::map<std::string, std::string> requestHeaders;

};


#endif //TIGREFRAMEWORK_APACHEHTTPCORE_H
