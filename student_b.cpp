#include "shared_types.h"
#include <memory>

std::unique_ptr<Result> calculateB(std::shared_ptr<const InputData> data) {
    // TODO: реалізувати алгоритм Беллмана-Форда
    auto result = std::make_unique<Result>();
    result->algorithmName = "Алгоритм Беллмана-Форда (заглушка)";
    result->distance = 0.0;
    result->iterations = 0;
    return result;
}