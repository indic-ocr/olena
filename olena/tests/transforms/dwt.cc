#include <oln/basics1d.hh>
#include <oln/basics2d.hh>
#include <oln/basics3d.hh>
#include <oln/level/compare.hh>
#include <oln/transforms/dwt.hh>
#include <oln/transforms/wavelet_coeffs.hh>

#include <ntg/all.hh>

#include <cstdlib>

#include "check.hh"
#include "data.hh"

#define CHECK(Condition)			\
    if (Condition)				\
      std::cout << "OK" << std::endl;		\
    else					\
      {						\
	std::cout << "FAIL" << std::endl;	\
	fail = true;				\
      }

using namespace oln;
using namespace ntg;
using namespace transforms;

Wavelet_coeffs_definition(daub4_test, float_d, 4)
{
  const float_d sqrt_3 = sqrt(3);
  const float_d denom = 4 * sqrt(2);

  Wavelet_coeffs_begin
    (1 + sqrt_3)/denom,
    (3 + sqrt_3)/denom,
    (3 - sqrt_3)/denom,
    (1 - sqrt_3)/denom
  Wavelet_coeffs_end
};

bool
check()
{
  bool fail = false;

  // 1D tests

  image1d<int_u16> vec1(4096);
  image1d<int_u16>::iter_type it1(vec1);
  for_all(it1)
    vec1[it1] = std::rand() / 10000000;

  dwt<image1d<int_u16>, daub4_test> wave1d(vec1);

  image1d<float_d> vec2 = wave1d.transform(dwt_std, true);

  image1d<int_u16> vec3 = wave1d.transform_inv<int_u16>();

  std::cout << "Test: Image1D == F-1(F(Image1D)) ... " << std::flush;
  CHECK (level::is_equal(vec1, vec3));

  // 2D tests

  image2d<int_u8> im1(rdata("lena.pgm"));

  dwt<image2d<int_u8>, coiflet6> wave2d(im1);

  image2d<float_d> im2 = wave2d.transform(dwt_std, true, 4);

  image2d<int_u8> im3 =
    wave2d.transform_inv<int_u8>();

  io::save(im3, "dwt_copy.pgm");

  std::cout << "Test: Image2D == F-1(F(Image2D)) ... " << std::flush;
  CHECK (level::is_equal(im1, im3));

  image2d<ntg::int_u<8, saturate> > out(im2.size());
  image2d<float_d>::iter_type it2(im2);
  for_all(it2)
    out[it2] = im2[it2];

  io::save(out, "dwt_trans_std.pgm");

  im2 = wave2d.transform(dwt_non_std, true, 4);

  for_all(it2)
    out[it2] = im2[it2];

  io::save(out, "dwt_trans_non_std.pgm");

  im2 = wave2d.transform(dwt_non_std, false, 3);
  for_all(it2)
    if (fabs(im2[it2]) < 42)
      if (im2[it2] != 0)
	im2[it2] = 0;

  out = wave2d.transform_inv<ntg::int_u<8, saturate> >();

  io::save(out, "dwt_compressed.pgm");

  // 3D tests

  image3d<int_u32> cube1(64, 64, 64);
  image3d<int_u32>::iter_type it3(cube1);
  for_all(it3)
    cube1[it3] = std::rand();

  dwt<image3d<int_u32>, haar> wave3d(cube1);

  image3d<float_d> cube2 = wave3d.transform(dwt_non_std, true, 1);
  image3d<int_u32> cube3 = wave3d.transform_inv<int_u32>();

  std::cout << "Test: Image3D == F-1(F(Image3D)) ... " << std::flush;
  CHECK (level::is_equal(cube1, cube3));

  return fail;
}
