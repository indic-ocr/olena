#							-*- Automake -*-

# Copyright (C) 2009, 2010 EPITA Research and Development Laboratory (LRDE).
#
# This file is part of Olena.
#
# Olena is free software: you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free
# Software Foundation, version 2 of the License.
#
# Olena is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Olena.  If not, see <http://www.gnu.org/licenses/>.
#

## Process this file through Automake to create Makefile.in.

examples_dir = $(doc_dir)/examples

PROGRAMS_examples =	\
  accu-right-instanciation 	\
  borderthickness 		\
  box2d-bbox 			\
  domain-display 		\
  dpoint-1 			\
  estim-sites 			\
  extend 			\
  extension-ignore 		\
  fill 				\
  fill-call-1			\
  fill-part-image 		\
  fill-subdomain 		\
  fill-subdomain-shorter	\
  fill-imageif-cfun 		\
  first_routine 		\
  forall-piter  		\
  fun-p2v-1 			\
  graph-data 			\
  graph-iter 			\
  ima-has 			\
  ima-save 			\
  ima-size 			\
  ima2d-1 			\
  ima2d-2 			\
  ima2d-3 			\
  ima2d-4 			\
  ima2d-5 			\
  ima2d-6-clone			\
  ima2d-7 			\
  ima2d-rot 			\
  ima-size 			\
  labeling-compute 		\
  logical-not 			\
  mln_var 			\
  parray-bbox 			\
  paste 			\
  paste-call-1 			\
  parray-append 		\
  point-1 			\
  predicate-1 			\
  win-create-1 			\
  win-create-2

PROGRAMS_examples += 	\
  tuto2_first_image 		\
  tuto3_rw_image 		\
  tuto4_genericity_and_algorithms

# Tuto3
PROGRAMS_examples += 	\
  tuto3_colorize 		\
  tuto3_println 		\
  tuto3_trace

# Tuto4
PROGRAMS_examples += 	\
  tuto4_point2d			\
  tuto4_site_set_create

EXTRA_PROGRAMS = $(PROGRAMS_examples)

# FIXME: Is this really needed?
CLEANFILES += $(PROGRAMS_examples)

accu_right_instanciation_SOURCES = $(examples_dir)/accu-right-instanciation.cc
borderthickness_SOURCES = $(examples_dir)/borderthickness.cc
box2d_bbox_SOURCES = $(examples_dir)/box2d-bbox.cc
domain_display_SOURCES = $(examples_dir)/domain-display.cc
dpoint_1_SOURCES = $(examples_dir)/dpoint-1.cc
estim_sites_SOURCES = $(examples_dir)/estim-sites.cc
extend_SOURCES = $(examples_dir)/extend.cc
extension_ignore_SOURCES = $(examples_dir)/extension-ignore.cc
fill_SOURCES = $(examples_dir)/fill.cc
fill_call_1_SOURCES = $(examples_dir)/fill-call-1.cc
fill_part_image_SOURCES = $(examples_dir)/fill-part-image.cc
fill_subdomain_SOURCES = $(examples_dir)/fill-subdomain.cc
fill_subdomain_shorter_SOURCES = $(examples_dir)/fill-subdomain-shorter.cc
fill_imageif_cfun_SOURCES = $(examples_dir)/fill-imageif-cfun.cc
first_routine_SOURCES = $(examples_dir)/tuto3/first_routine.cc
forall_piter_SOURCES = $(examples_dir)/forall-piter.cc
fun_p2v_1_SOURCES = $(examples_dir)/fun-p2v-1.cc
graph_data_SOURCES = $(examples_dir)/graph-data.cc
graph_iter_SOURCES = $(examples_dir)/graph-iter.cc
ima_has_SOURCES = $(examples_dir)/ima-has.cc
ima_save_SOURCES = $(examples_dir)/ima-save.cc
ima_size_SOURCES = $(examples_dir)/ima-size.cc
ima2d_1_SOURCES = $(examples_dir)/ima2d-1.cc
ima2d_2_SOURCES = $(examples_dir)/ima2d-2.cc
ima2d_3_SOURCES = $(examples_dir)/ima2d-3.cc
ima2d_4_SOURCES = $(examples_dir)/ima2d-4.cc
ima2d_5_SOURCES = $(examples_dir)/ima2d-5.cc
ima2d_6_clone_SOURCES = $(examples_dir)/ima2d-6-clone.cc
ima2d_7_SOURCES = $(examples_dir)/ima2d-7.cc
ima2d_rot_SOURCES = $(examples_dir)/ima2d-rot.cc
labeling_compute_SOURCES = $(examples_dir)/labeling-compute.cc
logical_not_SOURCES = $(examples_dir)/logical-not.cc
mln_var_SOURCES = $(examples_dir)/mln_var.cc
paste_SOURCES = $(examples_dir)/paste.cc
paste_call_1_SOURCES = $(examples_dir)/paste-call-1.cc
parray_append_SOURCES = $(examples_dir)/parray-append.cc
parray_bbox_SOURCES = $(examples_dir)/parray-bbox.cc
point_1_SOURCES = $(examples_dir)/point-1.cc
predicate_1_SOURCES = $(examples_dir)/predicate-1.cc
win_create_1_SOURCES = $(examples_dir)/win-create-1.cc
win_create_2_SOURCES = $(examples_dir)/win-create-2.cc

