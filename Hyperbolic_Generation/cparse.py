from generate_hyperbolic import *

"""
Parses the output of the generate_hyperbolic module 
into a C header file that's referenced as the master
list of vertices and edges.

use:
python3 cparse filename numverts expansion_rate1 expansion_rate2 ...

"""

def read_input():
    """
    reads command line args and parses with
    'make_hyperbolic' in mind.
    """
    import sys
    input_num_verts = int(sys.argv[1])
    expansion_rate =  [int(x) for x in sys.argv[2:]]
    return input_num_verts, expansion_rate

def edgify(out_string, edges):
    restlen = 1
    diag_len = 1.1412135623
    """
    Formats edges to the 'Edge' struct defined in 
    mesh_elements.h
    """
    for i in edges: 
        if i[2] == 1:
            out_string += "{0} {1} {2}\n".format(i[0], i[1], restlen)
        else:
            out_string +=  "{0} {1} {2}\n".format(i[0], i[1], diag_len)

    return out_string

def vertify(out_string, verts):
    """
    Formats verts to the 'Particle' struct
    defined in mesh_elements.h
    """
    for i in verts:
        position = "{0} {1} {2}\n" \
            .format(float(i[0]), float(i[1]), float(i[2])) 
        out_string += position
    return out_string


if __name__ == "__main__":
    readin = read_input()
    verts, edges = make_hyperbolic(readin[0], readin[1])

    constants = \
'#define NUM_PARTICLES {num_verts}\n\
#define NUM_EDGES {num_edges}\n\
\
'.format(num_verts = len(verts), num_edges = len(edges))

    verts = vertify("", verts)
    edges = edgify("", edges)

    with open('verts', 'w+') as v:
        v.write(verts)

    with open('edges', 'w+') as e:
        e.write(edges)

    with open('constants.h', 'w+') as c:
        c.write(constants)
