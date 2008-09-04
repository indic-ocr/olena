#include "my_xyz.hh"
#include "rgb_to_xyz.hh"

#include <cmath>

#include <mln/core/image/image2d.hh>
#include <mln/value/rgb.hh>

#include <mln/io/ppm/load.hh>
#include <mln/io/ppm/save.hh>
#include <mln/math/round.hh>
#include <mln/level/transform.hh>

int main()
{
  using namespace mln;

  image2d<value::rgb8> lena;
  io::ppm::load(lena, "../../../img/lena.ppm");

  image2d< value::xyz_<float, float, float> > lena_hsi 
     = level::transform(lena,
                        fun::v2v::f_rgb_to_xyz_f_t());

//   image2d<value::rgb8> lena_rgb = level::transform(lena_hsi,
// 						   fun::v2v::f_xyz_to_rgb_3x8);
}

