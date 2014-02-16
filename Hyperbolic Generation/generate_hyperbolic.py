"""
Creates the framework of a hyperbolic plane in R2,
which can then be passed to the cparse module 
and on to the spring simulation. 

The verts in this case correspond to cells, while
the edges correspond to the cell walls. This
algorithm is deterministic, but a probablistic
simulation would be pretty easy to implement 
(I think- I haven't tried it!)

The num_verts parameter controls the number of verts
in the first row.

The expansion_rate parameter is a list of values
that determine when a vertex will spawn two verts
rather than just one. A value of 5 will mean that
there will be a split every 5th vertex. The number
of items in the list determines the number of rows
in the mesh.

The output will look something like this:
y
o-o-oo-o
| | |/ |
o-o-o--o- x

input: number of verts in the first row and a list of expansion rates
"""
j
from math import sqrt

def generate_vertlist(num_verts, edgelen = 1):
    """Generate an initial list of verts and edges"""
    vertlist = []
    edges = []

    for i in range(num_verts):
        vertlist.append([0, 0, i])
        if i < (num_verts - 1):
            edges.append([i, i+1, edgelen])
        previous_vertex = i

    return vertlist, edges

def offset_vertex(vert_coords, offset = 0):
    new_vert = [0, vert_coords[1] + 1, vert_coords[2] + offset]
    return new_vert

def make_hyperbolic(input_num_verts, expansion_rate, edgelen = 1):
    rows = len(expansion_rate) + 1 # the expansion rate does not include the first row
    print( "Generating initial vertex list" )
    master_vertlist, edges = generate_vertlist(input_num_verts)

    # maintains the verts as [[x, y, z], ...]
    # edges as [[v1, v2], ...]

    diagonal_edgelen = edgelen*(2/sqrt(2))

    current_vertlist = [x for x in range(len(master_vertlist))]
    num_verts = len(master_vertlist)

    for row in range(1, rows): # to exclude the already-made row
        row_len = len(current_vertlist)
        next_vertlist = []
        row_beginning = True
        print ("Calculating Row " + str(row))
        
        for current_vertex, current_vert_position in enumerate(current_vertlist):

            if expansion_rate[row-1] == 0: 
            # catch the case where there is no expansion
                split = False
            elif ((current_vert_position + 1)) % expansion_rate[row-1] == 0:
                split = True
            else:
                split = False
        
            if split:
                for k in range(2):
                    new_vertex_coords = offset_vertex(
                        master_vertlist[current_vert_position], 
                        k*(1.0/float(row*2))
                        )

                    master_vertlist.append(new_vertex_coords)
                    new_vertex_number = num_verts
                    next_vertlist.append(new_vertex_number)

                    if not row_beginning:
                        edges.append([new_vertex_number-1, new_vertex_number, edgelen])

                    # stitch to previous row
                    edges.append([current_vert_position, new_vertex_number, edgelen])

                    # create the diagonal edge
                    if k == 0 and not row_beginning:
                        try: # cheating with exceptions
                            edges.append([current_vert_position-1, new_vertex_number, diagonal_edgelen])
                        except:
                            pass


                    num_verts += 1
                    row_beginning = False
            else:
                # determine position of vert and create it
                new_vertex_coords = offset_vertex(master_vertlist[current_vert_position])

                master_vertlist.append(new_vertex_coords)

                new_vertex_number = num_verts
                next_vertlist.append(new_vertex_number)

                if not row_beginning:
                    edges.append([new_vertex_number-1, new_vertex_number, edgelen])

                #stitch to previous row
                edges.append([current_vert_position, new_vertex_number, edgelen])

                # create the diagonal edge
                if not row_beginning:
                    try: # cheating with exceptions
                        edges.append([current_vert_position-1, new_vertex_number, diagonal_edgelen])
                    except:
                        pass

                num_verts += 1
                row_beginning = False

        # move to next line
        current_vertlist = [x for x in next_vertlist] # the right way to copy lists

    return master_vertlist, edges


if __name__ == "__main__":
    print(make_hyperbolic(5, [2,2]))
    #print(make_hyperbolic(read_input()[0], read_input()[1]))
