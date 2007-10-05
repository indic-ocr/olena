// Copyright (C) 2007 EPITA Research and Development Laboratory
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

#ifndef MLN_CORE_INTERNAL_CHECK_IMAGE_ALL_HH
# define MLN_CORE_INTERNAL_CHECK_IMAGE_ALL_HH

/*! \file mln/core/internal/check/image_all.hh
 *
 * \brief File that includes all image-related internal checks.
 */


# include <mln/core/internal/check/image_fastest.hh>
// ...


namespace mln
{

  namespace internal
  {

    /*! Namespace of all image-related internal checks.
     */
    namespace check
    {

      template <typename E>
      struct image_all_
	:
	public image_fastest_< E, typename mlc_equal(mln_trait_image_speed(E),
						     trait::image::speed::fastest)::eval >
        // , ...
      {
      };

    } // end of namespace mln::internal::check

  } // end of namespace mln::internal

} // end of namespace mln


#endif // ! MLN_CORE_INTERNAL_CHECK_IMAGE_ALL_HH
