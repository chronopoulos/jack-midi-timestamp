#!/usr/bin/env python2

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
