// Copyright (C) 2011 EPITA Research and Development Laboratory (LRDE)
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

#ifndef APPS_BENCH_TRAITS_HH
# define APPS_BENCH_TRAITS_HH

# include <mln/core/image/image2d.hh>
# include <mln/metal/none.hh>

# include "apps/bench/static_window.hh"
# include "apps/bench/static_dpoints_pixter.hh"


// FIXME: Move this into mln/trait/ (and mln/core/image/?)
namespace mln
{

  namespace trait
  {

    // qixter

    template <typename T, typename D, unsigned n>
    struct fwd_qixter< image2d<T>, static_window<D, n> >
    {
      typedef static_dpoints_fwd_pixter< image2d<T>, static_window<D, n> > ret;
    };

    template <typename T, typename D, unsigned n>
    struct fwd_qixter< const image2d<T>, static_window<D, n> >
    {
      typedef static_dpoints_fwd_pixter< const image2d<T>, static_window<D, n> > ret;
    };

    template <typename T, typename D, unsigned n>
    struct bkd_qixter< image2d<T>, static_window<D, n> >
    {
      typedef static_dpoints_bkd_pixter< image2d<T>, static_window<D, n> > ret;
    };

    template <typename T, typename D, unsigned n>
    struct bkd_qixter< const image2d<T>, static_window<D, n> >
    {
      typedef static_dpoints_bkd_pixter< const image2d<T>, static_window<D, n> > ret;
    };

    // FIXME: Also handle mln::image1d<T> and mln::image3d<T>.


  } // end of namespace mln::trait

} // end of namespace mln

#endif // ! APPS_BENCH_TRAITS_HH
