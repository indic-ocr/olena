// Copyright (C) 2013 EPITA Research and Development Laboratory (LRDE)
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

#undef MLN_WO_GLOBAL_VARS

#include <QtGui/QApplication>

#include <scribo/make/debug_filename.hh>
#include <mln/labeling/colorize.hh>
#include <mln/io/magick/load.hh>
#include <mln/debug/filename.hh>
#include <mln/literal/colors.hh>
#include <scribo/binarization/sauvola_ms.hh>
#include <mln/math/pi.hh>

#include "mainwindow.hh"

int main(int argc, char *argv[])
{
    Magick::InitializeMagick(*argv);
    // On Linux, we NEED to use the raster graphics system.
    // Linux don't really support openGL graphics system (the default one on Linux).
    QApplication::setGraphicsSystem("raster");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
