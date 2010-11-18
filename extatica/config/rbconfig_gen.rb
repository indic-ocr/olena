# Copyright (C) 2005 EPITA Research and Development Laboratory (LRDE).
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

require 'rbconfig'

def gen_m4 ( config )
  config.each_key do |k|
    name = "RUBY_#{k}"
    puts %Q{
      AC_SUBST([#{name}],
        RUBY([
          val = Config::CONFIG[%q[#{k}]]
          val = val.to_s.gsub(%q['], %q['"'"'])
          %q{['} + val + %q{']}
        ]))
      AC_DEFINE([#{name}], $#{name},
        [Contains Config::CONFIG['#{k}'] (generated by rbconfig_gen.rb)])
    }
  end
end

gen_m4(Config::CONFIG)