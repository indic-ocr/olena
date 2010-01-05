// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
//
// This file is part of Olena.
//
// Olena is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free
// Software Foundation, version 2 of the License.
//
// Olena is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Olena.  If not, see <http://www.gnu.org/licenses/>.
//
// As a special exception, you may use this file as part of a free
// software project without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to produce
// an executable, this file does not by itself cause the resulting
// executable to be covered by the GNU General Public License.  This
// exception does not however invalidate any other reasons why the
// executable file might be covered by the GNU General Public License.

#ifndef SCRIBO_FILTER_OBJECT_LINKS_BBOX_RATIO_HH
# define SCRIBO_FILTER_OBJECT_LINKS_BBOX_RATIO_HH

/// \file
///
/// Invalidate links between two objects with too different height or
/// width.


# include <mln/util/array.hh>

# include <scribo/core/macros.hh>
# include <scribo/core/object_links.hh>
# include <scribo/core/object_image.hh>

namespace scribo
{

  namespace filter
  {

    using namespace mln;

    /*! \brief Invalidate links between two objects with too different
        height or width.

	\param[in] objects   An object image.
	\param[in] links     Link objects information.
	\param[in] dim       The dimension to use to compare bbox length.
	\param[in] max_ratio The maximum length ratio of two linked
	                     bounding boxes.

	\result A filtered object link information.
    */
    template <typename L>
    object_links<L>
    object_links_bbox_ratio(const object_image(L)& objects,
			    const object_links<L>& links,
			    unsigned dim,
			    float max_ratio);


# ifndef MLN_INCLUDE_ONLY


    template <typename L>
    object_links<L>
    object_links_bbox_ratio(const object_image(L)& objects,
			    const object_links<L>& links,
			    unsigned dim,
			    float max_ratio)
    {
      trace::entering("scribo::filter::object_links_bbox_ratio");

      mln_precondition(objects.is_valid());
      mln_precondition(links.is_valid());

      object_links<L> output(links);
      for (unsigned i = 1; i < links.size(); ++i)
	if (links[i] != i)
	{
	  float
	    lmin = objects.bbox(i).pmax()[dim] - objects.bbox(i).pmin()[dim],
	    lmax = objects.bbox(links(i)).pmax()[dim]
	            - objects.bbox(links(i)).pmin()[dim];

	  if (lmin > lmax)
	    std::swap(lmin, lmax);

	  if ((lmax/ lmin) > max_ratio)
	    output(i) = i;
	}

      trace::exiting("scribo::filter::object_links_bbox_ratio");
      return output;
    }


# endif // ! MLN_INCLUDE_ONLY


  } // end of namespace scribo::filter

} // end of namespace scribo


#endif // ! SCRIBO_FILTER_OBJECT_LINKS_BBOX_RATIO_HH