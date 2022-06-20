# Example
```c++
for (auto i : rg::range(1, 19.3, 3.2))
{
    std::cout << i << ' ';
}
```
Translates to:
```c++
rg::range<int, double, double>&& __range1 = rg::range<int, double, double>(1, 19.3, 3.2);
rg::detail::range_begin_type<int, double, double> __begin1 = __range1.begin();
rg::detail::range_end_type __end1 = __range1.end();
for (; __begin1.operator!=(__end1); __begin1.operator++())
{
    double i = __begin1.operator*();
    std::operator<<(std::cout.operator<<(i), ' ');
}
```
Output:
```c++
1 4.2 7.4 10.6 13.8 17
```
