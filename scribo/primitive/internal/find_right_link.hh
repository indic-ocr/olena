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

#ifndef SCRIBO_PRIMITIVE_INTERNAL_FIND_RIGHT_LINK_HH
# define SCRIBO_PRIMITIVE_INTERNAL_FIND_RIGHT_LINK_HH

/// \file
///
/// Find the right neighbor of a line of text if exists.
///
/// \todo To be deleted.

# include <mln/core/concept/image.hh>

# include <mln/math/abs.hh>

# include <mln/util/array.hh>
# include <mln/util/couple.hh>

# include <scribo/core/object_image.hh>
# include <scribo/primitive/internal/update_link_array.hh>
# include <scribo/primitive/internal/is_invalid_link.hh>

//FIXME: not generic.
# include <mln/core/alias/dpoint2d.hh>

namespace scribo
{

  namespace primitive
  {

    namespace internal
    {

      /// Find the right neighbor of a line of text if exists.
      ///
      /// \param objects An image of objects.
      /// \param right_link The right neighbors.
      /// \param current_comp A text line id.
      /// \param dmax The maximum lookup distance.
      /// \param c The lookup start point.
      //
      template <typename L>
      mln::util::couple<bool, mln_site(L)>
      find_right_link(const object_image(L)& objects,
		     mln::util::array<unsigned>& right_link,
		     unsigned current_comp,
		     float dmax,
		     const mln_site(L)& c);


# ifndef MLN_INCLUDE_ONLY

      template <typename L>
      mln::util::couple<bool, mln_site(L)>
      find_right_link(const object_image(L)& objects,
		     mln::util::array<unsigned>& right_link,
		     unsigned current_comp,
		     float dmax,
		     const mln_site(L)& c)
      {
	/// FIXME: the following code is not generic...
	/// First site on the right of the central site
	mln_site(L) p = c + mln::right;

	while (is_invalid_link(objects, right_link, p,
			       current_comp, c, dmax))
	  ++p.col();

	bool
	  b = update_link_array(objects, right_link, p, c, current_comp, dmax);

	return mln::make::couple(b, p);
      }

# endif // MLN_INCLUDE_ONLY

      } // end of namespace scribo::primitive::internal

  } // end of namespace scribo::primitive

} // end of namespace scribo


#endif // ! SCRIBO_PRIMITIVE_INTERNAL_FIND_RIGHT_LINK_HH