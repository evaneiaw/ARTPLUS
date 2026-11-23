// src/color_management/callback_converter.h
#pragma once
#include <functional>
#include <vector>

namespace artplus::color {

using CallbackFn = std::function<double(double)>;

class CallbackConverter {
public:
    virtual ~CallbackConverter() = default;

    // 0x18000a2f0 - virtual pipeline de conversão de cor com callbacks injetáveis
    virtual void convertColor(const std::vector<double>& input,
                              const std::vector<CallbackFn>& callbacks,
                              CallbackFn fn,
                              int param,
                              std::vector<double>& output) const = 0;
};

} // namespace artplus::color