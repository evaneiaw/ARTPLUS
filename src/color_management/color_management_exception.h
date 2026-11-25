// src/color_management/color_management_exception.h
// F-008 — exceção do subsistema de cor.
//
// Equivalente ao GCSimpleException observado em
// GCColorManipulation::GetActiveICCProfile (0x180012bf0), que lança com o
// código 0x124f85 quando não existe perfil (cache vazio ou nenhum match).
#pragma once

#include <QString>
#include <stdexcept>

namespace artplus::color {

// Mensagens de erro declaradas na spec F-008 §4 R6 (strings do .rdata do
// ColorManipulationLayer.dll). São constantes de compilação — a spec descreve
// o carregamento do .rdata; em C++ o equivalente é uma tabela de literais.
namespace messages {
inline constexpr auto kNoProfileDefined = "No XYZ ICC profile has been defined";
inline constexpr auto kProfileReadFailed = "An ICC profile could not be read";
inline constexpr auto kInvalidProfile = "Invalid ICC profile";
inline constexpr auto kCmmUnavailable =
    "Color conversion was not possible because the requested CMM engine was not available";
inline constexpr auto kChannelMismatch = "Incorrect number of input values for color conversion";
inline constexpr auto kNotInitialized = "No Color Management support available";
} // namespace messages

class ColorManagementException : public std::runtime_error {
public:
    // Código de erro observado no binário de referência (0x180012bf0).
    static constexpr int kErrorCodeNoProfile = 0x124f85;

    ColorManagementException(int code, const QString& message)
        : std::runtime_error(message.toStdString()), m_code(code), m_message(message) {}

    int code() const noexcept { return m_code; }
    QString message() const { return m_message; }

private:
    int m_code;
    QString m_message;
};

} // namespace artplus::color
