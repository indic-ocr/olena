# Copyright (C) 2009, 2010 EPITA Research and Development Laboratory
# (LRDE).
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

MILENA_CPPFLAGS = @MILENA_CPPFLAGS@

# Add paths to Scribo's and Milena's headers.
AM_CPPFLAGS =					\
  -I$(top_srcdir)				\
  -I$(top_builddir)				\
  $(MILENA_CPPFLAGS)

SCRIBO_CXXFLAGS = @SCRIBO_CXXFLAGS@
AM_CXXFLAGS = $(SCRIBO_CXXFLAGS)
