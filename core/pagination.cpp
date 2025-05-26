#include "pagination.h"

Pagination::Pagination(size_t quantity_on_page, size_t current_page) :
    quantity_on_page{quantity_on_page}, current_page{current_page}
{}


ParametersRequest Pagination::get_parametrs_request() const{
    ParametersRequest parameters;

    size_t offset = (current_page - 1) * quantity_on_page;

    parameters.insert(":limit", quantity_on_page);
    parameters.insert(":offset", offset);

    return parameters;
}
