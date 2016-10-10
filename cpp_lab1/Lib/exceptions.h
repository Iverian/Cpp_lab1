#pragma once

#include <stdexcept>
#include <string>

/*
 * ���������� runtime_error c �������� ����������, ��� ���������� �������
 */
#define check_if(__cond__, __msg__) \
    if (__cond__)                   \
        throw std::runtime_error("[FATAL]:( " + std::string(__FILE__) + ", " + std::to_string(__LINE__) + " ): " + (__msg__));
