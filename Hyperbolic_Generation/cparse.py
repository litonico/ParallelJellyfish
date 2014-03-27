from generate_hyperbolic import *

"""
Parses the output of the generate_hyperbolic module 
into a data file that's referenced as the master
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

def edgify(edges):
    restlen = 1.0 
    diag_len = 1.1412135623 

    """
    Formats edges to the 'Edge' struct defined in 
    mesh_elements.h
    """
    out_string = ""

    for i in edges: 
        if i[2] == 1:
            out_string += "{0} {1} {2}\n".format(i[0], i[1], restlen)
        else:
            out_string +=  "{0} {1} {2}\n".format(i[0], i[1], diag_len)

    return out_string

def vertify(verts):
    """
    Formats verts to the 'Particle' struct
    defined in mesh_elements.h
    """
    out_string = ""

    for i in verts:
        position = "{0} {1} {2}" \
            .format(float(i[0]), float(i[1]), float(i[2])) 
        # inlcude both position before and after
        out_string += "{0} {1}\n".format(position, position)

    return out_string

def faceify(faces):
    """
    Formats faces for the .obj file format.
    """
    out_string = ""

    for face in faces:
        out_string += "f {0} {1} {2}\n" \
            .format(face[0]+1, face[1]+1, face[2]+1) 
            # .obj files start verts from 1, not 0
        
    return out_string

def adjacency_list(edges, num_verts): 
    A = {x:[] for x in range(num_verts)}
    for edge in edges:
        if edge[1] not in A[edge[0]]:
            A[edge[0]].append(edge[1])
        if edge[0] not in A[edge[1]]:
            A[edge[1]].append(edge[0])
    return A

def find_faces(verts, edges): 
    # could be done with just graph, but this is simpler

    """
    Finds the faces of an all-triangle mesh given the
    verts and edges. Uses the adjacency_list function
    to generate the graph.
    Could be tweaked to find face-pairs
    """
    graph = adjacency_list(edges, len(verts))
    
    faces = []
    facepairs = []
    for edge in edges:
        a = edge[0]
        b = edge[1]
        common_verts = set(graph[a]).intersection(set(graph[b]))


        facepair = []
        for i in common_verts:
            if i == a or i == b:
                break
            face = sorted([a, b, i])

            facepair.append(face)

            if face not in faces:
                faces.append(face)

        facepairs.append(facepair) 

    return faces, facepairs


# def faceify(out_string, verts, edges):
#     faces, face-pairs = find_faces(verts, edges)
    

if __name__ == "__main__":
    try:
        readin = read_input()
        verts, edges = make_hyperbolic(readin[0], readin[1])
    except:
        verts, edges = make_hyperbolic(5, [2, 2]) # testing conditions
    datapath = 'data'    

    # TODO: kill- print(find_faces(adjacency_list(edges, len(verts)), edges))

    verts_str = vertify(verts)
    edges_str = edgify(edges)
    faces, facepairs = find_faces(verts, edges)
    faces_str = faceify(faces)

    num_verts = len(verts)
    num_edges  = len(edges)

    # Save verts, edges, and face-pairs for the C module
    with open('{path}/verts'.format(path = datapath), 'w+') as v:
        v.write(str(num_verts) + "\n")
        v.write(verts_str)

    with open('{path}/edges'.format(path = datapath), 'w+') as e:
        e.write(str(num_edges) + "\n")
        e.write(edges_str)

    # with open('{path}/faces'.format(path = datapath+"/tmp") 'w+') as fp:
    #    fp.write(faces_str)

    # Save faces for later, to make the .obj file
    with open('{path}/tmp/faces'.format(path = datapath), 'w+') as f:
        f.write(faces_str)
