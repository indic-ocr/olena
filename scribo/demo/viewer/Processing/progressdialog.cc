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

#include "progressdialog.hh"

ProgressDialog::ProgressDialog(QWidget *parent):
        QProgressDialog(parent, Qt::Dialog)
{
    setAutoClose(false);
    setCancelButton(0);
    hide();
}

void ProgressDialog::reset()
{
    setValue(0);
    setLabelText("Initilization");
    show();
}

void ProgressDialog::run()
{
  setValue(value()+1);
}
