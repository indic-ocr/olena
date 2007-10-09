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

#ifndef MLN_FUN_X2X_TRANSLATION_HH
# define MLN_FUN_X2X_TRANSLATION_HH

/*! \file mln/fun/x2x/translation.hh
 *
 * \brief FIXME.
 */

# include <mln/fun/x2x/bijective_tr.hh>
# include <mln/metal/vec.hh>
# include <mln/metal/mat.hh>


namespace mln
{

  namespace fun
  {

    namespace x2x
    {

      // FIXME: Doc!

      template <unsigned n, typename C>
      struct translation : public bijective_tr< translation<n,C> >
      {

	enum {dim = n};

	typedef metal::vec<n,C> result;
	typedef translation<n,C> invert;

	translation();
	translation(const metal::vec<n,C>& t);

	result operator()(const metal::vec<n,C>& v) const;
	invert inv() const;

	void set_t(const metal::vec<n,C>& t);

      protected:

	metal::vec<n,C> t_;
	metal::mat<n + 1,n + 1,C> m_;
      };


# ifndef MLN_INCLUDE_ONLY

      template <unsigned n, typename C>
      translation<n,C>::translation()
      {
	t_ = make::vec<n,C>(0);
	m_ = metal::mat<n+1,n+1,C>::Id;
      }

      template <unsigned n, typename C>
      translation<n,C>::translation(const metal::vec<n,C>& t)
	:t_(t)
      {
	m_ = metal::mat<n+1,n+1,C>::Id;
	for (unsigned i = 0; i < n; ++i)
	  m_(i,n) = t_[i];
      }

      template <unsigned n, typename C>
      metal::vec<n,C>
      translation<n,C>::operator()(const metal::vec<n,C>& v) const
      {
	typename translation::result res;
	// FIXME: Why not "res = v + t_;"?
	for (unsigned i = 0; i < n; ++i)
	  res[i] = v[i] + t_[i];
	return res;
      }

      template <unsigned n, typename C>
      translation<n,C>
      translation<n,C>::inv() const
      {
	typename translation::invert res(-t_);

	return res;
      }

      template <unsigned n, typename C>
      void
      translation<n,C>::set_t(const metal::vec<n,C>& t)
      {
	t_ = t;
	for (unsigned i = 0; i < n; ++i)
	  m_(i,n) = t_[i];
      }


# endif // ! MLN_INCLUDE_ONLY

    } // end of namespace mln::fun::x2x

  } // end of namespace mln::fun

} // end of namespace mln


#endif // ! MLN_FUN_X2X_TRANSLATION_HH
