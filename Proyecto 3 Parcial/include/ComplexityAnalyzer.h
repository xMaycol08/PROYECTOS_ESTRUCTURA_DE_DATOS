#ifndef COMPLEXITYANALYZER_H
#define COMPLEXITYANALYZER_H

#include <string>
#include <vector>

class ComplexityAnalyzer {
public:
    static void analizarComplejidad(const std::string& className, const std::string& functionName);
    static std::vector<std::string> obtenerClases();
    static std::vector<std::string> obtenerFunciones(const std::string& className);
};

#endif // COMPLEXITYANALYZER_H