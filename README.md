# Competitive Programming Library

The cp library whose primary users are jonathanxia, kxia1729, and WyattWismer.

Project list:
* Tree shaker to reduce submission sizes
* Build out more of the lib/geo subpackage

# Constant Factors

Here are some notes about the CF server's constant factors. Everything is quoted
as `ms/1 mil ops`.

* vec.push_back(vl(2)): 100ms
* vec.push_back(ll): 10ms
* DfsTree(1mil node tree): 200ms
* 1mil recursive func calls: 60ms
* Constructing vector(1mil): 2.3ms
* a[i] += a[i - 1] + a[i - 2]: 1.4ms
* a[i] *= a[i - 1] * a[i - 2]: 1.4ms
* a[i] = a[i - 1] / a[i - 2]: 11.2ms
* a[rand] = a[rand] + a[rand]: 6 ms

Cache locality can make things about 4x slower

## lib/nt.h
Each thing run 1mil times
* `nt::get_digits(1bil, any base): 120ms` 
* `nt::sum_digits(1bil): 20ms`