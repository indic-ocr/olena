// Copyright (C) 2005  EPITA Research and Development Laboratory
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

#ifndef OLN_IO_READ_IMAGE_2D_PNM_HH
# define OLN_IO_READ_IMAGE_2D_PNM_HH

# include <iostream>
# include <string>

# include <mlc/box.hh>

# include <ntg/core/macros.hh>
# include <ntg/real/int_u8.hh>
# include <ntg/real/integer.hh>
# include <ntg/enum/enum.hh>
# include <ntg/color/color.hh>

# include <oln/core/2d/image2d.hh>
# include <oln/core/abstract/op.hh>

# include <oln/io/utils.hh>


namespace oln {

  template <typename I>
  struct image2d;

  // fwd decl
  namespace io {
    namespace impl {
      template <typename I> struct read_image_2d_raw;
    }
  }

  // category
  template <typename I>
  struct set_category < io::impl::read_image_2d_raw<I> >
  {
    typedef category::image ret;
  };

  // super_type
  template <typename I>
  struct set_super_type < io::impl::read_image_2d_raw<I> >
  {
    typedef abstract::op<I, io::impl::read_image_2d_raw<I> > ret;
  };


  namespace io {

    namespace impl {

      template <typename I>
      struct read_image_2d_raw :
	public oln::abstract::op<I, read_image_2d_raw<I> >
      {

	typedef oln::abstract::op<I, read_image_2d_raw<I> > super_type;
	typedef oln_type_of(I, value) value_type;
	typedef ntg_io_type(value_type) io_type;

	mlc::box<I> image_;
	std::istream& istr_;
	internal::pnm_info& info_;

	read_image_2d_raw(I& image,
			  std::istream &istr,
			  internal::pnm_info &info) :
	  super_type(image),
	  image_(image),
	  istr_(istr),
	  info_(info)
	{}


	read_image_2d_raw<I>& output(I& output)
	{
	  output = *image_;
	  return *this;
	}

	void impl_run()
	{
	  value_type c;
	  point2d p;
	  oln::image2d<value_type>  tmp(info_.rows, info_.cols);

	  if (info_.max_val > ntg_max_val(value_type))
	    {
	      std::cerr << "Can't load image, data type is not large enough"
			<< std::endl;
	      return;
	    }

	  for (p.row() = 0; p.row() < info_.rows && !istr_.eof(); ++p.row())
	    for (p.col() = 0; p.col() < info_.cols && !istr_.eof(); ++p.col())
	      {
		read_value_type(c);
		tmp[p] = c;
	      }
	  *image_ = tmp;
	}

	void read_value_type(ntg::integer<value_type> &c)
	{
	  io_type v;
	  istr_.read(&v, sizeof (io_type));
	  c = v;
	}

	void read_value_type(ntg::color<value_type> &c)
	{
	  io_type v;

	  for (unsigned i = 0; i < ntg_depth(value_type); i++)
	    {
	      istr_.read(&v, sizeof (v));
	      c[i] = v;
	    }
	}

	void read_value_type(ntg::enum_value<value_type> &c)
	{
	  static io_type v;
	  static int offset = -1;

	  if (offset == -1)
	    {
	      istr_.read((char *)(&v), sizeof (v));
	      offset = 7;
	    }
	  if ((int)(v & (1<<offset--)) == 0)
	    c = 0;
	  else
	    c = 1;
	}
      };



      template <typename I>
      void read(abstract::image2d<I>& ima,
		std::istream& istr,
		internal::pnm_info info)
      {
	read_image_2d_raw<I> tmp(ima.exact(), istr, info);
	tmp.run();
	tmp.output(ima.exact());
      }

    }

  }

}


#endif // ! OLN_IO_READ_IMAGE_2D_PNM_HH
