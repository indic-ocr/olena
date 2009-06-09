// Copyright (C) 2007, 2008 EPITA Research and Development Laboratory (LRDE)
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

#ifndef MLN_CANVAS_BROWSING_HYPER_DIRECTIONAL_HH
# define MLN_CANVAS_BROWSING_HYPER_DIRECTIONAL_HH

/// \file
///
/// Hyper_Directional browsing of an image.

# include <mln/core/concept/browsing.hh>
# include <mln/core/concept/image.hh>

namespace mln
{

  namespace canvas
  {

    namespace browsing
    {

      /// Browsing in a certain direction.
      /*!
       * This canvas browse all the point of an image 'input' of type
       * 'I' and of dimension 'dim' in the direction 'dir'.
       *
       * The functor should provide (In addition to 'input', 'I',
       * 'dim' and 'dir') three methods :
       *
       *   - init() : Will be called at the beginning.
       *   - next() : Will be called at each point 'p' (also provided by
       *   the fonctor).
       *   - final(): Will be called at the end.
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
       * --- as methods: \n
       *   void init(); \n
       *   void next(); \n
       *   void final(); \n
       * } \n
       *
       */
      struct hyper_directional_t : public Browsing< hyper_directional_t >
      {
	template <typename F>
	void operator()(F& f) const;
      };

      extern const hyper_directional_t hyper_directional;

# ifndef MLN_INCLUDE_ONLY

      const hyper_directional_t hyper_directional;

      template <typename F>
      inline
      void
      hyper_directional_t::operator()(F& f) const
      {
	trace::entering("canvas::browsing::hyper_directional");
	mln_precondition(f.dir < f.dim);
	typedef typename F::I I;

	mln_psite(I)
	  pmin = f.input.domain().pmin(),
	  pmax = f.input.domain().pmax();

	f.p = pmin;

	f.init();

	do
	{
	  f.next();

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

	f.final();
	trace::exiting("canvas::browsing::hyper_directional");
      }

# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::canvas::browsing

  } // end of namespace mln::canvas

} // end of namespace mln

#endif // ! MLN_CANVAS_BROWSING_HYPER_DIRECTIONAL_HH