tuto2_first_image_SOURCES = $(examples_dir)/tuto2_first_image.cc
tuto3_rw_image_SOURCES = $(examples_dir)/tuto3_rw_image.cc
tuto4_genericity_and_algorithms_SOURCES = $(examples_dir)/tuto4_genericity_and_algorithms.cc

# Tuto 3
tuto3_colorize_SOURCES = $(examples_dir)/tuto3/colorize.cc
tuto3_println_SOURCES = $(examples_dir)/tuto3/println.cc
tuto3_trace_SOURCES = $(examples_dir)/tuto3/trace.cc

# Tuto 4
tuto4_site_set_create_SOURCES = $(examples_dir)/tuto4/site_set_create.cc
tuto4_point2d_SOURCES = $(examples_dir)/tuto4/point2d.cc


.PHONY : examples run-examples diff-data fix-refdata 		\
	 split-examples split-outputs

examples: $(PROGRAMS_examples)

run-examples: examples
	test -d $(top_builddir)/milena/doc/figures  			\
		|| mkdir $(top_builddir)/milena/doc/figures;		\
	failcom='exit 1'; 						\
	list='$(PROGRAMS_examples)'; for bin in $$list; do	\
	  echo "Running $$bin"; 					\
	  ./$$bin > $(OUTPUTS_SRCDIR)/$$bin.txt || eval $$failcom; 	\
	done

## FIXME: This is wrong.  Make is not an imperative language, and this
## rule probably does not work as expected.
data-regen: examples run-examples split-examples split-outputs diff-data


diff-data: run-examples split-examples
	@failcom='exit 1'; 						\
	has_txt_diff="";						\
	txtlist="$(OUTPUTS_SRCDIR)/*.txt"; for txt in $$txtlist; do 	\
	  echo "Diff `basename $$txt`";					\
	  diff $$txt $(OUTPUTS_SRCDIR)/`basename $$txt` >/dev/null 2>&1	\
		|| has_txt_diff="$$has_txt_diff `basename $$txt`";	\
	done;								\
	has_fig_diff="";						\
	figlist="$(FIGURES_SRCDIR)/*.p*m"; for fig in $$figlist; do 	\
	  echo "Diff `basename $$fig`";					\
	  diff $$fig $(FIGURES_SRCDIR)/`basename $$fig` >/dev/null 2>&1 \
		|| has_fig_diff="$$has_fig_diff `basename $$fig`";	\
	done; 								\
	has_split_out_diff="";						\
	split_outlist="$(SPLIT_OUTPUTS_SRCDIR)/*"; for split_out in $$split_outlist; do \
	  echo "Diff `basename $$split_out`";				\
	  diff $$split_out $(SPLIT_OUTPUTS_SRCDIR)/`basename $$split_out` >/dev/null 2>&1 \
		|| has_split_out_diff="$$has_split_out_diff `basename $$split_out`";	\
	done; 								\
	has_split_ex_diff="";						\
	split_exlist="$(SPLIT_EXAMPLES_SRCDIR)/*"; for split_ex in $$split_exlist; do \
	  echo "Diff `basename $$split_ex`";				\
	  diff $$split_ex $(SPLIT_EXAMPLES_SRCDIR)/`basename $$split_ex` >/dev/null 2>&1 \
		|| has_split_ex_diff="$$has_split_ex_diff `basename $$split_ex`";	\
	done; 								\
	(test -z "$$has_txt_diff" && test -z "$$has_fig_diff" && 	\
	 test -z "$$has_split_out_diff" && test -z "$$has_split_ex_diff")\
	 || (echo "--------";						\
	     echo "ERROR: please check if the tutorial needs an update.";\
	     echo "       The following files differ from their \
reference or their reference file does not exist:";  			\
	     echo "--------"; 						\
	     echo "* Outputs:";						\
	     echo "";							\
	     echo "$$has_txt_diff"; 					\
	     echo "";							\
	     echo "--------"; 						\
	     echo "* Figures:"; 					\
	     echo "";							\
	     echo "$$has_fig_diff"; 					\
	     echo "";							\
	     echo "--------"; 						\
	     echo "* Split outputs:"; 					\
	     echo "";							\
	     echo "$$has_split_out_diff"; 				\
	     echo "";							\
	     echo "--------"; 						\
	     echo "* Split examples:"; 					\
	     echo "";							\
	     echo "$$has_split_ex_diff"; 				\
	     echo "";							\
	     echo "--------"; 						\
	     echo "* Please update manually the reference files located in:" \
	     echo "";							\
	     echo " $(OUTPUTS_SRCDIR)"; 				\
	     echo " $(FIGURES_SRCDIR)"; 				\
	     echo " $(SPLIT_EXAMPLES_SRCDIR)"; 				\
	     echo " $(SPLIT_OUTPUTS_SRCDIR)"; 				\
	     echo "";							\
	     echo "* Reference files can updated automatically with 'make fix-refdata'"; \
	     echo "";							\
	     echo "";							\
	     eval $$failcom);


