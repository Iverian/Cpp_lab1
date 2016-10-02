#pragma once

#include <stdexcept>
#include <string>

/*
 * выкидываем runtime_error c заданным сообщением, при выполнении условия
 */
#define check_if(__cond__, __msg__) \
    if (__cond__)                   \
        throw std::runtime_error("[FATAL]:( " + std::string(__FILE__) + ", " + std::to_string(__LINE__) + " ): " + (__msg__));
