// Copyright 2001  EPITA Research and Development Laboratory
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

#ifndef OLENA_CORE_BKD_ITER1D_HH
# define OLENA_CORE_BKD_ITER1D_HH

# include "core/internal/iter1d.hh"

namespace oln {

  class bkd_iter1d : public internal::_iter1d<bkd_iter1d>
  {
  public:
    typedef type::bottom inferior;
    typedef internal::_iter1d<bkd_iter1d> super;

    enum { dim = 1 };
    typedef point1d point;

    template<class T>
    bkd_iter1d(const image1d<T>& ima) :
      super(ima.size())
    {
    }

    template<class U> U operator=(U u) { return super::operator=(u); }

    void _goto_begin()
    {
      _p.col() = _ncols - 1;
    }

    void _goto_end()
    {
      _p.col() = -1;
    }

    bool _is_at_end() const
    {
      return _p.col() == -1;
    }

    void _goto_next()
    {
      --_p.col();
    }

    static std::string name() { return "bkd_iter1d"; }

  };

} // end of oln

#endif // ! OLENA_CORE_BKD_ITER1D_HH
