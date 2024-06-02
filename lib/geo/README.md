# Geometry

This is the geometry documentation for our programming library.

Basic geometric objects, `Point`, `Line`, `Segment`, `Circle`, and `Polygon` are defined inside
the `base` subpackage. If you want to just import all of these in one swoop you can import the `lib/geo/basic.h` file.

## Base class types

In the implementation of all of these objects, we aim to be *type consistent*. This means that
you can have `Point<ll>`, `Point<long double>`, or even `Point<MI>`. In general, you can have
`Point<T>`. Now, Lines, Segments, Circles, and Polygons will always be with respect to the same
type `T`. So, you can construct a `Line<double>(Point<double> p1, Point<double> p2)`, for
example. We try very hard to make sure that if we are operating in type `T`, we stay in type `T`.

For instance, this makes it possible to find the area of a `Polygon<MI>`!

Roughly, there are three types of `T` that can be used. You can have
* **Ring**: such as `ll`, `int`, and other integer types that do not have proper division.
* **Field**: Such as `double`, `long double`, and `MI`.
* **Real**: a continuous real type, such as `double` and `long double`.

A lot of geometric objects can actually work with Rings just fine. You can add Points, form polygons,
and make Lines with them. However, some concepts must go to the reals, such as perimeter and distance.
To designate the `REAL` type, we define the typedef `REAL` at the top of `point.h`. The default is
`long double`. This means that if you call `Point<T>.dist()` you will always get type `REAL`,
regardless of `T`.

Another note is that intersections fail to work when you do not have a Field type. For instance,
you can ask for the intersection of two lines in `ll` space, but the answer might be
some rational point. However, line intersection interestingly still works over `MI`.
