// src/color_management/callback_converter.cpp
#include "callback_converter.h"
#include "color_management_exception.h"

namespace artplus::color {

void CmmCallbackConverter::convertColor(const std::vector<double>& input,
                                        const std::vector<CallbackFn>& callbacks,
                                        CallbackFn fn,
                                        int param,
                                        std::vector<double>& output) const {
    if (param > 0 && static_cast<int>(input.size()) != param) {
        // Spec F-008 §5: nada é escrito em output quando a contagem diverge.
        throw ColorManagementException(0x124f86,
                                       QString::fromLatin1(messages::kChannelMismatch));
    }

    std::vector<double> result(input.size(), 0.0);
    for (std::size_t i = 0; i < input.size(); ++i) {
        double value = fn ? fn(input[i]) : input[i];
        for (const CallbackFn& callback : callbacks) {
            if (callback) {
                value = callback(value);
            }
        }
        result[i] = value;
    }
    output = std::move(result);
}

std::unique_ptr<CallbackConverter> CallbackConverter::create() {
    return std::make_unique<CmmCallbackConverter>();
}

} // namespace artplus::color
