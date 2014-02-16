from generate_hyperbolic import *

# use:
# python3 cparse filename numverts expansion_rate1 expansion_rate2 ...

def read_input():
    """reads command line args and parses with
    'make_hyperbolic' in mind. """
    import sys
    filename = sys.argv[1]
    input_num_verts = int(sys.argv[2])
    expansion_rate =  [int(x) for x in sys.argv[3:]]
    return filename, input_num_verts, expansion_rate

def edgify(out_string, edges):
    """Formats edges to the 'Edge' struct defined in 
    mesh_elements.h"""
    out_string += "Edge edges[] = {\n    "

    out_string += ', '.join(
        ("{{{0}, {1}, {2}}}".format(i[0], i[1], 'diagonal_length') 
            ) for i in edges)
    out_string += "}\n"
    return out_string

def vertify(out_string, verts):
    """Formats verts to the 'Particle' struct
    defined in mesh_elements.h"""
    out_string += "Particle verts[] = {\n    "
    for i in verts:
        position = "{{{0}, {1}, {2}}}" \
            .format(float(i[0]), float(i[1]), float(i[2])) 
        out_string += "{{{0}, {1}}}, ".format(position, position)
    out_string = out_string[:-2] + "\n}\n" # remove the final comma and add the last brace
    return out_string


if __name__ == "__main__":
    readin = read_input()
    filename = readin[0]
    verts, edges = make_hyperbolic(readin[1], readin[2])

    output = \
'#ifndef {name}_h\n\
#define {name}_h\n\
#include "struct_vectormath.h"\n\
#include "mesh_elements.h"\n\
#define DIAGONAL 1.41421356237\n\
\n\
double diagonal_length = DIAGONAL;\n\
int num_particles = {num_verts};\n\
int num_edges = {num_edges};\n\n\
\
'.format(name = filename, num_verts = len(verts), num_edges = len(edges))

    output = vertify(output, verts)
    output = edgify(output, edges)
    output += "#endif"

    with open('{0}.h'.format(filename), 'w+') as f:
        f.write(output)
