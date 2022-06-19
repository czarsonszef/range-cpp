#ifndef RANGE_HPP_INCLUDED
#define RANGE_HPP_INCLUDED


#include <type_traits>


namespace rg
{


        namespace detail 
        {
                

                template
                <
                        class,
                        class,
                        class
                >
                class range_iter;
                

                struct empty
                {

                };


                template <class T>
                constexpr auto less(T a, T b) noexcept
                {
                        return a < b;
                }


                template <class T>
                constexpr auto greater(T a, T b) noexcept
                {
                        return a > b;
                }

                
        } /* namespace detail */


        template
        <
                class T,
                class U,
                class W = int
        >
        class range
        {


                static_assert(
                        std::is_arithmetic_v<T> &&
                        std::is_arithmetic_v<U> &&
                        std::is_arithmetic_v<W>
                );


        public:


                using InnerType = std::common_type_t<T, U, W>;


                friend class detail::range_iter<T, U, W>;


                range() = delete;


                constexpr range(T from, U to, W step = 1) noexcept
                        : m_n
                          {
                                  static_cast<InnerType>
                                  (
                                        from
                                  )
                          }

                        , m_to
                          {
                                  static_cast<InnerType>
                                  (
                                        to
                                  )
                          }

                        , m_step
                          {
                                  static_cast<InnerType>
                                  (
                                        step
                                  )
                          }

                        , m_cmp
                          {
                                  from < to ?
                                        &detail::less<InnerType>
                                        :
                                        &detail::greater<InnerType>
                          }

                {

                        if ((m_n < m_to && m_step < 0) || (m_n > m_to && m_step > 0)) // if this check passes it means the range is incorrect, we don't want to enter the for loop
                        {
                                m_n = m_to;     // makes detail::range_iter::operator!= return false, the for loop won't be entered
                        }

                }


                constexpr auto begin() noexcept -> detail::range_iter<T, U, W>
                {
                        return *this;
                }


                constexpr auto end() const noexcept -> detail::empty
                {
                        return
                                {

                                };
                }
        

        private:


                InnerType m_n,
                          m_to,
                          m_step;


                bool (*m_cmp)(InnerType, InnerType);


        };


        template
        <
                class T,
                class U,
                class W
        >
        class detail::range_iter
        {
        public:


                range_iter() = delete;


                constexpr range_iter(range<T, U, W>& rng) noexcept
                        : m_rng
                          {
                                  rng
                          }
                {

                }


                constexpr auto operator++() noexcept -> decltype(auto)
                {
                        m_rng.m_n += m_rng.m_step;

                        return *this;
                }


                constexpr auto operator!=(detail::empty) const noexcept
                {
                        return m_rng.m_cmp(m_rng.m_n, m_rng.m_to);
                }


                constexpr auto operator*() noexcept
                {
                        return m_rng.m_n;
                }


        private:


                range<T, U, W>& m_rng;


        };


} /* namespace rg */


#endif /* ifndef RANGE_HPP_INCLUDED */
