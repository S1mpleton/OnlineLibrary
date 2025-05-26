#ifndef PAGINATION_H
#define PAGINATION_H


#include "database/databasecore.h"
#include <cstddef>


class Pagination
{
public:
    Pagination(size_t quantity_on_page, size_t current_page);

    ParametersRequest get_parametrs_request() const;

private:
    size_t quantity_on_page;
    size_t current_page;
};

#endif // PAGINATION_H
