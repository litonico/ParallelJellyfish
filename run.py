#!/usr/bin/env python

import os
import sys

if len(sys.argv) > 1:
    # If passed args, use those
    os.system("python3 Hyperbolic_Generation/cparse.py " + " ".join(sys.argv[1:]))
else:
    print("Please provide arguments")
    sys.exit()

# Run the simulation
os.system("./Springs/Jellyfish")

# concatenate the verts and faces to form a .obj file
os.system("cat ./data/tmp/obj ./data/tmp/faces > ./JellyfishTmp.obj")

# cleanup
# os.system("rm ./data/tmp/obj ./data/tmp/faces ./data/verts ./data/edges")