fix-refdata:
	@failcom='exit 1'; 						\
	txtlist="$(OUTPUTS_SRCDIR)/*.txt"; for txt in $$txtlist; do 	\
	  diff $$txt $(OUTPUTS_SRCDIR)/`basename $$txt` >/dev/null 2>&1	\
		|| echo "Updating reference file for $$txt"; 		\
		   cp $$txt $(OUTPUTS_SRCDIR);				\
	done;								\
	figlist="$(FIGURES_SRCDIR)/*.p*m"; for fig in $$figlist; do 	\
	  diff $$fig $(FIGURES_SRCDIR)/`basename $$fig` >/dev/null 2>&1 \
		|| echo "Updating reference file for $$fig";		\
		   cp $$fig $(FIGURES_SRCDIR);				\
	done; 								\
	split_outlist="$(SPLIT_OUTPUTS_SRCDIR)/*.txt"; for split_out in $$split_outlist; do \
	  diff $$split_out $(SPLIT_OUTPUTS_SRCDIR)/`basename $$split_out` >/dev/null 2>&1 \
		|| echo "Updating reference file for $$split_out";	\
		   cp $$split_out $(SPLIT_OUTPUTS_SRCDIR);		\
	done; 								\
	split_exlist="$(SPLIT_EXAMPLES_SRCDIR)/*.cc"; for split_ex in $$split_exlist; do \
	  diff $$split_ex $(SPLIT_EXAMPLES_SRCDIR)/`basename $$split_ex` >/dev/null 2>&1 \
		|| echo "Updating reference file for $$split_ex";	\
		   cp $$split_ex $(SPLIT_EXAMPLES_SRCDIR);		\
	done;


split-examples:
	test -d $(SPLIT_EXAMPLES_SRCDIR) || mkdir $(SPLIT_EXAMPLES_SRCDIR)
	@failcom='exit 1'; 						\
	list=`find $(EXAMPLES_SRCDIR) -type f -name '*.cc'`; for file in $$list; do \
	$(DOC_SRCDIR)/tools/split_sample.sh $$file cc raw $(SPLIT_EXAMPLES_SRCDIR)\
					      || eval $$failcom; 	\
	done

split-outputs:
	test -d $(SPLIT_OUTPUTS_SRCDIR) || mkdir $(SPLIT_OUTPUTS_SRCDIR)
	@failcom='exit 1'; 						\
	list='$(OUTPUTS_SRCDIR)/*.txt'; for file in $$list; do 	\
	$(DOC_SRCDIR)/tools/split_sample.sh $$file txt "" $(SPLIT_OUTPUTS_SRCDIR)\
					      || eval $$failcom; 	\
	done

## FIXME: Generated products recored in the repository should be
## listed in MAINTAINERCLEANFILES.
clean-local: clean-figures
##	rm -Rf $(OUTPUTS_BUILDDIR)
##	rm -f $(EXAMPLES_BUILDDIR)/*.cc

## FIXME: Generated products recored in the repository should be
## listed in MAINTAINERCLEANFILES.
clean-figures:
##	rm -Rf $(FIGURES_BUILDDIR)