// Copyright (C) 2007, 2008, 2009 EPITA Research and Development
// Laboratory (LRDE)
//
// This file is part of the Milena Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License version 2 as published by the
// Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 51 Franklin Street, Fifth Floor,
// Boston, MA 02111-1307, USA.
//
// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

#ifndef MLN_CORE_IMAGE_GRAPH_ELT_WINDOW_HH
# define MLN_CORE_IMAGE_GRAPH_ELT_WINDOW_HH

/// \file mln/core/image/graph_elt_window.hh
///
/// Definition of the elementary ``window'' on a graph.

# include <mln/core/concept/window.hh>
# include <mln/core/internal/neighborhood_base.hh>
# include <mln/core/internal/graph_window_base.hh>
# include <mln/core/image/graph_window_piter.hh>


namespace mln
{

  /// Forward declaration
  template <typename G, typename S> class graph_elt_window;
  template <typename G, typename F> struct p_edges;
  template <typename G, typename F> struct p_vertices;


  namespace internal
  {

    template <typename G, typename S, typename E>
    struct neighborhood_impl<graph_elt_window<G,S>,E>
      : public neighborhood_extra_impl<graph_elt_window<G,S>,E>
    {
    };


    /// Default
    /// The given site set parameter is not supported yet!
    template <typename G, typename S>
    struct graph_window_iter_dispatch;

    template <typename G, typename F>
    struct graph_window_iter_dispatch<G, p_edges<G,F> >
    {
      typedef mln_edge_nbh_edge_fwd_iter(G) nbh_fwd_iter_;
      typedef mln_edge_nbh_edge_bkd_iter(G) nbh_bkd_iter_;
    };

    template <typename G, typename F>
    struct graph_window_iter_dispatch<G, p_vertices<G,F> >
    {
      typedef mln_vertex_nbh_vertex_fwd_iter(G) nbh_fwd_iter_;
      typedef mln_vertex_nbh_vertex_bkd_iter(G) nbh_bkd_iter_;
    };


  } // end of namespace mln::internal


  namespace trait
  {

    template <typename G, typename S>
    struct window_< mln::graph_elt_window<G,S> >
    {
      typedef trait::window::size::unknown       size;
      typedef trait::window::support::irregular  support;
      typedef trait::window::definition::varying definition;
    };

  } // end of namespace mln::trait


  /// Elementary window on graph class.
  /// \p G is the graph type.
  /// \p S is the image site set.
  template <typename G, typename S>
  class graph_elt_window
    : public graph_window_base<mln_result(S::fun_t),
			       graph_elt_window<G,S> >,
      public internal::graph_window_iter_dispatch<G,S>
  {
    typedef graph_elt_window<G,S> self_;
    typedef internal::graph_window_iter_dispatch<G,S> super_;

    typedef typename super_::nbh_fwd_iter_ nbh_fwd_iter_;
    typedef typename super_::nbh_bkd_iter_ nbh_bkd_iter_;

  public:
    /// Associated types.
    /// \{
    typedef S target;
    /// The type of psite corresponding to the window.
    typedef mln_psite(target) psite;

    /// Site_Iterator type to browse the psites of the window
    /// w.r.t. the ordering of vertices.
    typedef graph_window_piter<target,self_,nbh_fwd_iter_> fwd_qiter;

    /// Site_Iterator type to browse the psites of the window
    /// w.r.t. the reverse ordering of vertices.
    typedef graph_window_piter<target,self_,nbh_bkd_iter_> bkd_qiter;

    /// The default qiter type.
    typedef fwd_qiter qiter;
    /// \}

  };

} // end of namespace mln


#endif // ! MLN_CORE_IMAGE_GRAPH_ELT_WINDOW_HH
