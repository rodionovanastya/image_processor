#ifndef WORKSHOPX_ABSTRACT_FILTER_H
#define WORKSHOPX_ABSTRACT_FILTER_H

#include "../image.h"

#include <vector>
// Базовый класс всех фильтров. Параметры фильтра живут в наследнике
// (их туда кладёт продюсер), Apply только применяет их к картинке.
class AbstractFilter {
public:
    // Виртуальный деструктор обязателен: фильтры удаляются через указатель на базу
    // (Pipeline), без него это UB и утечка полей наследника.
    virtual ~AbstractFilter() = default;

    virtual void Apply(Image& image) const = 0;
};

#endif //WORKSHOPX_ABSTRACT_FILTER_H