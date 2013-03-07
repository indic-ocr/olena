## Generated by ./build-aux/build_unit_test.sh, do not modify.

check_PROGRAMS =

# Starting a conditional unit test list.
if HAVE_MAGICKXX
check_PROGRAMS +=  \
scribo_core_document \
scribo_core_internal_doc_serializer \
scribo_debug_text_color_image \
scribo_filter_images_in_paragraph \
scribo_filter_paragraphs_in_borders \
scribo_filter_paragraphs_in_image \
scribo_filter_separators_in_borders \
scribo_filter_separators_in_element \
scribo_filter_separators_in_paragraph \
scribo_filter_separators_vert_in_borders \
scribo_io_img_internal_debug_img_visitor \
scribo_io_img_internal_full_img_visitor \
scribo_io_img_internal_non_text_img_visitor \
scribo_io_img_internal_text_img_visitor \
scribo_io_img_save \
scribo_io_xml_internal_extended_page_xml_visitor \
scribo_io_xml_internal_page_xml_visitor \
scribo_io_xml_internal_print_page_preambule \
scribo_io_xml_save \
scribo_make_text_blocks_image \
scribo_make_text_components_image \
scribo_postprocessing_images_to_drop_capital \
scribo_primitive_extract_alignments \
scribo_primitive_extract_non_text \
scribo_primitive_extract_non_text_hdoc \
scribo_primitive_extract_non_text_kmean \
scribo_text_extract_lines_wo_merge

scribo_core_document_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_core_document_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_core_internal_doc_serializer_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_core_internal_doc_serializer_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_debug_text_color_image_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_debug_text_color_image_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_images_in_paragraph_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_images_in_paragraph_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_paragraphs_in_borders_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_paragraphs_in_borders_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_paragraphs_in_image_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_paragraphs_in_image_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_separators_in_borders_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_separators_in_borders_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_separators_in_element_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_separators_in_element_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_separators_in_paragraph_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_separators_in_paragraph_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_filter_separators_vert_in_borders_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_filter_separators_vert_in_borders_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_img_internal_debug_img_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_img_internal_debug_img_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_img_internal_full_img_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_img_internal_full_img_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_img_internal_non_text_img_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_img_internal_non_text_img_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_img_internal_text_img_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_img_internal_text_img_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_img_save_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_img_save_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_internal_extended_page_xml_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_internal_extended_page_xml_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_internal_page_xml_visitor_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_internal_page_xml_visitor_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_internal_print_page_preambule_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_internal_print_page_preambule_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_save_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_save_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_make_text_blocks_image_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_make_text_blocks_image_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_make_text_components_image_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_make_text_components_image_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_postprocessing_images_to_drop_capital_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_postprocessing_images_to_drop_capital_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_primitive_extract_alignments_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_primitive_extract_alignments_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_primitive_extract_non_text_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_primitive_extract_non_text_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_primitive_extract_non_text_hdoc_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_primitive_extract_non_text_hdoc_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_primitive_extract_non_text_kmean_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_primitive_extract_non_text_kmean_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_text_extract_lines_wo_merge_CPPFLAGS= ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_text_extract_lines_wo_merge_LDFLAGS= ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_MAGICKXX

# Starting a conditional unit test list.
if HAVE_MAGICKXX
if HAVE_QT
check_PROGRAMS +=  \
scribo_io_xml_internal_full_xml_visitor \
scribo_io_xml_load

