# Example
```c++
for (auto& i : rg::range(1, 19, 3))
{
    std::cout << i << ' ';
}
```
Translates to:
```c++
rg::range<int>&& __range1 = rg::range<>(1, 19, 3);
rg::detail::range_iter<int> __begin1 = __range1.begin();
rg::detail::empty __end1 = __range1.end();
for (; __begin1.operator!=(detail::empty(__end1)); __begin1.operator++())
{
    int& i = __begin1.operator*();
    std::operator<<(std::cout.operator<<(i), ' ');
}
```
Output:
```c++
1 4 7 10 13 16
```