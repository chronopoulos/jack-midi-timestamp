#!/usr/bin/env python2

"""
Copyright 2018, 2019 Chris Chronopoulos

This file is part of jack-midi-timestamp.

jack-midi-timestamp is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

jack-midi-timestamp is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
jack-midi-timestamp. If not, see <https://www.gnu.org/licenses/>. 
"""


import numpy as np
import matplotlib.pyplot as plt
import sys

if len(sys.argv) > 1:
    logfile = sys.argv[1]
else:
    print 'Usage: %s <logfile>' % sys.argv[0]
    sys.exit(1)

data = np.loadtxt(logfile)
diff = np.diff(data)
mean = np.mean(diff)
std = np.std(diff)

print 'mean = ', mean
print 'std = ', std

plt.hist(diff, bins=100)
plt.show()
