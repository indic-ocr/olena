// EDOC == Erosion Dilation Opening Closing.
// Compare the morpho::fast:: and morpho:: versions.

#include "basics2d.hh"

#include "morpho/erosion.hh"
#include "morpho/dilation.hh"
#include "morpho/opening.hh"
#include "morpho/closing.hh"

#include "level/compare.hh"

#include "check.hh"

using namespace oln;

#define OK_OR_FAIL				\
      std::cout << "OK" << std::endl;		\
    else					\
      {						\
	std::cout << "FAIL" << std::endl;	\
	fail = true;				\
      }

bool
check()
{
  bool fail = false;

  image2d<int_u8> lena(data("lena128.pgm"));

  std::cout << "erosion ... " << std::flush;
  if (level::is_equal(morpho::erosion(lena, win_c4p()),
		      morpho::fast::erosion(lena, win_c4p())))
    OK_OR_FAIL;
  std::cout << "dilation ... " << std::flush;
  if (level::is_equal(morpho::dilation(lena, win_c4p()),
		      morpho::fast::dilation(lena, win_c4p())))
    OK_OR_FAIL;
  std::cout << "opening ... " << std::flush;
  if (level::is_equal(morpho::opening(lena, win_c4p()),
		      morpho::fast::opening(lena, win_c4p())))
    OK_OR_FAIL;
  std::cout << "closing ... " << std::flush;
  if (level::is_equal(morpho::closing(lena, win_c4p()),
		      morpho::fast::closing(lena, win_c4p())))
    OK_OR_FAIL;

  return fail;
}
