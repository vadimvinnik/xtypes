#include <cstdint>
#include <utility>

namespace xtypes
{
  template <std::size_t I, typename Product>
  struct product_helper {
    using others_t = typename Product::others_t;
    using accessor_t = product_helper<I-1, others_t>;
    using item_t = typename accessor_t::item_t;

    static item_t& get(Product& p) noexcept
      { return accessor_t::get(p.others); }
    static item_t const& get(Product const& p) noexcept
      { return accessor_t::get(p.others); }
    static item_t&& get(Product&& p) noexcept
      { return std::move(accessor_t::get(p.others)); }
  };

  template <typename Product>
  struct product_helper<0, Product> {
    using item_t = typename Product::first_t;

    static item_t& get(Product& p) noexcept
      { return p.first; }
    static item_t const& get(Product const& p) noexcept
      { return p.first; }
    static item_t&& get(Product&& p) noexcept
      { return p.first; }
  };
  
  template <typename... Args>
  struct product {};

  template <typename Head, typename... Tail>
  struct product<Head, Tail...> {
    using first_t = Head;
    using others_t = product<Tail...>;
    using this_t = product<Head, Tail...>;

    template <std::size_t I>
    using helper_t = product_helper<I, this_t>;

    template <std::size_t I>
    using item_t = typename helper_t<I>::item_t;

    first_t first;
    others_t others;

    template <std::size_t I>
    item_t<I>& get() & noexcept
      { return helper_t<I>::get(*this); }

    template <std::size_t I>
    item_t<I> const& get() const noexcept
      { return helper_t<I>::get(*this); }

    template <std::size_t I>
    item_t<I>&& get() && noexcept
      { return std::move(helper_t<I>::get(*this)); }
  };
}
