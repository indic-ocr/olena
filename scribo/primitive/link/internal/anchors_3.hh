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

#ifndef SCRIBO_PRIMITIVE_LINK_INTERNAL_ANCHORS_3_HH
# define SCRIBO_PRIMITIVE_LINK_INTERNAL_ANCHORS_3_HH

/// \file
///
/// Routine providing 3 anchors for neighbor seeking.

# include <mln/math/min.hh>

# include <scribo/core/object_image.hh>


namespace scribo
{

  namespace primitive
  {

    namespace link
    {

      namespace internal
      {

	/*! \brief Return the proper anchor used to find a neighbor.

	  This routine provides up to 3 different anchors.

	  \param[in] objects        An object image.
	  \param[in] mass_centers   Object mass centers.
	  \param[in] current_object An object id.
	  \param[in] anchor         The expected anchor.

	  Anchor can take one of the following values:
	  - 0, top anchor.
	  - 1, center anchor. It is the mass center.
	  - 2, bottom anchor.


	  Top and bottom anchors are respectively computed from the
	  bbox pmin and the bbox pmax, P.

	  Then the output anchor coordinates are computed as follows:

	  out.col = bbox.center.col

	  if object height, h, is lower than 30.
	   out.row = P.row + min(2, (h + 1) / 2 - 1)
	  else
	   out.row = P.row - min(10, h /10)

	 */
	template <typename L, typename P>
	mln_site(L)
	anchors_3(const object_image(L)& objects,
		  const mln::util::array<P>& mass_centers,
		  unsigned current_object, unsigned anchor);


# ifndef MLN_INCLUDE_ONLY

	template <typename L, typename P>
	mln_site(L)
	anchors_3(const object_image(L)& objects,
		  const mln::util::array<P>& mass_centers,
		  unsigned current_object, unsigned anchor)
	{
	  unsigned h = objects.bbox(current_object).pmax().row()
	               - objects.bbox(current_object).pmin().row();

	  mln_site(L) sp = objects.bbox(current_object).center();
	  def::coord r;

	  switch (anchor)
	  {
	    // Top
	    case 0:
	      if (h < 30)
		r = objects.bbox(current_object).pmin().row()
		  + math::min(2u, (h + 1) / 2 - 1);
	      else
		r = objects.bbox(current_object).pmin().row()
		  - math::min(10u, h /10);
	      break;


	      // Center
	    case 1:
	      return mass_centers(current_object);


	      // Bottom
	    case 2:
	      if (h < 30)
		r = objects.bbox(current_object).pmax().row()
		  + math::min(2u, (h + 1) / 2 - 1);
	      else
		r = objects.bbox(current_object).pmax().row()
		  - math::min(10u, h /10);
	      break;

	    default:
	      trace::warning("Non handled anchor");
	      mln_assertion(anchor > 2);
	  }

	  sp.row() = r;
	  return sp;
	}

# endif // ! MLN_INCLUDE_ONLY

      } // end of namespace scribo::primitive::link::internal

    } // end of namespace scribo::primitive::link

  } // end of namespace scribo::primitive

} // end of namespace scribo

#endif // ! SCRIBO_PRIMITIVE_LINK_INTERNAL_ANCHORS_3_HH