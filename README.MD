# Example
```c++
for (auto i : rg::range(1, 19.3, 3.2)) // decltype(i) == int (type of the first param)
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
for (auto i : rg::range<double>(1, 19.3, 3.2)) // decltype(i) == double
{
    std::cout << i << ' ';
}
```
Output:
```c++
1 4.2 7.4 10.6 13.8 17
```
