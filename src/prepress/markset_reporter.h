#ifndef MARKSET_REPORTER_H
#define MARKSET_REPORTER_H

#include <string>
#include <vector>

namespace ArtPlus::Prepress {

class Reporter {
public:
    virtual ~Reporter() = default;

    // Avisos emitidos durante copyMarksToPage / applyMarksFromSet
    // IDs estáveis: DocumentMarks.Warning.MissingNamedObject / MissingPageBox
    virtual void warnMissingNamedObject(const std::vector<std::string>& names,
                                        const std::string& markSetName,
                                        size_t pageIndex) = 0;
    virtual void warnMissingPageBox(const std::string& boxName,
                                    const std::string& markSetName,
                                    size_t pageIndex) = 0;

    // Informativo: progresso de carregamento/aplicação
    virtual void info(const std::string& message) { (void)message; }
    virtual void error(const std::string& message) { (void)message; }
};

} // namespace ArtPlus::Prepress

#endif // MARKSET_REPORTER_H