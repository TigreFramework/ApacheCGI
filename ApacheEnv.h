//
// Created by pedrosoares on 4/28/18.
//

#ifndef TIGREFRAMEWORK_APACHEENV_H
#define TIGREFRAMEWORK_APACHEENV_H

#include <string>
#include <map>
#include <TigreFramework/Core/Kernel/Application/Env.h>
#include <TigreFramework/Core/Kernel/Application/Configurable.h>

class ApacheEnv : public Env, public Configurable {

    public:
        virtual std::string get(std::string name, std::string default_value="");

};


#endif //TIGREFRAMEWORK_ENV_H
