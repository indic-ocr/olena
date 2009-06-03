// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory
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

#ifndef MLN_DRAW_BOX_HH
# define MLN_DRAW_BOX_HH

/*! \file mln/draw/box.hh
 *
 * \brief Draw a box in an image.
 */

# include <mln/core/concept/image.hh>
# include <mln/core/alias/box2d.hh>
# include <mln/data/paste.hh>
# include <mln/draw/line.hh>
# include <mln/pw/image.hh>
# include <mln/pw/cst.hh>


namespace mln
{

  namespace draw
  {

    /*! Draw a box at value \p v in image \p ima
     *
     * \param[in,out] ima The image to be drawn.
     * \param[in] b the boxto draw.
     * \param[in] v The value to assign to all drawn pixels.
     *
     * \pre \p ima has to be initialized.
     * \pre \p ima has \p beg.
     * \pre \p ima has \p end.
     *
     */
    template <typename I, typename B>
    void box(Image<I>& ima,
	     const Box<B>& b,
	     const mln_value(I)& v);


# ifndef MLN_INCLUDE_ONLY

    template <typename I, typename B>
    inline
    void box(Image<I>& ima,
	     const Box<B>& b,
	     const mln_value(I)& v)
    {
      mln_precondition(exact(ima).is_valid());

      mln_psite(I) pmin = exact(b).pmin();
      mln_psite(I) pmax = exact(b).pmax();

      mln_precondition(exact(ima).has(pmin) && exact(ima).has(pmax));

      mln_psite(I) p1 (pmin[0], pmin[1]);
      mln_psite(I) p2 (pmax[0], pmin[1]);
      mln_psite(I) p3 (pmin[0], pmax[1]);
      mln_psite(I) p4 (pmax[0], pmax[1]);

      draw::line (ima, p1, p2, v);
      draw::line (ima, p2, p4, v);
      draw::line (ima, p4, p3, v);
      draw::line (ima, p3, p1, v);
    }

# endif // ! MLN_INCLUDE_ONLY

  } // end of namespace mln::draw

} // end of namespace mln


#endif // ! MLN_DRAW_BOX_HH
