#include <oln/basics2d.hh>
#include <oln/convol/fast_gaussian.hh>

using namespace oln;
using namespace ntg;

int main(void)
{
  image2d<int_u8> lena = load(IMGDIR "/lena.pgm");

  save(convol::fast::gaussian(lena, float_d(0.50f)),
       "lena-gau.pgm");
  save(convol::fast::gaussian_derivative(lena, float_d(0.50f)),
       "lena-gd1.pgm");
  save(convol::fast::gaussian_second_derivative(lena, float_d(0.50f)),
       "lena-gd2.pgm");

}
