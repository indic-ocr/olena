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

# include <variantpointer.hh>


template<typename T>
VariantPointer<T>::VariantPointer()
{
}


template<typename T>
QVariant
VariantPointer<T>::toQVariant(T *pointer)
{
  return QVariant::fromValue(static_cast<void *>(pointer));
}


template<typename T>
T *
VariantPointer<T>::fromQVariant(const QVariant& variant)
{
  return static_cast<T *>(variant.value<void *>());
}
