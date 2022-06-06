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
                inline constexpr auto less(T a, T b)
                {
                        return a < b;
                }


                template <typename T>
                inline constexpr auto greater(T a, T b)
                {
                        return a > b;
                }


                template <typename T>
                class range_iter
                {
                public:


                        range_iter() = delete;


                        constexpr range_iter(T n, T to, T step)
                                : m_n{n}
                                , m_to{to}
                                , m_step{step}
                                , m_cmp{n < to ? &less<T> : &greater<T>}
                        {

                        }


                        constexpr decltype(auto) operator++()
                        {
                                m_n += m_step;
                                return *this;
                        }


                        constexpr auto operator++(int)
                        {
                                auto buf = *this;
                                this->operator++();
                                return buf;
                        }


                   	constexpr auto operator!=(empty) const
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


                constexpr explicit range(T from, T to, T step = 1)
                        : m_from{from}
                        , m_to{to}
                        , m_step{step}
                {
                        // results in an infinite loop if from < to and step < 0 or if from > to and step > 0
                }
        

                constexpr auto begin() const -> detail::range_iter<T>
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
