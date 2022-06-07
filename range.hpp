#ifndef RANGE_HPP_INCLUDED
#define RANGE_HPP_INCLUDED


namespace rg
{


        namespace detail 
        {
                

                template <typename T>
                class range_iter;
                

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

                
        } /* namespace detail */


        template <typename T = int>
        class range
        {
        public:


                friend class detail::range_iter<T>;


                range() = delete;


                constexpr explicit range(T from, T to, T step = 1)
                        : m_n{from}
                        , m_to{to}
                        , m_step{step}
                        , m_cmp{from < to ? &detail::less<T> : &detail::greater<T>}
                {

                }

                constexpr auto begin() -> detail::range_iter<T>
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


                T m_n,
                  m_to,
                  m_step;


                bool (*m_cmp)(T, T);


        };

        template <typename T>
        class detail::range_iter
        {
        public:


                range_iter() = delete;


                constexpr range_iter(range<T>& rng)
                        : m_rng{rng}
                {

                }


                constexpr decltype(auto) operator++()
                {
                        m_rng.m_n += m_rng.m_step;
                        return *this;
                }


                constexpr auto operator++(int)
                {
                        auto buf = *this;
                        this->operator++();
                        return buf;
                }


                constexpr auto operator!=(detail::empty) const
                {
                        return m_rng.m_cmp(m_rng.m_n, m_rng.m_to);
                }


                constexpr auto& operator*() noexcept
                {
                        return m_rng.m_n;
                }


        private:


                range<T>& m_rng;


        };


} /* namespace rg */


#endif /* ifndef RANGE_HPP_INCLUDED */
