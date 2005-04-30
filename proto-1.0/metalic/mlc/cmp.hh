// Copyright (C) 2001, 2002, 2003, 2004, 2005 EPITA Research and Development Laboratory
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
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.
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

#ifndef METALIC_CMP_HH
# define METALIC_CMP_HH

# include <mlc/bool.hh>
# include <mlc/types.hh>


/// Macros mlc_eq and mlc_neq.
# define mlc_eq(T1, T2) mlc::eq<T1, T2>
# define mlc_neq(T1, T2) mlc::neq<T1, T2>

# define mlc_is_found(T) mlc::is_found<(T)>
# define mlc_is_not_found(T) mlc::is_not_found<(T)>


namespace mlc
{

  /// Equality test between a couple of types.

  template <typename T1, typename T2>
  struct eq : public value<bool, false>
  {
  };

  template <typename T>
  struct eq <T, T> : public value<bool, true>
  {
  };

  /// Inequality test between a couple of types.

  template <typename T1, typename T2>
  struct neq : public value<bool, true>
  {
  };

  template <typename T>
  struct neq <T, T> : public value<bool, false>
  {
  };

  /// Tests is_found and is_not_found (sugar) upon a type.

  template <typename T>
  struct is_found : public neq <T, internal::not_found>
  {
  };

  template <typename T>
  struct is_not_found : public eq <T, internal::not_found>
  {
  };



  template <typename T>
  struct is_ok : public and_< and_< neq<T, internal::not_found>,
				    neq<T, internal::not_ok> >,
			      neq<T, undefined_type> >
  {
  };


} // end of namespace mlc


#endif // ! METALIC_CMP_HH
