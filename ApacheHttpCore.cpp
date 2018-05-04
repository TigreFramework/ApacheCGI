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
#include "ApacheHttpCore.h"
#include "ApacheResponseStream.h"

void ApacheHttpCore::handle() {
    Response response;
    ResponseStream * stream = (ResponseStream *) Configuration::get("Response.Stream");
    try {
        //Mount the Request
        Request request(this->getHeaders());
        //Pass the request to the Router System Registered
        Router * router = (Router *) Configuration::get("Router");
        //Receive the Response or an Exception
        response = router->handle(&request);
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
}

//Load the Request Header using the envs variable, the envp is the way that apache pass the headers to the CGI
std::map<std::string, std::string> ApacheHttpCore::getHeaders() {
    std::map<std::string, std::string> requestHeader;

    Application * application = (Application *) Configuration::get("app");
    auto envp = application->getEnvp();

    for (char **env = envp; *env != nullptr; env++){
        std::string text(*env);

        Tigre::String environment = text;

        auto piece = environment.explode("=");
        if(piece.size() == 2) {
            requestHeader[piece[0].getValue()] = piece[1].getValue();
        }
    }

    return requestHeader;
}