#ifndef INC_TRAPEZOID_H
#define INC_TRAPEZOID_H

#include <iostream>

#include <CGAL/Arr_observer.h>
#include <CGAL/Arr_point_location/Trapezoidal_decomposition_2.h>
#include <CGAL/Arr_point_location/Td_traits.h>

namespace CGAL//Route_Plan
{
template <typename Arrangement_>
class Trapezoid : public CGAL::Arr_observer<Arrangement_> {
public:
  typedef Arrangement_ Arrangement_on_surface_2;
  //type of traits adaptor
  typedef typename Arrangement_on_surface_2::Traits_adaptor_2		
                                                Traits_adaptor_2;
  //type of trapezoidal decomposition traits class
  typedef CGAL::Td_traits<Traits_adaptor_2, Arrangement_on_surface_2> 
                                                Td_traits;
  //type of trapezoidal decomposition class
  typedef CGAL::Trapezoidal_decomposition_2<Td_traits>    
                                                Trapezoidal_decomposition;

  //type of halfedge handle
  typedef typename Arrangement_on_surface_2::Halfedge_handle	
                                                Halfedge_handle;
  //type of halfedge const handle
  typedef typename Arrangement_on_surface_2::Halfedge_const_handle	
                                                Halfedge_const_handle;

  //type of edge const iterator
  typedef typename Arrangement_on_surface_2::Edge_const_iterator	
                                                Edge_const_iterator;

  typedef typename Trapezoidal_decomposition::Dag_node Dag_node;

  typedef typename Trapezoidal_decomposition::Td_map_item Td_map_item;
  typedef typename Trapezoidal_decomposition::Td_active_trapezoid Td_active_trapezoid;
  typedef typename Td_active_trapezoid::Vertex_const_handle Vertex_const_handle;

  typedef typename Trapezoidal_decomposition::bottom_he_visitor bottom_he_visitor;

public:
  /*! Constructor given an arrangement. */
  Trapezoid (const Arrangement_on_surface_2& arr, 
                           bool with_guarantees = true, 
                           double depth_thrs = CGAL_TD_DEFAULT_DEPTH_THRESHOLD, 
                           double size_thrs = CGAL_TD_DEFAULT_SIZE_THRESHOLD) :
    CGAL::Arr_observer<Arrangement_on_surface_2> 
              (const_cast<Arrangement_on_surface_2 &>(arr))
  {
    //m_traits = static_cast<const Traits_adaptor_2*> (arr.geometry_traits());
    td.set_with_guarantees(with_guarantees);
    td.init_arrangement_and_traits(&arr);
    td.depth_threshold(depth_thrs);
    td.size_threshold(size_thrs);
    _construct_td();
  }

  void print_dag() {
      //td.print_dag(std::cout);
      remove_trapezoid_in_polygon();
      }

  // 移除位于障碍物多边形内部的梯形左右边界
  void remove_trapezoid_in_polygon() {
      // 取出所有的梯形
      const Dag_node& dag_traverse_root =  td.dag_root();
      
      traverse_dag_recursive(dag_traverse_root, 0);
    }

  void traverse_dag_recursive(const Dag_node& curr, int depth) {
    //curr is the current pointer to node in the data structure
    //item holds the trapezoidal map item connected to curr.
    Td_map_item item = curr.get_data();
    if (td.get_traits().is_td_edge(item)) {
    } else {
        if (td.get_traits().is_td_trapezoid(item) && td.get_traits().is_active(item)) {
          std::cout << " TRAPEZOID \n";
          // 获取梯形图
          Td_active_trapezoid& trapezoid_item = boost::get<Td_active_trapezoid>(item);
          // 打印梯形的顶点
          if (!trapezoid_item.is_on_left_boundary()) {
            Vertex_const_handle left_vertex = trapezoid_item.left();
            std::cout << "left (" << left_vertex->point() << ")" << std::endl;
          }
          if (!trapezoid_item.is_on_right_boundary()) {
            Vertex_const_handle rigt_vertex = trapezoid_item.right();
            std::cout << "right (" << rigt_vertex->point() << ")" << std::endl;
          }
          if (!trapezoid_item.is_on_bottom_boundary()) {
            Halfedge_const_handle bottom_half_edge = trapezoid_item.bottom();
            std::cout << "bottom (" << bottom_half_edge->curve() << ")" << std::endl;
          }
          if (!trapezoid_item.is_on_top_boundary()) {
            Halfedge_const_handle top_halfedge = trapezoid_item.top();
            std::cout << "top (" << top_halfedge->curve() << ")" << std::endl;
          }
        }
    }

    if (!curr.left_child().is_null()) {
      traverse_dag_recursive(curr.left_child(), depth + 1);
    }

    if (!curr.right_child().is_null()) {
      traverse_dag_recursive(curr.right_child(), depth + 1);
    }
  }

protected:
  //type of trapezoidal decomposition class
  typedef Trapezoidal_decomposition             TD;
  TD  td;       // instance of trapezoidal decomposition

protected:

  /*! Construct the trapezoidal decomposition. */
  void _construct_td ()
  {
    td.clear();
 
    std::vector<Halfedge_const_handle> he_container; 
    Edge_const_iterator eit;
    Halfedge_const_handle he_cst;
    Arrangement_on_surface_2 *arr = this->arrangement();
    //collect the arrangement halfedges
    for (eit = arr->edges_begin(); eit != arr->edges_end(); ++eit)
    {
      he_cst = eit;
      he_container.push_back(he_cst);
    }
    //container insertion
    td.insert(he_container.begin(), he_container.end()); 
  }

};

}; // namespace Route_Plan

#endif //INC_TRAPEZOID_H