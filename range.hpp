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

                
        } /* namespace detail */


        template <typename T = int>
        class range
        {
        public:


                range() = delete;


                constexpr explicit range(T from, T to, T step = 1)
                        : m_n{from}
                        , m_to{to}
                        , m_step{step}
                        , m_cmp{from < to ? &detail::less<T> : &detail::greater<T>}
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


                constexpr auto operator!=(detail::empty) const
                {
                        return m_cmp(m_n, m_to);
                }


                constexpr auto& operator*() noexcept
                {
                        return m_n;
                }
        

                constexpr decltype(auto) begin()
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


} /* namespace rg */


#endif /* ifndef RANGE_HPP_INCLUDED */
