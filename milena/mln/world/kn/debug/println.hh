// Copyright (C) 2012 EPITA Research and Development Laboratory (LRDE)
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

/// \file
///
/// \brief Display a Kn 2D image.

#ifndef MLN_WORLD_KN_DEBUG_PRINTLN_HH
# define MLN_WORLD_KN_DEBUG_PRINTLN_HH

# include <mln/core/concept/image.hh>
# include <mln/geom/min_row.hh>
# include <mln/geom/max_row.hh>
# include <mln/geom/min_col.hh>
# include <mln/geom/max_col.hh>
# include <mln/world/kn/face_dim.hh>
# include <mln/world/kn/is_1_face_horizontal.hh>

namespace mln
{

  namespace world
  {

    namespace kn
    {

      namespace debug
      {

        /// \brief Display a Kn 2D image.
	template <typename I, typename B>
	void println(const std::string& msg, const Image<I>& ima,
		     const Box<B>& bbox,
		     std::ostream& ostr = std::cout);

        /// \overload
	template <typename I>
	void println(const std::string& msg, const Image<I>& ima,
		     std::ostream& ostr = std::cout);


	/// \overload
	template <typename I>
	void println(const Image<I>& ima,
		     std::ostream& ostr = std::cout);

	/// \overload
	template <typename I, typename B>
	void println(const Image<I>& ima,
		     const Box<B>& bbox,
		     std::ostream& ostr = std::cout);


# ifndef MLN_INCLUDE_ONLY

	namespace internal
	{

	  template <typename P>
	  void display_dim(std::ostream& ostr, const P& p)
	  {
	    switch (face_dim(p))
	    {
	      case 0:
		ostr << " +";
		break;
	      case 1:
		ostr << (is_1_face_horizontal(p) ? " -" : " |");
		break;
	      case 2:
		ostr << " x";
		break;
	    }
	  }


	  template <typename I, typename B, typename F>
	  void println(const std::string& msg,
		       const Image<I>& ima_,
		       const Box<B>& bbox_,
		       std::ostream& ostr,
		       const F& display_dim)
	  {
	    const I& ima = exact(ima_);
	    const B& bbox = exact(bbox_);
	    mln_precondition(ima.is_valid());
	    mln_precondition(I::site::dim == 2);
	    mln_precondition(bbox.is_valid());

	    if (msg != "")
	      std::cout << msg << std::endl;
	    def::coord
	      min_row = geom::min_row(bbox), max_row = geom::max_row(bbox),
	      min_col = geom::min_col(bbox), max_col = geom::max_col(bbox);

	    // FIXME: not generic.
	    mln_site(I) p;
	    def::coord& row = p.row();
	    def::coord& col = p.col();

	    char bdr = '#';

	    for (col = min_col; col <= max_col + 2; ++col)
	      std::cout << bdr << ' ';
	    std::cout << std::endl;

	    for (row = min_row; row <= max_row; ++row)
	    {
	      std::cout << bdr;
	      for (col = min_col; col <= max_col; ++col)
		if (ima.domain().has(p) && ima(p))
		  display_dim(ostr, p);
		else
		  ostr << "  ";
	      std::cout << ' ' << bdr << std::endl;
	    }
	    for (col = min_col; col <= max_col + 2; ++col)
	      std::cout << bdr << ' ';
	    std::cout << std::endl
		      << std::endl;

	  };


	}// end of namespace mln::world::kn::debug::internal


	template <typename I, typename B>
	void println(const std::string& msg,
		     const Image<I>& ima_,
		     const Box<B>& bbox_,
		     std::ostream& ostr = std::cout)
	{
	  trace::entering("mln::world::kn::debug::println");

	  const I& ima = exact(ima_);
	  const B& bbox = exact(bbox_);
	  mln_precondition(ima.is_valid());
	  mln_precondition(I::site::dim == 2);
	  mln_precondition(bbox.is_valid());

	  typedef mln_site(I) P;
	  kn::debug::internal::println(msg, ima, bbox, ostr,
				       world::kn::debug::internal::display_dim<P>);

	  trace::exiting("mln::world::kn::debug::println");
	};

	template <typename I>
	void println(const std::string& msg,
		     const Image<I>& ima,
		     std::ostream& ostr = std::cout)
	{
	  mln_box(I) bbox = geom::bbox(ima);
	  println(msg, ima, bbox, ostr);
	}

	template <typename I>
	void println(const Image<I>& ima,
		     std::ostream& ostr = std::cout)
	{
	  mln_box(I) bbox = geom::bbox(ima);
	  println("", ima, bbox, ostr);
	}

	template <typename I, typename B>
	void println(const Image<I>& ima,
		     const Box<B>& bbox,
		     std::ostream& ostr = std::cout)
	{
	  println("", ima, bbox, ostr);
	}

# endif // ! MLN_INCLUDE_ONLY

      } // mln::world::kn::debug

    } // mln::world::kn

  } // mln::world

} // mln

#endif // ! MLN_WORLD_KN_DEBUG_PRINTLN_HH