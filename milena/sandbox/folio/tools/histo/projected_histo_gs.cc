// Copyright (C) 2007, 2008, 2009 EPITA Research and Development Laboratory (LRDE)
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


#include <mln/accu/math/sum.hh>
#include <mln/data/stretch.hh>
#include <mln/io/pgm/save.hh>
#include <mln/io/ppm/load.hh>
#include <mln/value/rgb8.hh>

#include "../../mln/histo/compute_histo_3d.hh"
#include "../../mln/histo/project_histo_3d.hh"

using namespace mln;
using namespace mln::value;


namespace mln
{

  struct take_log : Function_v2v< take_log >
  {
    typedef float result;
    float operator()(float f) const
    {
      mln_precondition(f > 0);
      return std::log(f + 1);
    }
  };

}


int
main(int argc, char** argv)
{
  // check arguments
  if (argc != 4)
  {
    std::cerr << "Usage:" << std::endl
	      << "  ./a.out ../../../../img/lena.ppm 51 out.pgm" << std::endl
	      << std::endl
	      << "BTW, the number is the closure's lambda." << std::endl;
    exit(1);
  }

  // build test image
  std::cout << "  => loading " << argv[1] << "..." << std::endl;
  image2d<value::rgb8> ima8;
  io::ppm::load(ima8, argv[1]);

  // build histo
  std::cout << "  => computing histogram..." << std::endl;
  image3d<unsigned> histo = histo::compute_histo_3d(ima8);

  // project it
  image2d<unsigned> proj =
    histo::project_histo<accu::math::sum<unsigned, unsigned>, 2>(histo);

  // compute output image
  image2d<value::int_u8> out = data::stretch( value::int_u8(),
					      data::transform( proj,
							       take_log() ) );
  // save output image
  std::cout << "  => saving " << argv[3] << "..." << std::endl;
  io::pgm::save(out, argv[3]);
}