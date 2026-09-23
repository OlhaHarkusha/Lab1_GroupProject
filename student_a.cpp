#include "shared_types.h"
#include <memory>

std::unique_ptr<Result> calculateA(std::shared_ptr<const InputData> data) {
    // TODO: реалізувати алгоритм Дейкстри
    auto result = std::make_unique<Result>();
    result->algorithmName = "Алгоритм Дейкстри (заглушка)";
    result->distance = 0.0;
    result->iterations = 0;
    return result;
}