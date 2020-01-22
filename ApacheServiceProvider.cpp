#include "ApacheServiceProvider.h"
#include "ApacheEnv.h"
#include "ApacheResponseStream.h"
#include "ApacheHttpCore.h"
#include <TigreFramework/Core/Kernel/Application/Configuration.h>

void ApacheServiceProvider::boot() {
    Configuration::set("Response.Stream", new ApacheResponseStream());
    Configuration::set("env", new ApacheEnv());
    Configuration::set("Http.Core", new ApacheHttpCore());
}