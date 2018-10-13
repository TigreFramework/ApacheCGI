//
// Created by pedrosoares on 4/29/18.
//

#include <TigreFramework/Core/Kernel/Response.h>
#include <TigreFramework/Core/Kernel/Exception.h>
#include <TigreFramework/Core/Kernel/ExceptionHandler.h>
#include <TigreFramework/Core/Kernel/Application/Configuration.h>
#include <TigreFramework/Core/Kernel/Request.h>
#include <TigreFramework/Core/Kernel/Router.h>
#include <TigreFramework/Core/Kernel/Application.h>
#include <TigreFramework/String/String.h>
#include <TigreFramework/Core/Event/Event.h>
#include <TigreFramework/Apache/Event/RequestEvent.h>
#include "ApacheHttpCore.h"
#include "ApacheResponseStream.h"

void ApacheHttpCore::handle() {
    RequestEvent requestEventStated("request.started");
    Event::emit("request.started", requestEventStated);

    Response response;
    auto stream = Configuration::Get<ResponseStream*>("Response.Stream");
    try {
        //Mount the Request
        Request request(this->getRequestHeaders());

        RequestEvent requestEventInitiated("request.initiated", &request);
        Event::emit("request.initiated", requestEventInitiated);

        //Pass the request to the Router System Registered
        Router * router = (Router *) Configuration::get("Router");
        //Receive the Response or an Exception
        response = router->handle(&request);

        RequestEvent requestEventProcessed("request.processed", &request, &response);
        Event::emit("request.processed", requestEventProcessed);
    } catch (Exception & exception) {
        // TigreFramework Exception Standard
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    } catch(const std::runtime_error& re) {
        // If any extra code throws a std::runtime_error
        Exception exception(std::string("Runtime error: ") + re.what());
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    } catch(const std::exception& ex)  {
        // If any extra code throws a std::exception
        Exception exception(std::string("Error occurred: ") + ex.what());
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    } catch(const std::string& ex)  {
        // If someone have a crazy idea of throw a string it is catched here any way
        Exception exception("Error occurred: " + ex);
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    } catch(const char *& ex)  {
        // If someone have a crazy idea of throw a char pointer it is catched here any way
        Exception exception("Error occurred: " + std::string(ex));
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    } catch (...) {
        // If nothing else cant handle this is used to not make the system out of mind
        Exception exception("Unknown Error occurred");
        ExceptionHandler * exceptionHandler = (ExceptionHandler *) Configuration::get("Exception.Handler");
        exceptionHandler->report(exception);
        response = exceptionHandler->render(exception);
    }
    //Write the response to the Client (A Successful Request or an Exception)
    stream->write(response.render());

    RequestEvent requestEventEnded("request.ended");
    Event::emit("request.ended", requestEventEnded);
}

void ApacheHttpCore::addHeader(std::string name, std::string value) {
    if(value.empty()){
        this->headers.push_back(name);
    }else{
        this->headers.push_back(name + ": " + value);
    }
}

std::string ApacheHttpCore::getHeaders() {
    const char* const delim = "\r\n";

    std::ostringstream imploded;
    std::copy(this->headers.begin(), this->headers.end(), std::ostream_iterator<std::string>(imploded, delim));

    return imploded.str();
}

std::string ApacheHttpCore::getPostData() {
    auto headers = this->getRequestHeaders();

    std::string post_tmp;
    // Recebe do apache as informações POST
    while(headers.find("USER") == headers.end()) {
        std::string line;
        getline(std::cin, line);

        if (line.empty()) {
            break;
        }
        post_tmp += line;
    }
    return post_tmp;
}

//Load the Request Header using the envs variable, the envp is the way that apache pass the headers to the CGI
std::map<std::string, std::string> ApacheHttpCore::getRequestHeaders() {
    if(this->requestHeaders.empty()) {
        std::map<std::string, std::string> requestHeader;

        Application *application = (Application *) Configuration::get("app");
        auto envp = application->getEnvp();

        for (char **env = envp; *env != nullptr; env++) {
            std::string text(*env);

            Tigre::String environment = text;

            auto piece = environment.explode("=");
            if (piece.size() == 2) {
                requestHeader[piece[0].getValue()] = piece[1].getValue();
            }
        }

        this->requestHeaders = requestHeader;
    }

    return this->requestHeaders;
}