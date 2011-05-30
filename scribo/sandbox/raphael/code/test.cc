
#include <vector>
#include <mln/io/all.hh>

#include <mln/core/site_set/p_vertices.hh>
#include <mln/core/image/graph_elt_window.hh>
#include <mln/core/image/vertex_image.hh>
#include <mln/core/image/graph_elt_neighborhood.hh>
#include <mln/core/concept/function.hh>
#include <mln/core/neighb.hh>
#include <mln/core/image/graph_elt_neighborhood_if.hh>
#include <mln/core/var.hh>
#include <mln/accu/shape/bbox.hh>
#include <mln/fun/i2v/array.hh>
#include <mln/fun/p2b/all.hh>
#include <mln/util/graph.hh>
#include <mln/util/timer.hh>
#include <mln/debug/draw_graph.hh>
#include <mln/debug/println.hh>
#include <mln/transform/all.hh>
#include <mln/make/image2d.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/make/influence_zone_adjacency_graph.hh>
#include <mln/make/w_window2d.hh>
#include <mln/labeling/all.hh>
#include <mln/make/image.hh>
#include <mln/value/rgb8.hh>
#include <mln/value/int_u8.hh>
#include <mln/value/int_u.hh>
#include <mln/data/all.hh>
#include <mln/core/alias/neighb2d.hh>
#include <mln/algebra/all.hh>
#include <mln/core/image/graph_elt_neighborhood.hh>
#include <mln/literal/all.hh>
#include <mln/graph/compute.hh>

#include <mln/draw/plot.hh>
#include <my/debug/pict.hh>
#include <my/debug/bbox.hh>
#include <my/util/vector_bbox.hh>
#include <my/util/vector_bbox_group.hh>
#include <my/document/document.hh>

#include <my/document/clean.hh>
using namespace mln;
using namespace std;
void Process(std::string File)
{
  
   std::cout << "Processing : " << File << endl;
    /* CREATE GRAPH */
      typedef value::int_u<16> uint16;
    image2d<bool> ima;
    
   mln::util::timer timer;
   timer.start();
   io::pbm::load(ima, File);
   std::cout << "LOADING FILE : " << timer.stop() << endl;
   timer.restart();

    

    uint16 areas_detected;
      timer.start();
    image2d<uint16> ima_blob = labeling::blobs(ima, c4(), areas_detected);
     std::cout << "CREATE BLOBS : " << timer.stop() << endl;
     timer.restart();
       timer.start();
    image2d<uint16> ima_influ = transform::influence_zone_geodesic(ima_blob, c8());
     std::cout << "CREATE INFLUENCE ZONE GEODESIC : " << timer.stop() << endl;
     timer.restart();
       timer.start();
    util::graph grph = make::influence_zone_adjacency_graph(ima_influ, c4(), areas_detected);
    
    
    std::cout << "CREATE GRAPH : " << timer.stop() << endl;
    
    
    /* COMPUTE GRAPH POINT POSITION */
    timer.restart();
    util::array<box2d> boxes = labeling::compute(accu::meta::shape::bbox(), ima_blob, areas_detected);
    typedef p_vertices<util::graph, fun::i2v::array<mln::point2d> > g_vertices_p;
    typedef graph_elt_neighborhood<util::graph, g_vertices_p> g_nbh;    
    fun::i2v::array<point2d> graph_points(areas_detected + 1);
    graph_points(0) = point2d(0,0);
    for(unsigned int N = 0; N <  areas_detected; N++)
    {graph_points(N + 1) = boxes[N + 1].pcenter();}
    g_vertices_p area_grph(grph, graph_points);
    
    std::cout << "COMPUTE GRAPH POINT POSITION : " << timer.stop() << endl;
    
     /* WORK ON GRAPH */
     
    
     
      timer.restart();
     
    mymln::document::document<uint16,float,short> doc(ima_blob, ima_influ, boxes, area_grph, areas_detected);
    doc.vertical_separator_ratio_range(0.0f, 0.1f);
    doc.horizontal_separator_ratio_range(6.0f, 1000.0f);
    doc.container_volume_range(40, 100);
    for (uint16 N = 1; N <=  areas_detected; N++)
    {

      g_nbh grph_nbh;
      mln_psite_(g_vertices_p) plist(area_grph, N);
      mln_fwd_niter_(g_nbh) fq(grph_nbh, plist);
      unsigned link = 0;
      for_all((fq))
      {
	link++;
      }
      doc.add(N, (uint16)link);
	
    }
    //mymln::debug::save_label_image(ima_influ, "influ_" + File);
    mymln::document::clean_containers_items(doc);
    mymln::document::clean_letters_items(doc);
    mymln::document::clean_get_lines(doc);
    doc.stat();
    std::cout << "WORK ON GRAPH : " << timer.stop() << endl;
    //io::ppm::save(ima_influ, "separator.ppm");
   //io::pbm::save(doc.image_mask_separators(),"separators");
    io::pbm::save(doc.image_mask_letters(),"letters_" + File);
    io::pbm::save(doc.image_mask_separators(),"separators_" + File);
    io::pbm::save(doc.image_mask_containers(),"containers_" + File);
    io::pbm::save(doc.image_mask_noise(),"noise_" + File);
 /*  typedef vertex_image<point2d,bool> v_ima_g;
   v_ima_g mask = doc.fun_mask_letters();
*/
  /*image2d<bool> out(3500,3500);
  



    mln_piter_(v_ima_g) v(mask.domain());
    typedef graph_elt_neighborhood_if<util::graph, g_vertices_p, v_ima_g> nbh_t;
    nbh_t nbh(mask);
    mln_niter_(nbh_t) q(nbh, v);
    
    unsigned int fnds = 0;
    for_all(v)
    {
      unsigned int nds = 0;
      for_all(q)
      {	
	nds++;
	
	draw::line(out, q,v, true);
      }
      if(nds > 0)
      {
	std::cout << v << endl;
	fnds++;
      }
      
      
    }*/
   //mymln::debug::draw_graph(out, mask);
    //io::pbm::save(out, "maskltt.dgb");
   //std::cout << "NODES:" << fnds << endl;
   //  mymln::debug::save_graph_image(area_grph, ima, "graph_" + File);
    // mymln::debug::save_graph_image(doc.fun_mask_separators(), ima, "separator_graph_" + File);
    mymln::debug::save_graph_image(area_grph, doc.image_mask_letters(), "graph_" + File);
    mymln::debug::save_graph_image(doc.fun_mask_letters(), doc.image_mask_letters(), "container_graph_" + File);
   //mymln::debug::save_boxes_image(doc.bbox_mask_letters(), ima, "lbox_" + File);
      //mymln::debug::save_boxes_image(doc.bbox_enlarge_mask_letters(10, 0), ima, "linebox_" + File);
}


int main( int argc, char** argv)
{
   if(argc <= 1){Process("ima.pbm");}
   else
   {
     for(int N = 1 ; N < argc; N++)
     {Process(argv[N]);}
   }
    
}