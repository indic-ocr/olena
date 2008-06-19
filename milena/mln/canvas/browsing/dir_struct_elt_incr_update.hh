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

#ifndef MLN_CANVAS_BROWSING_DIR_STRUCT_ELT_INCR_UPDATE_HH
# define MLN_CANVAS_BROWSING_DIR_STRUCT_ELT_INCR_UPDATE_HH

/*! \file mln/canvas/browsing/dir_struct_elt_incr_update.hh
 *
 * \brief Directional browsing of an image with structuring element.
 */

# include <mln/core/concept/browsing.hh>
# include <mln/core/concept/image.hh>

namespace mln
{

  namespace canvas
  {

    namespace browsing
    {
      
      /*!
       * \brief Browsing in a certain direction with a segment.
       *
       * This canvas browse all the point of an image 'input' of type
       * 'I', of dimension 'dim' in the direction 'dir' with
       * considering weigh the 'length' nearest points.
       *
       * The functor should provide (In addition to 'input', 'I',
       * 'dim', 'dir' and 'length') six methods :
       *
       *   - init()         : Will be called at the beginning.
       *   - init_line()    : Will be called at the beginning of each
       *                      line.
       *   - add_point(q)   : Will be called for taking the new point
       *                      'q' into account.
       *   - remove_point(q): Will be called for untaking the new point
       *                      'q' into account.
       *   - next()         : Will be called at each point 'p' (also
       *                      provided by the functor).
       *   - final()        : Will be called at the end.
       *
       * F shall features : \n
       * { \n
       * --- as types: \n
       *   I; \n
       * --- as attributes: \n
       *   dim; \n
       *   dir; // and test dir < dim \n
       *   input; \n
       *   p; \n
       *   length; \n
       * --- as methods: \n
       *   void init(); \n
       *   void init_line(); \n
       *   void add_point(q) \n
       *   void remove_point(q) \n
       *   void next(); \n
       *   void final(); \n
       * } \n
       *
       */
      struct dir_struct_elt_incr_update_t : public Browsing< dir_struct_elt_incr_update_t >
      {
	template <typename F>
	void operator()(F& f) const;
      }

      dir_struct_elt_incr_update;

# ifndef MLN_INCLUDE_ONLY

      template <typename F>
      inline
      void
      dir_struct_elt_incr_update_t::operator()(F& f) const
      {
	trace::entering("canvas::browsing::dir_struct_elt_incr_update");
	mln_precondition(f.dir < f.dim);
	typedef typename F::I I;

	const mln_psite(I)
	  pmin = f.input.domain().pmin(),
	  pmax = f.input.domain().pmax();

	const mln_coord(I)
	  pmin_dir = pmin[f.dir],
	  pmax_dir = pmax[f.dir],
	  pmin_dir_plus_half_length = pmin_dir + f.length / 2,
	  pmax_dir_minus_half_length = pmax_dir - f.length / 2;

	mln_psite(I) pt, pu;
	
	typedef mln_coord(I)& coord_ref;
	coord_ref
	  ct = pt[f.dir],
	  cu = pu[f.dir],
	  p_dir = f.p[f.dir];

	f.p = pmin;
	
	trace::entering("canvas::browsing::dir_struct_elt_incr_update::init");
	f.init();
	trace::exiting("canvas::browsing::dir_struct_elt_incr_update::init");
	
	do
	{
	  pt = f.p;
	  pu = f.p;

	  trace::entering("canvas::browsing::dir_struct_elt_incr_update::init_line");
	  f.init_line();
	  trace::exiting("canvas::browsing::dir_struct_elt_incr_update::init_line");

	  // initialization (before first point of the line)
	  for (ct = pmin_dir; ct < pmin_dir_plus_half_length; ++ ct)
	    if (f.input.has(pt))
	    {
	      trace::entering("canvas::browsing::dir_struct_elt_incr_update::add_point");
	      f.add_point(pt);
	      trace::exiting("canvas::browsing::dir_struct_elt_incr_update::add_point");
	    }

	  // left columns (just take new points)
	  for (p_dir = pmin_dir; p_dir <= pmin_dir_plus_half_length; ++p_dir, ++ct)
	  {
	    if (f.input.has(pt))
	    {
	      trace::entering("canvas::browsing::dir_struct_elt_incr_update::add_point");
	      f.add_point(pt);
	      trace::exiting("canvas::browsing::dir_struct_elt_incr_update::add_point");
	    }
	    trace::entering("canvas::browsing::dir_struct_elt_incr_update::next");
	    f.next();
	    trace::exiting("canvas::browsing::dir_struct_elt_incr_update::next");
	  }

	  // middle columns (both take and untake)
	  cu = pmin_dir;
	  for (; p_dir <= pmax_dir_minus_half_length; ++cu, ++p_dir, ++ct)
	  {
	    if (f.input.has(pt))
	    {
	      trace::entering("canvas::browsing::dir_struct_elt_incr_update::add_point");
	      f.add_point(pt);
	      trace::exiting("canvas::browsing::dir_struct_elt_incr_update::add_point");
	    }
	    if (f.input.has(pu))
	    {
	      trace::entering("canvas::browsing::dir_struct_elt_incr_update::remove_point");
	      f.remove_point(pu);
	      trace::exiting("canvas::browsing::dir_struct_elt_incr_update::remove_point");
	    }
	    trace::entering("canvas::browsing::dir_struct_elt_incr_update::next");
	    f.next();
	    trace::exiting("canvas::browsing::dir_struct_elt_incr_update::next");
	  }

	  // right columns (now just untake old points)
	  for (; p_dir <= pmax_dir; ++cu, ++p_dir)
	  {
	    if (f.input.has(pu))
	    {
	      trace::entering("canvas::browsing::dir_struct_elt_incr_update::remove_point");
	      f.remove_point(pu);
	      trace::exiting("canvas::browsing::dir_struct_elt_incr_update::remove_point");
	    }
	    trace::entering("canvas::browsing::dir_struct_elt_incr_update::next");
	    f.next();
	    trace::exiting("canvas::browsing::dir_struct_elt_incr_update::next");
	  }

	  p_dir = pmin_dir;
	  
	  for (int c = F::dim - 1; c >= 0; --c)
	  {
	    if (c == int(f.dir))
	      continue;
	    if (f.p[c] != pmax[c])
	    {
	      ++f.p[c];
	      break;
	    }
	    f.p[c] = pmin[c];
	  }
	} while (f.p != pmin);

	trace::entering("canvas::browsing::dir_struct_elt_incr_update::final");
	f.final();
	trace::exiting("canvas::browsing::dir_struct_elt_incr_update::final");
	trace::exiting("canvas::browsing::dir_struct_elt_incr_update");
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::canvas::browsing

  } // end of namespace mln::canvas

} // end of namespace mln

#endif // ! MLN_CANVAS_BROWSING_DIR_STRUCT_ELT_INCR_UPDATE_HH
