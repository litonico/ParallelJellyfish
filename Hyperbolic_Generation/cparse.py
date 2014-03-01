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
    restlen = 1.0 
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
        position = "{0} {1} {2}" \
            .format(float(i[0]), float(i[1]), float(i[2])) 
        out_string += "{0} {1}\n".format(position, position)
    return out_string


if __name__ == "__main__":
    try:
        readin = read_input()
        verts, edges = make_hyperbolic(readin[0], readin[1])
    except:
        verts, edges = make_hyperbolic(5, [2,2]) # testing conditions
    datapath = '../data'    
    cpath = '../Springs'

    constants = \
'#define NUM_PARTICLES {num_verts}\n\
#define NUM_EDGES {num_edges}\n\
\
'.format(num_verts = len(verts), num_edges = len(edges))

    verts_str = vertify("", verts)
    edges_str = edgify("", edges)

    num_verts = len(verts)
    num_edges  = len(edges)

    with open('{path}/verts'.format(path = datapath), 'w+') as v:
        v.write(str(num_verts) + "\n")
        v.write(verts_str)

    with open('{path}/edges'.format(path = datapath), 'w+') as e:
        e.write(str(num_edges) + "\n")
        e.write(edges_str)

    # with open('{path}/constants.h'.format(path = cpath), 'w+') as c:
    #    c.write(constants)