scribo_io_xml_internal_full_xml_visitor_CPPFLAGS= ${QT_CPPFLAGS} -DHAVE_QT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_internal_full_xml_visitor_LDFLAGS= ${QT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_load_CPPFLAGS= ${QT_CPPFLAGS} -DHAVE_QT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_io_xml_load_LDFLAGS= ${QT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_QT
endif HAVE_MAGICKXX

# Starting a conditional unit test list.
if HAVE_MAGICKXX
if HAVE_QT
if HAVE_TESSERACT
if HAVE_TIFF
check_PROGRAMS +=  \
scribo_toolchain_nepomuk_text_extraction

scribo_toolchain_nepomuk_text_extraction_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${QT_CPPFLAGS} -DHAVE_QT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_toolchain_nepomuk_text_extraction_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${QT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_TIFF
endif HAVE_TESSERACT
endif HAVE_QT
endif HAVE_MAGICKXX

# Starting a conditional unit test list.
if HAVE_MAGICKXX
if HAVE_TESSERACT
check_PROGRAMS +=  \
scribo_toolchain_content_in_hdoc \
scribo_toolchain_internal_content_in_hdoc_functor

scribo_toolchain_content_in_hdoc_CPPFLAGS= ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_toolchain_content_in_hdoc_LDFLAGS= ${TESSERACT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_toolchain_internal_content_in_hdoc_functor_CPPFLAGS= ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_toolchain_internal_content_in_hdoc_functor_LDFLAGS= ${TESSERACT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_TESSERACT
endif HAVE_MAGICKXX

# Starting a conditional unit test list.
if HAVE_MAGICKXX
if HAVE_TESSERACT
if HAVE_TIFF
check_PROGRAMS +=  \
scribo_toolchain_content_in_doc \
scribo_toolchain_internal_content_in_doc_functor

scribo_toolchain_content_in_doc_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_toolchain_content_in_doc_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
scribo_toolchain_internal_content_in_doc_functor_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${MAGICKXX_CPPFLAGS} -DHAVE_MAGICKXX ${AM_CPPFLAGS}
scribo_toolchain_internal_content_in_doc_functor_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${MAGICKXX_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_TIFF
endif HAVE_TESSERACT
endif HAVE_MAGICKXX

# Starting a conditional unit test list.
if HAVE_QT
check_PROGRAMS +=  \
scribo_convert_from_base64 \
scribo_convert_from_qimage \
scribo_io_xml_internal_save_image_to_xml

scribo_convert_from_base64_CPPFLAGS= ${QT_CPPFLAGS} -DHAVE_QT ${AM_CPPFLAGS}
scribo_convert_from_base64_LDFLAGS= ${QT_LDFLAGS}  ${AM_LDFLAGS}
scribo_convert_from_qimage_CPPFLAGS= ${QT_CPPFLAGS} -DHAVE_QT ${AM_CPPFLAGS}
scribo_convert_from_qimage_LDFLAGS= ${QT_LDFLAGS}  ${AM_LDFLAGS}
scribo_io_xml_internal_save_image_to_xml_CPPFLAGS= ${QT_CPPFLAGS} -DHAVE_QT ${AM_CPPFLAGS}
scribo_io_xml_internal_save_image_to_xml_LDFLAGS= ${QT_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_QT

# Starting a conditional unit test list.
if HAVE_TESSERACT
if HAVE_TIFF
check_PROGRAMS +=  \
scribo_text_recognition \
scribo_toolchain_internal_text_in_doc_functor \
scribo_toolchain_text_in_doc

scribo_text_recognition_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${AM_CPPFLAGS}
scribo_text_recognition_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${AM_LDFLAGS}
scribo_toolchain_internal_text_in_doc_functor_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${AM_CPPFLAGS}
scribo_toolchain_internal_text_in_doc_functor_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${AM_LDFLAGS}
scribo_toolchain_text_in_doc_CPPFLAGS= ${TIFF_CPPFLAGS} -DHAVE_TIFF ${TESSERACT_CPPFLAGS} -DHAVE_TESSERACT ${AM_CPPFLAGS}
scribo_toolchain_text_in_doc_LDFLAGS= ${TIFF_LDFLAGS}  ${TESSERACT_LDFLAGS}  ${AM_LDFLAGS}
endif HAVE_TIFF
endif HAVE_TESSERACT

# Starting non-conditional unit test list.
check_PROGRAMS +=  \
scribo_all \
scribo_binarization_all \
scribo_binarization_global_threshold \
scribo_binarization_global_threshold_auto \
scribo_binarization_internal_local_threshold_core \
scribo_binarization_internal_local_threshold_debug \
scribo_binarization_internal_niblack_formula \
scribo_binarization_internal_niblack_functor \
scribo_binarization_internal_niblack_functor_fast \
scribo_binarization_internal_niblack_threshold_functor \
scribo_binarization_internal_sauvola_formula \
scribo_binarization_internal_sauvola_functor \
scribo_binarization_internal_sauvola_ms_functor \
scribo_binarization_internal_sauvola_threshold_functor \
scribo_binarization_internal_singh_formula \
scribo_binarization_internal_singh_functor \
scribo_binarization_internal_wolf_formula \
scribo_binarization_internal_wolf_functor \
scribo_binarization_internal_wolf_functor_fast \
scribo_binarization_kim \
scribo_binarization_local_threshold \
scribo_binarization_niblack \
scribo_binarization_niblack_fast \
scribo_binarization_niblack_threshold \
scribo_binarization_otsu \
scribo_binarization_otsu_threshold \
scribo_binarization_sauvola \
scribo_binarization_sauvola_ms \
scribo_binarization_sauvola_ms_split \
scribo_binarization_sauvola_threshold \
scribo_binarization_singh \
scribo_binarization_wolf \
scribo_binarization_wolf_fast \
scribo_canvas_integral_browsing \
scribo_convert_to_base64 \
scribo_core_all \
scribo_core_central_sites \
scribo_core_component_features_data \
scribo_core_component_info \
scribo_core_component_set \
scribo_core_concept_dmax_functor \
scribo_core_concept_link_functor \
scribo_core_concept_serializable \
scribo_core_concept_serialize_visitor \
scribo_core_def_color_type \
scribo_core_def_lbl_type \
scribo_core_erase_objects \
scribo_core_group_info \
scribo_core_init_integral_image \
scribo_core_internal_sort_comp_ids \
scribo_core_line_info \
scribo_core_line_links \
scribo_core_line_set \
scribo_core_macros \
scribo_core_object_groups \
scribo_core_object_links \
scribo_core_paragraph_info \
scribo_core_paragraph_set \
scribo_core_stats \
scribo_core_tag_anchor \
scribo_core_tag_component \
scribo_core_tag_line \
scribo_core_tag_paragraph \
scribo_debug_alignment_decision_image \
scribo_debug_all \
scribo_debug_bboxes_enlarged_image \
scribo_debug_bboxes_image \
scribo_debug_char_space_image \
scribo_debug_decision_image \
scribo_debug_highlight_text_area \
scribo_debug_line_info_image \
scribo_debug_linked_bboxes_image \
scribo_debug_links_decision_image \
scribo_debug_links_image \
scribo_debug_logger \
scribo_debug_looks_like_a_text_line_image \
scribo_debug_mean_and_base_lines_image \
scribo_debug_option_check \
scribo_debug_option_parser \
scribo_debug_save_comp_diff \
scribo_debug_save_label_image \
scribo_debug_save_table_image \
scribo_debug_text_areas_image \
scribo_debug_usage \
scribo_draw_all \
scribo_draw_bounding_box_links \
scribo_draw_bounding_boxes \
scribo_draw_groups_bboxes \
scribo_draw_line_components \
scribo_estim_components_features \
scribo_estim_font_boldness \
scribo_estim_font_color \
scribo_estim_internal_compute_skeleton \
scribo_estim_object_groups_mean_width \
scribo_filter_all \
scribo_filter_common_objects_photo \
scribo_filter_internal_alignment_angle \
scribo_filter_internal_component_aligned \
scribo_filter_internal_compute \
scribo_filter_line_links_x_height \
scribo_filter_object_groups_mean_width \
scribo_filter_object_groups_size_ratio \
scribo_filter_object_groups_small \
scribo_filter_object_groups_with_holes \
scribo_filter_object_links_aligned \
scribo_filter_object_links_bbox_h_ratio \
scribo_filter_object_links_bbox_overlap \
scribo_filter_object_links_bbox_ratio \
scribo_filter_object_links_bbox_w_ratio \
scribo_filter_object_links_bottom_aligned \
scribo_filter_object_links_center_aligned \
scribo_filter_object_links_left_aligned \
scribo_filter_object_links_non_aligned_simple \
scribo_filter_object_links_right_aligned \
scribo_filter_object_links_top_aligned \
scribo_filter_objects_h_thick \
scribo_filter_objects_h_thin \
scribo_filter_objects_large \
scribo_filter_objects_on_border \
scribo_filter_objects_size_ratio \
scribo_filter_objects_small \
scribo_filter_objects_thick \
scribo_filter_objects_thin \
scribo_filter_objects_v_thick \
scribo_filter_objects_v_thin \
scribo_filter_objects_with_holes \
scribo_filter_paragraphs_bbox_overlap \
scribo_fun_v2b_label_to_bool \
scribo_fun_v2b_objects_large_filter \
scribo_fun_v2b_objects_on_border_filter \
scribo_fun_v2b_objects_small_filter \
scribo_fun_v2v_highlight \
scribo_io_img_internal_draw_edges \
scribo_io_text_boxes_save \
scribo_io_xml_internal_compute_text_colour \
scribo_io_xml_internal_print_box_coords \
scribo_io_xml_internal_print_image_coords \
scribo_io_xml_internal_time_info \
scribo_layout_internal_hist_info \
scribo_layout_internal_node \
scribo_layout_xy_cut \
scribo_make_all \
scribo_make_debug_filename \
scribo_make_influence_zone_graph \
scribo_postprocessing_all \
scribo_postprocessing_fill_object_holes \
scribo_preprocessing_all \
scribo_preprocessing_crop \
scribo_preprocessing_crop_without_localization \
scribo_preprocessing_denoise \
scribo_preprocessing_denoise_bg \
scribo_preprocessing_denoise_fg \
scribo_preprocessing_deskew \
scribo_preprocessing_deskew_crop \
scribo_preprocessing_homogeneous_contrast \
scribo_preprocessing_rotate_90 \
scribo_preprocessing_split_bg_fg \
scribo_primitive_all \
scribo_primitive_extract_all \
scribo_primitive_extract_canvas \
scribo_primitive_extract_cells \
scribo_primitive_extract_components \
scribo_primitive_extract_horizontal_separators \
scribo_primitive_extract_internal_union \
scribo_primitive_extract_lines_discontinued \
scribo_primitive_extract_lines_h_discontinued \
scribo_primitive_extract_lines_h_pattern \
scribo_primitive_extract_lines_h_single \
scribo_primitive_extract_lines_h_thick \
scribo_primitive_extract_lines_h_thick_and_single \
scribo_primitive_extract_lines_h_thick_and_thin \
scribo_primitive_extract_lines_pattern \
scribo_primitive_extract_lines_thick \
scribo_primitive_extract_lines_v_discontinued \
scribo_primitive_extract_lines_v_pattern \
scribo_primitive_extract_lines_v_single \
scribo_primitive_extract_lines_v_thick \
scribo_primitive_extract_lines_v_thick_and_single \
scribo_primitive_extract_separators \
scribo_primitive_extract_separators_nonvisible \
scribo_primitive_extract_vertical_separators \
scribo_primitive_group_all \
scribo_primitive_group_apply \
scribo_primitive_group_from_double_link \
scribo_primitive_group_from_double_link_any \
scribo_primitive_group_from_graph \
scribo_primitive_group_from_single_link \
scribo_primitive_identify \
scribo_primitive_internal_all \
scribo_primitive_internal_find_graph_link \
scribo_primitive_internal_find_root \
scribo_primitive_internal_have_link_valid \
scribo_primitive_internal_is_link_valid \
scribo_primitive_internal_rd \
scribo_primitive_internal_update_graph_link \
scribo_primitive_link_all \
scribo_primitive_link_compute \
scribo_primitive_link_internal_compute_anchor \
scribo_primitive_link_internal_dmax_default \
scribo_primitive_link_internal_dmax_functor_base \
scribo_primitive_link_internal_dmax_hrules \
scribo_primitive_link_internal_dmax_width_and_height \
scribo_primitive_link_internal_dmax_width_only \
scribo_primitive_link_internal_find_link \
scribo_primitive_link_internal_link_functor_base \
scribo_primitive_link_internal_link_several_dmax_base \
scribo_primitive_link_internal_link_single_dmax_base \
scribo_primitive_link_internal_link_single_dmax_ratio_aligned_base \
scribo_primitive_link_internal_link_single_dmax_ratio_aligned_delta_base \
scribo_primitive_link_internal_link_single_dmax_ratio_base \
scribo_primitive_link_merge_double_link \
scribo_primitive_link_merge_double_link_closest_aligned \
scribo_primitive_link_with_graph \
scribo_primitive_link_with_rag \
scribo_primitive_link_with_several_graphes \
scribo_primitive_link_with_several_left_links \
scribo_primitive_link_with_several_right_links \
scribo_primitive_link_with_single_down_link \
scribo_primitive_link_with_single_left_link \
scribo_primitive_link_with_single_left_link_dmax_ratio \
scribo_primitive_link_with_single_left_link_dmax_ratio_aligned \
scribo_primitive_link_with_single_right_link \
scribo_primitive_link_with_single_right_link_bottom \
scribo_primitive_link_with_single_right_link_dmax_ratio \
scribo_primitive_link_with_single_right_link_dmax_ratio_aligned \
scribo_primitive_link_with_single_right_link_top \
scribo_primitive_link_with_single_up_link \
scribo_primitive_merge_components \
scribo_primitive_regroup_from_single_left_link \
scribo_primitive_regroup_from_single_left_link_wrt_h_ratio \
scribo_primitive_remove_separators \
scribo_subsampling_bilinear \
scribo_subsampling_integral \
scribo_subsampling_integral_single_image \
scribo_table_align_lines_horizontaly \
scribo_table_align_lines_verticaly \
scribo_table_all \
scribo_table_connect_horizontal_lines \
scribo_table_connect_vertical_lines \
scribo_table_erase \
scribo_table_extract \
scribo_table_internal_align_lines \
scribo_table_internal_all \
scribo_table_internal_connect_lines \
scribo_table_internal_repair_lines \
scribo_table_rebuild \
scribo_table_repair_horizontal_lines \
scribo_table_repair_vertical_lines \
scribo_text_all \
scribo_text_clean \
scribo_text_clean_inplace \
scribo_text_extract_lines \
scribo_text_extract_lines_with_features \
scribo_text_extract_paragraphs \
scribo_text_extract_paragraphs_hdoc \
scribo_text_link_lines \
scribo_text_look_like_text_lines \
scribo_text_merging \
scribo_text_merging_hdoc \
scribo_text_paragraphs_closing \
scribo_toolchain_internal_text_in_doc_preprocess_functor \
scribo_toolchain_internal_text_in_picture_functor \
scribo_toolchain_internal_toolchain_functor \
scribo_toolchain_text_in_doc_preprocess \
scribo_toolchain_text_in_picture \
scribo_upsampling_bs2x \
scribo_upsampling_eagle \
scribo_util_box_intersection \
scribo_util_box_is_included \
scribo_util_color_to_hex \
scribo_util_component_precise_outline \
scribo_util_compute_sub_domains \
scribo_util_hex_to_color \
scribo_util_init_integral_image \
scribo_util_integral_sub_sum_sum2_functor \
scribo_util_integral_sum_sum2_functor \
scribo_util_integral_sum_sum2_global_min_functor


