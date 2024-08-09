# Competitive Programming Library

The cp library whose primary users are jonathanxia, kxia1729, and WyattWismer.

Project list:
* Tree shaker to reduce submission sizes
* Build out more of the lib/geo subpackage

# Constant Factors

Here are some notes about the CF server's constant factors. Everything is quoted
as `ms/1 mil ops`.

* Construction of vl(2): 100ms
* push_back(ll): 10ms
* DfsTree Constructor: 200ms
* Simple dfs w/ lambda: 60ms
* Constructing vector(1mil): 2.3ms
* Addition on vector access (close by): 1.4ms
* Multiply on vector access (close by): 1.4ms
* Division on vector access (close by): 11.2ms
* Addition on vector access (random access): 6 ms

## lib/nt.h
Each thing run 1mil times
* `nt::get_digits(1bil): 100ms` 
* `nt::sum_digits(1bil): 20ms`