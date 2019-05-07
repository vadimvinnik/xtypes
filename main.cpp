#include "product.h"
#include <iostream>

using record_t = xtypes::product<int, bool, std::string>;

void negate(bool& b) noexcept { b = !b; }

int main() {
  record_t r;

  xtypes::product_helper<0, record_t>::get(r) = 9;
  xtypes::product_helper<1, record_t>::get(r) = true;
  xtypes::product_helper<2, record_t>::get(r) = "a";

  ++r.first;
  negate(r.others.first);
  r.others.others.first += "bc";

  std::cout
    << r.get<0>()
    << " "
    << r.get<1>()
    << " ["
    << r.get<2>()
    << "]"
    << std::endl;

  auto const moved = std::move(r).get<2>();
  record_t const s = r;
  std::cout
    << " ["
    << r.get<2>()
    << "]"
    << std::endl;

  return 0;
}

