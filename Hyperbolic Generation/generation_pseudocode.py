# y
# o-o-oo-o
# | | |/ |
# o-o-o--o- x

# master_vertlist 
# list previous_vertlist [v1, v2, ...]
# list expansion_rate [rate1, rate2, ...]

# input: number of verts in the first row and a list of expansion rates

def generate_vertlist(num_verts):
    """Generate an initial list of verts and edges"""
    vertlist = []
    edges = []

    for i in range(num_verts):
        vertlist.append([0, 0, i])
        if i < (num_verts - 1):
            edges.append([i, i+1])
        previous_vertex = i

    return vertlist, edges

def offset_vertex(vert_coords, offset = 0):
    new_vert = [0, vert_coords[1] + 1, vert_coords[2] + offset]
    return new_vert

def read_input():
    """reads command line args and parses with 
    'make_hyperbolic' in mind. """
    import sys
    input_num_verts = int(sys.argv[1])
    expansion_rate =  [int(x) for x in sys.argv[2:]]
    return input_num_verts, expansion_rate

def make_hyperbolic(input_num_verts, expansion_rate):
    rows = len(expansion_rate)
    print( "Generating Initial Vertex List" )
    master_vertlist, edges = generate_vertlist(input_num_verts)
    
    # maintains the verts as [[x, y, z], ...]
    # edges as [[v1, v2], ...] form

    current_vertlist = [x for x in range(len(master_vertlist))]
    next_vertlist = []
    num_verts = len(master_vertlist)
    
    for row in range(1, rows): # to exclude the already-made row
        print ("Calculating Row " + str(row))
        row_beginning = True

        for current_vertex, current_vert_position in enumerate(current_vertlist):

            if (current_vert_position + 1) % expansion_rate[row] == 0:
                for k in range(2):
                    
                    new_vertex_coords = offset_vertex(master_vertlist[current_vertex], 0.5*k)
                    
                    master_vertlist.append(new_vertex_coords)

                    num_verts += 1
                    new_vertex_number = num_verts 

                    next_vertlist.append(new_vertex_number)

                    if not row_beginning:
                        #stitch to previously-created vert
                        edges.append([new_vertex_number-1, new_vertex_number])

                    #stitch to previous row
                    edges.append([current_vert_position, new_vertex_number])
                    #end
                    row_beginning = False
            else:
                # add and connect new verts routine
                # determine position of vert and create it
                new_vertex_coords = offset_vertex(master_vertlist[current_vertex])
                # add to master list
                master_vertlist.append(new_vertex_coords)

                num_verts += 1
                new_vertex_number = num_verts 
                # add to maintained vertlist
                next_vertlist.append(new_vertex_number)

                if not row_beginning:
                    #stitch to previously-created vert
                    edges.append([new_vertex_number-1, new_vertex_number])

                #stitch to previous row
                edges.append([current_vert_position, new_vertex_number])
                #end
                row_beginning = False


            # move to next line
            current_vertlist = next_vertlist



    return master_vertlist, edges 


if __name__ == "__main__":
    print(make_hyperbolic(read_input()[0], read_input()[1]))