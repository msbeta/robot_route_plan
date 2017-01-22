#include <iostream>

#include <CGAL/Cartesian.h>
#include <CGAL/Quotient.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_observer.h>

#include "trapezoid.h"

typedef CGAL::Quotient<CGAL::MP_Float>                          Number_type;
typedef CGAL::Simple_cartesian<Number_type>                     Kernel;
typedef CGAL::Arr_segment_traits_2<Kernel>                      Traits_2;
typedef Traits_2::Point_2                                       Point_2;
typedef CGAL::Arrangement_2<Traits_2>                           Arrangement_2;

template <class Arrangement_>
void construct_segments_arr(Arrangement_& arr)
{
  typedef Arrangement_                                Arrangement_2;
  typedef typename Arrangement_2::Point_2             Point_2;
  typedef typename Arrangement_2::X_monotone_curve_2  Segment_2;
  typedef typename Arrangement_2::Halfedge_handle     Halfedge_handle;

  Point_2   b0(0, 0), b1(0, 5), b2(6, 5), b3(6, 0);
  Segment_2 l1(b0, b1), l2(b1, b2), l3(b2, b3), l4(b3, b0);

  Point_2    p1(0,3), p2(2,5), p3(4,5), p4(6,3), p5(3,0);
  Segment_2  s1(p1, p2), s2(p2, p3), s3(p3, p4), s4(p4, p5), s5(p5, p1);

  // arr.insert_in_face_interior(p0, arr.unbounded_face());
  // insert(arr, l1);
  // insert(arr, l2);
  // insert(arr, l3);
  // insert(arr, l4);

  // insert(arr, s1);
  // insert(arr, s2);
  // insert(arr, s3);
  // insert(arr, s4);
  // insert(arr, s5);

  Halfedge_handle e1 = arr.insert_in_face_interior(s1, arr.unbounded_face());
  Halfedge_handle e2 = arr.insert_from_left_vertex(s2, e1->target());
  Halfedge_handle e3 = arr.insert_from_left_vertex(s3, e2->target());
  Halfedge_handle e4 = arr.insert_from_right_vertex(s4, e3->target());
  arr.insert_at_vertices(s5, e4->target(), e1->source());
}

int main()
{
   // Construct the arrangement.
  Arrangement_2    arr;
  construct_segments_arr(arr);

  CGAL::Trapezoid<Arrangement_2> trapezoid_map(arr);

  trapezoid_map.print_dag();
  return 0;
}
