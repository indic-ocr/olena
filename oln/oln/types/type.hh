// Copyright (C) 2001, 2002  EPITA Research and Development Laboratory
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

#ifndef OLENA_VALUE_TYPE_HH
# define OLENA_VALUE_TYPE_HH

namespace type {

  // Static hierarchy tool
  template <class Self>
  class any_type
  {
  public:
    Self& self() { return static_cast<Self&>(*this); }
    const Self& self() const { return static_cast<const Self&>(*this); }
  };

  // classes used to disambiguate overloading

  template <class T>
  class any_class
  {
  public:
    any_class(T& t) : _target(t) {}

    T& self() { return _target; }

  private:
    T& _target;
  };

  template <class T>
  class any_const_class
  {
  public:
    any_const_class(const T& t) : _target(t) {}
      
    const T& self() const { return _target; }

  private:
    const T& _target;
  };

} // end of namespace type

#endif // ndef OLENA_VALUE_TYPE_HH
