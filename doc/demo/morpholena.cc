#include <oln/basics2d.hh>
#include <oln/morpho/erosion.hh>
#include <oln/morpho/dilation.hh>
#include <oln/morpho/opening.hh>
#include <oln/morpho/closing.hh>
#include <oln/morpho/laplacian.hh>
#include <oln/morpho/gradient.hh>
#include <oln/morpho/top_hat.hh>
#include <oln/morpho/hit_or_miss.hh>
#include <oln/morpho/watershed.hh>
#include <oln/morpho/thinning.hh>
#include <oln/morpho/thickening.hh>
#include <oln/convol/fast_gaussian.hh>
#include <oln/morpho/extrema.hh>
#include <oln/types/all.hh>
#include <oln/level/fill.hh>

using namespace oln;

int main()
{
  image2d<int_u8> lena = load(IMGDIR2 "/lena.pgm");

  save(morpho::erosion(lena,  win_c8p()), "lena-ero.pgm");
  save(morpho::dilation(lena, win_c8p()), "lena-dil.pgm");
  save(morpho::opening(lena,  win_c8p()), "lena-ope.pgm");
  save(morpho::closing(lena,  win_c8p()), "lena-clo.pgm");
  save(morpho::laplacian(convert::force<int_u8>(), lena, win_c8p()),
       "lena-lap.pgm");
  save(morpho::fast::erosion(lena,  win_c8p()), "lena-ero-f.pgm");
  save(morpho::fast::dilation(lena, win_c8p()), "lena-dil-f.pgm");
  save(morpho::fast::opening(lena,  win_c8p()), "lena-ope-f.pgm");
  save(morpho::fast::closing(lena,  win_c8p()), "lena-clo-f.pgm");
  save(morpho::fast::laplacian(convert::force<int_u8>(), lena, win_c8p()),
       "lena-lap-f.pgm");

  save(morpho::beucher_gradient(lena, win_c8p()), "lena-beg.pgm");
  save(morpho::internal_gradient(lena, win_c8p()), "lena-ing.pgm");
  save(morpho::external_gradient(lena, win_c8p()), "lena-exb.pgm");
  save(morpho::fast::beucher_gradient(lena, win_c8p()), "lena-beg-f.pgm");
  save(morpho::fast::internal_gradient(lena, win_c8p()), "lena-ing-f.pgm");
  save(morpho::fast::external_gradient(lena, win_c8p()), "lena-exb-f.pgm");

  save(morpho::white_top_hat(lena, win_c8p()), "lena-wth.pgm");
  save(morpho::black_top_hat(lena, win_c8p()), "lena-bth.pgm");
  save(morpho::self_complementary_top_hat(lena, win_c8p()),
       "lena-sth.pgm");
  save(morpho::top_hat_contrast_op(convert::bound<int_u8>(),
				   lena, win_c8p()), "lena-thc.pgm");

  save(morpho::fast::white_top_hat(lena, win_c8p()), "lena-wth-f.pgm");
  save(morpho::fast::black_top_hat(lena, win_c8p()), "lena-bth-f.pgm");
  save(morpho::fast::self_complementary_top_hat(lena, win_c8p()),
       "lena-sth-f.pgm");
  save(morpho::fast::top_hat_contrast_op(convert::bound<int_u8>(),
					 lena, win_c8p()), "lena-thc-f.pgm");

  window2d mywin;
  mywin
    .add(-3,-2).add(-3,-1).add(-3,0).add(-3,1).add(-3,2)
    .add(-2,-1).add(-2,0).add(-2,1)
    .add(-1,0);
  save(morpho::closing(lena, mywin), "lena-myw.pgm");

  window2d mywin2 = - mywin;

  save(morpho::hit_or_miss(lena, mywin, mywin2), "lena-hom.pgm");
  save(morpho::fast::hit_or_miss(lena, mywin, mywin2), "lena-hom-f.pgm");

  save(morpho::fast::thinning(lena, mywin, mywin2), "lena-thin.pgm");
  save(morpho::fast::thickening(lena, mywin, mywin2), "lena-thick-f.pgm");


  neighborhood2d n = neighb_c4 ();
  save(morpho::watershed_seg<int_u8>(lena, n), "lena-wss.pgm");
  save(morpho::watershed_con<int_u8>(lena, n), "lena-wsc.pgm");

  image2d<int_u8> markers(lena.size());
  level::fill(markers, 0);

  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 10; ++j)
      {
	markers(477 + i, 67 + j) = 72;
	markers(100 + i, 200 + j) = 20;
	markers(50 + i, 50 + j) = 60;
	markers(100 + i, 500 + j) = 200;
	markers(255 + i, 355 + j) = 120;
      }

  save
    (morpho::watershed_seg_or
     (morpho::closing
      (morpho::beucher_gradient(lena, win_c8p()), win_c8p()), markers,
      neighb_c8()),
     "lena-wor.pgm");

  save(convol::fast::gaussian(lena, dfloat(0.50f)),
       "lena-gau.pgm");
  save(convol::fast::gaussian_derivative(lena, dfloat(0.50f)),
       "lena-gd1.pgm");
  save(convol::fast::gaussian_second_derivative(lena, dfloat(0.50f)),
       "lena-gd2.pgm");

  window2d face_se = load(IMGDIR "/face_se.pbm");
  save(morpho::fast::opening(lena,  face_se), "lena-ope-f-face.pgm");

  {
    // extrema
    image2d<bin> minima_map = load(IMGDIR "/map.pbm");
    save(morpho::sure::minima_imposition(lena, minima_map, neighb_c4()),
	 "minima_imposition_sure.pgm");
    save(morpho::sequential::minima_imposition(lena, minima_map, neighb_c4()),
	 "minima_imposition_sequential.pgm");
    save(morpho::hybrid::minima_imposition(lena, minima_map, neighb_c4()),
	 "minima_imposition_hybrid.pgm");

    save(morpho::sure::regional_minima(lena, neighb_c4()),
	 "regional_min_sure.pbm");
    save(morpho::sequential::regional_minima(lena, neighb_c4()),
	 "regional_min_sequential.pbm");
    save(morpho::hybrid::regional_minima(lena, neighb_c4()),
	 "regional_min_hybrid.pbm");
  }
}
