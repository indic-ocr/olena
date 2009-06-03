// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_GRAPH_LABELING_HH
# define MLN_GRAPH_LABELING_HH

/// \file mln/graph/labeling.hh
///
/// Label a graph image.


# include <mln/core/concept/image.hh>
# include <mln/core/concept/neighborhood.hh>
# include <mln/labeling/blobs.hh>
# include <mln/metal/bexpr.hh>
# include <mln/metal/is_a.hh>


namespace mln
{

  namespace graph
  {


    /// Label graph components.
    /// Vertex with id 0, usuallly used to represent the background component,
    /// will be labeled with an id different from 0. Therefore, the labeling
    /// starts from 1.
    ///
    /// \param[in]     graph_image_ A graph image (\sa vertex_image,
    ///				    edge_image).
    /// \param[in]     nbh_	    A graph neighborhood.
    /// \param[in,out] nlabels	    The number of labels found.
    ///
    /// \return a Graph image of labels.
    //
    template <typename I, typename N, typename L>
    mln_ch_value(I,L)
    labeling(const Image<I>& graph_image_,
	     const Neighborhood<N>& nbh_, L& nlabels);



# ifndef MLN_INCLUDE_ONLY


    template <typename I, typename N, typename L>
    mln_ch_value(I,L)
    labeling(const Image<I>& graph_image_,
	     const Neighborhood<N>& nbh_, L& nlabels)
    {
      trace::entering("graph::labeling");

      const I& graph_image = exact(graph_image_);
      const N& nbh = exact(nbh_);

      mln_precondition(graph_image.is_valid());
      mln_precondition(nbh.is_valid());
      // FIXME: Be sure that's a graph image!
      // FIXME: Be sure that's a neighborhood on graph!

      mln_ch_value(I,bool) tmp;
      initialize(tmp, graph_image);
      data::fill(tmp, true);

      mln_ch_value(I,L) output = mln::labeling::blobs(tmp, nbh, nlabels);

      trace::exiting("graph::labeling");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY


  } // end of namespace mln::graph

} // end of namespace mln


#endif // ! MLN_GRAPH_LABELING_HH
