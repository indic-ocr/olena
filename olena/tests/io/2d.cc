#include "loadsave.hh"

bool
check(void)
{
  bool fail = false;

  fail |= loadsave< image2d<ntg::bin>     >(rdata("lena"), "lena");
  fail |= loadsave< image2d<int_u8>  >(rdata("lena"), "lena");
  fail |= loadsave< image2d<nrgb_8>  >(rdata("lena"), "lena");

  fail |= loadsave< image2d<ntg::bin>     >(rdata("lena.pbm"), "lena.pbm");
  fail |= loadsave< image2d<int_u8>  >(rdata("lena.pgm"), "lena.pgm");
  fail |= loadsave< image2d<nrgb_8>  >(rdata("lena.ppm"), "lena.ppm");

  fail |= loadsave< image2d<ntg::bin>     >(rdata("lena.ppbm"), "lena.ppbm");
  fail |= loadsave< image2d<int_u8>  >(rdata("lena.ppgm"), "lena.ppgm");
  fail |= loadsave< image2d<nrgb_8>  >(rdata("lena.pppm"), "lena.pppm");

  fail |= loadsave< image2d<int_u16> >(rdata("lena16b.pgm"), "lena16b.pgm");
  fail |= loadsave< image2d<int_u16> >(rdata("lena16b.ppgm"), "lena16b.ppgm");

#if HAVE_ZLIB
  fail |= loadsave< image2d<ntg::bin>     >(rdata("lena.pbm.gz"), "lena.pbm.gz");
  fail |= loadsave< image2d<int_u8>  >(rdata("lena.pgm.gz"), "lena.pgm.gz");
  fail |= loadsave< image2d<nrgb_8>  >(rdata("lena.ppm.gz"), "lena.ppm.gz");
#endif

  return fail;
}
