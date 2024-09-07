# acsegtree

This module defines some common use-cases for the atcoder lazy segment tree. Technically everything
can just directly use the `atcoder::lazy_segtree`. But we define very common use cases here, so that we
do not have to reimplement them each time.

The convention shall be the following:
* The filename will be `lazy_<lazy_op>_<query_op>.h`. For example, `lazy_assign_sum.h` means it supports
range assignment and sum queries.
* Within each file, a namespace of the same name will be used.
* Within this namespace, include the implementation exactly how you would if you were writing the segtree
from scratch
* Then include this line: `using LazySegTree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;`

For the usage, people can then just construct the segtree as
```
lazy_assign_sum::LazySegTree seg(n);
```