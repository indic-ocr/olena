// Copyright (C) 2009 EPITA Research and Development Laboratory (LRDE)
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

#include <iostream>

#include <mln/core/image/image2d.hh>
#include <mln/core/alias/neighb2d.hh>

#include <mln/data/convert.hh>

#include <mln/value/rgb8.hh>
#include <mln/value/label_16.hh>
#include <mln/literal/colors.hh>

#include <mln/io/pbm/load.hh>
#include <mln/io/ppm/save.hh>

#include <scribo/primitive/extract/objects.hh>
#include <scribo/primitive/link/with_single_left_link.hh>

#include <scribo/draw/bounding_boxes.hh>

#include <scribo/debug/save_linked_bboxes_image.hh>
#include <scribo/debug/usage.hh>



const char *args_desc[][2] =
{
  { "input.pbm", "A binary image. True for objects and False for the background." },
  { "max_nbh_dist", " Maximum distance for neighborhood search. (common value : 30)" },
  {0, 0}
};


int main(int argc, char* argv[])
{
  using namespace scribo;
  using namespace scribo::primitive::internal;
  using namespace mln;

  if (argc != 4)
    return scribo::debug::usage(argv,
				"Show sucessful/unsuccessful left links between components.",
				"input.pbm max_nbh_dist output.ppm",
				args_desc,
				"A color image. Valid links are drawn in green, invalid ones in red.");

  image2d<bool> input;
  io::pbm::load(input, argv[1]);

  // Finding objects.
  value::label_16 nbboxes;
  typedef image2d<value::label_16> L;
  object_image(L) objects
    = scribo::primitive::extract::objects(input, c8(), nbboxes);

  // Finding left links.
  object_links<L> left_link
    = primitive::link::with_single_left_link(objects, atoi(argv[2]));



  // Preparing output image.
  image2d<value::rgb8> output = data::convert(value::rgb8(), input);
  scribo::draw::bounding_boxes(output, objects, literal::blue);


  // Drawing links.
  mln::util::array<mln_result_(accu::center<mln_psite_(L)>)>
    mass_centers = labeling::compute(accu::meta::center(),
				     objects, objects.nlabels());

  for_all_ncomponents(i, objects.nlabels())
  {
    unsigned midcol = (objects.bbox(i).pmax().col()
		       - objects.bbox(i).pmin().col()) / 2;
    int dmax = midcol + atoi(argv[2]);
    mln_site_(L) c = mass_centers(i);

    mln_site_(L) p = c + mln::left;

    while (is_invalid_link(objects, left_link, p, i, c, dmax))
    {
      if (left_link[i] != i)
	output(p) = literal::green;
      else
	output(p) = literal::red;
      --p.col();
    }

  }

  io::ppm::save(output, argv[3]);
}