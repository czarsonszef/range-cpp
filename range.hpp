#ifndef RANGE_HPP_INCLUDED
#define RANGE_HPP_INCLUDED

#include <type_traits>

namespace rg {

    template <class T, class U, class W = int>
    class range {

        static_assert(std::is_arithmetic_v<T> &&
                      std::is_arithmetic_v<U> &&
                      std::is_arithmetic_v<W>);

        struct end_empty_tag {};

    public:

        class __range_begin_type {

        public:

            constexpr __range_begin_type(range<T, U, W>& rng) noexcept
                : m_rng{rng}
            {

            }

            constexpr auto operator++() noexcept -> decltype(auto) {
                m_rng.m_n += m_rng.m_step;
                return *this;
            }

            constexpr auto operator!=(end_empty_tag) const noexcept {
                return m_rng.m_cmp(m_rng.m_n, m_rng.m_to);
            }

            constexpr auto operator*() const noexcept {
                return m_rng.m_n;
            }

        private:

            range<T, U, W>& m_rng;

        };

        friend class __range_begin_type;

        using inner_type = std::common_type_t<T, U, W>;

    private:

        static constexpr bool less(inner_type lhs, inner_type rhs) noexcept {
            return lhs < rhs;
        }

        static constexpr bool greater(inner_type lhs, inner_type rhs) noexcept {
            return lhs > rhs;
        }

    public:

        constexpr range(T from, U to, W step = 1) noexcept
            : m_n    { static_cast<inner_type>(from) }
            , m_to   { static_cast<inner_type>( to ) }
            , m_step { static_cast<inner_type>(step) }
            , m_cmp  { from < to ? &less : &greater  }
        {
            if ((m_n < m_to && m_step < 0) || (m_n > m_to && m_step > 0)) // if this check passes it means the range is incorrect (for example 'range(5, 20, -5)')
            {
                m_n = m_to; // makes detail::range_begin_type::operator!=() return false, the for loop won't be entered
            }
        }

        constexpr auto begin() noexcept -> __range_begin_type {
            return *this;
        }

        constexpr auto end() const noexcept -> end_empty_tag {
            return {};
        }

    private:

        inner_type m_n;
        inner_type m_to;
        inner_type m_step;
        bool (*m_cmp)(inner_type, inner_type);

    };


} /* namespace rg */


#endif /* ifndef RANGE_HPP_INCLUDED */
