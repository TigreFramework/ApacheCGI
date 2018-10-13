//
// Created by pedrosoares on 4/28/18.
//

#include "ApacheResponseStream.h"
#include <string>
#include <iostream>

void ApacheResponseStream::write(std::string data) {
    std::cout << data << std::endl;
}