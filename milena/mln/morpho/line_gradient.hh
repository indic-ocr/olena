// Copyright (C) 2008 EPITA Research and Development Laboratory
//
// This file is part of the Olena Library.  This library is free
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

#ifndef MLN_MORPHO_LINE_GRADIENT_HH
# define MLN_MORPHO_LINE_GRADIENT_HH

/// \file mln/morpho/line_gradient.hh
/// \brief Conversions to mln::line_graph_image.

# include <map>
# include <vector>

# include <mln/core/image2d.hh>
# include <mln/core/line_graph_image.hh>

// FIXME: Generalize to other (input) images as well (image1d,
// image3d, etc.).

namespace mln
{

  namespace morpho
  {

    /// \brief Create a line graph image representing the gradient
    /// norm of a mln::image2d.
    /* FIXME: Currently, the adjacency is set to 4-c and cannot be
       changed.  */
    template <typename T>
    mln::line_graph_image<mln::point2d, T>
    line_gradient(const mln::image2d<T>& ima);


# ifndef MLN_INCLUDE_ONLY

    template <typename T>
    mln::line_graph_image<mln::point2d, T>
    line_gradient(const mln::image2d<T>& ima)
    {
      // FIXME: Precondition: Ensure the image is scalar.
      typedef T value_t;

      util::graph<mln::point2d> g;

      // Points.
      /* FIXME: The need for such a structure during the conversion
	 exhibits the lack of a service from util::graph (or a another,
	 missing tool) regarding the retrieval of nodes' ids from
	 points.  */
      std::map<mln::point2d, util::node_id> points;
      util::node_id id = 0;

      // Nodes.
      std::vector<value_t> node_values;
      mln_fwd_piter(image2d<value_t>) p(ima.domain());
      for_all (p)
      {
	g.add_node (p);
	node_values.push_back (ima(p));
	/* FIXME: ``Guessing'' the id of the point just being inserted
	   is bad.  util:graph<N,E>::add_node should return this
	   id.  */
	points[p] = id;
	++id;
      }

      // Edges.
      // FIXME: The creation of this window should be generic.
      window2d next_c4_win;
      next_c4_win.insert(0, 1).insert(1, 0);
      std::vector<value_t> edge_values;
      mln_fwd_qiter_(window2d) q(next_c4_win, p); 
      for_all (p)
	for_all (q)
	if (ima.has(q))
	  {
	    g.add_edge(points[p], points[q]);
	    // The computed value is a norm of the gradient between P and Q.
	    edge_values.push_back(math::abs(ima(p) - ima(q)));
	  }

      // Line graph point set.
      p_line_graph<mln::point2d> plg(g);

      // Line graph image.
      typedef line_graph_image<mln::point2d, value_t> ima_t;
      ima_t lg_ima(plg, node_values, edge_values);
      return lg_ima;
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::morpho

} // end of namespace mln


#endif // ! MLN_MORPHO_LINE_GRADIENT_HH
