// src/color_management/callback_converter.cpp
#include "callback_converter.h"
#include <QtGlobal>

namespace artplus::color {

void CallbackConverter::convertColor(const std::vector<double>& input,
                                     const std::vector<CallbackFn>& callbacks,
                                     CallbackFn fn,
                                     int param,
                                     std::vector<double>& output) const
{
    Q_UNUSED(input);
    Q_UNUSED(callbacks);
    Q_UNUSED(fn);
    Q_UNUSED(param);

    if (output.size() != 1) {
        output.resize(1);
    }
    output[0] = fn(0.0);
}

} // namespace artplus::color