#ifndef RANGE_HPP_INCLUDED
#define RANGE_HPP_INCLUDED


namespace rg
{


        namespace detail 
        {


                struct empty
                {

                };


                template <typename T>
                inline constexpr bool less(T a, T b) noexcept
                {
                        return a < b;
                }


                template <typename T>
                inline constexpr bool greater(T a, T b) noexcept
                {
                        return a > b;
                }


                template <typename T>
                class range_iter
                {
                public:


                        range_iter() = delete;


                        constexpr range_iter(T n, T to, T step) noexcept
                                : m_n{n}
                                , m_to{to}
                                , m_step{step}
                                , m_cmp{n < to ? &less<T> : &greater<T>}
                        {

                        }


                        constexpr decltype(auto) operator++() noexcept
                        {
                                m_n += m_step;
                                return *this;
                        }


                        constexpr auto operator++(int) noexcept
                        {
                                auto buf = *this;
                                this->operator++();
                                return buf;
                        }


                   	constexpr auto operator!=(empty) const noexcept
                        {
                                return m_cmp(m_n, m_to);
                        }


                        constexpr auto operator*() noexcept -> T&
                        {
                                return m_n;
                        }


                private:


                        T m_n,
                          m_to,
                          m_step;


                        bool (*m_cmp)(T, T);


                };


        } /* namespace detail */


        template <typename T = int>
        class range
        {
        public:


                range() = delete;


                constexpr explicit range(T from, T to, T step = 1) noexcept
                        : m_from{from}
                        , m_to{to}
                        , m_step{step}
                {
                        // results in an infinite loop if from < to and step < 0 or if from > to and step > 0
                }
        

                constexpr auto begin() const noexcept -> detail::range_iter<T>
                {
                        return
                                {
                                        m_from,
                                        m_to,
                                        m_step
                                };
                }


                constexpr auto end() const noexcept -> detail::empty
                {
                        return
                                {

                                };
                }


        private:
        

            T m_from,
              m_to,
              m_step;


        };


} /* namespace rg */


#endif /* ifndef RANGE_HPP_INCLUDED */