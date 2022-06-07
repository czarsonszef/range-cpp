# Example
```c++
for (auto i : rg::range(1, 19.3, 3.0)) // decltype(i) == int (type of the first param)
{
    std::cout << i << ' ';
}
```
Translates to:
```c++
rg::range<int>&& __range1 = rg::range<int>(1, 19.3, 3.0);
rg::detail::range_iter<int> __begin1 = __range1.begin();
rg::detail::empty __end1 = __range1.end();
for (; __begin1.operator!=(detail::empty(__end1)); __begin1.operator++())
{
    int i = __begin1.operator*();
    std::operator<<(std::cout.operator<<(i), ' ');
}
```
Output:
```c++
1 4 7 10 13 16
```
# Example 2
```c++
const float f = 17.9;
const char c = 3;
const double d = -3.9;

for (auto i : rg::range<int>(f, c, d)) /* decltype(i) == int */
{
    std::cout << i << ' ';
}
```
Output:
```c++
17 14 11 8 5
```
# Example 3
```c++
for (auto i : rg::range<double>(4, 12, 3.3)) /* decltype(i) == double */
{
    std::cout << i << ' ';
}
```
Output:
```c++
4 7.3 10.6
```