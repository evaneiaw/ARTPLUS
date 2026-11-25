// src/color_management/callback_converter.h
#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace artplus::color {

using CallbackFn = std::function<double(double)>;

class CallbackConverter {
public:
    virtual ~CallbackConverter() = default;

    // 0x18000a2f0 — GCCallbackConverter::ConvertColor.
    // R5: para cada canal i, parte de fn(input[i]) (ou input[i] quando fn é
    // vazio) e aplica os callbacks em sequência, gravando o resultado em
    // output[i]. `param` é o número de canais esperado (0 desativa a
    // validação — spec F-008 §5, "Incorrect number of input values for color
    // conversion"); com contagem divergente nada é escrito em `output`.
    virtual void convertColor(const std::vector<double>& input,
                              const std::vector<CallbackFn>& callbacks,
                              CallbackFn fn,
                              int param,
                              std::vector<double>& output) const = 0;

    // Implementação base do módulo (pipeline puro, sem lcms).
    static std::unique_ptr<CallbackConverter> create();
};

// Pipeline de callbacks do módulo canônico.
class CmmCallbackConverter final : public CallbackConverter {
public:
    void convertColor(const std::vector<double>& input,
                      const std::vector<CallbackFn>& callbacks,
                      CallbackFn fn,
                      int param,
                      std::vector<double>& output) const override;
};

} // namespace artplus::color
