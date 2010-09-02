// Copyright (C) 2010 EPITA Research and Development Laboratory (LRDE)
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

#ifndef SCRIBO_DEMO_SHARED_SRC_IMAGE_VIEWER_HH
# define SCRIBO_DEMO_SHARED_SRC_IMAGE_VIEWER_HH

# include <QApplication>
# include <QtCore>
# include <QtGui>

# include <ui_image_viewer.h>

# include <mln/core/image/image2d.hh>
# include <mln/convert/to_qimage.hh>

# include <shared/src/types.hh>
# include <shared/src/internal/interactive_scene.hh>


namespace scribo
{

  namespace demo
  {

    namespace shared
    {

      class image_viewer
	: public QWidget, private Ui::ImageViewer
      {
	Q_OBJECT;

      public:
	image_viewer(QWidget *parent = 0);
	~image_viewer();

	unsigned current_slice() const;

	internal::interactiveScene * scene();
	const internal::interactiveScene * scene() const;

	void clear();

      private: // members
	void setup_scene();

	void draw_image(const mln::image2d<dsp_data_t>& ima);

	void resize_image(const QRectF& rect);

	void keyPressEvent(QKeyEvent *event);
	void resizeEvent(QResizeEvent * event);
//       void mouseMoveEvent(QMouseEvent *e);
//       void mousePressEvent(QMouseEvent *e);
//       void mouseReleasedEvent(QMouseEvent *e);

      private slots:
	void visible_slider(bool b);

	void move_vertical_sliders(int value);
	void move_horizontal_sliders(int value);

	void on_slider_valueChanged(int sli);

	void on_zoomIn_clicked();
	void on_zoomOut_clicked();
	void on_zoomFixed_clicked();
	void on_zoomOriginal_clicked();


      public slots:
	void set_image_layer_count(unsigned nslis);
	void update_image(const mln::image2d<dsp_data_t>& ima);


      signals:
	void slider_valueChanged(int sli);

      private: // attributes
	QGraphicsItem *item_;
	bool mouse_moving_;
	QPoint p_start_;
      };


    } // end of namespace scribo::demo::shared

  } // end of namespace scribo::demo

} // end of namespace scribo


#endif // ! SCRIBO_DEMO_SHARED_SRC_IMAGE_VIEWER_HH