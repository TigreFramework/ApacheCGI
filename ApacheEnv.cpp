//
// Created by pedrosoares on 4/28/18.
//

#include "ApacheEnv.h"

std::string ApacheEnv::get(std::string name, std::string default_value) {
    char* ENV_VALUE = getenv( name.c_str() );

    if (ENV_VALUE != nullptr)
        return ENV_VALUE;
    else
        return default_value;
}
