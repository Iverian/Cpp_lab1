#pragma once

#define _prop static constexpr auto

namespace str {
    _prop windowTitle = "Калькулятор";
    _prop normalMode = "Обычный";
    _prop engineerMode = "Инженерный";
}

namespace id {
    _prop ColumnDelta = 4;
    _prop magicNumber = 10;
    _prop maxDigitCount = 15;
}
