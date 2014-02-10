# adapted from the pyGame OBJ file loader

def LoadObj(filename):
    '''
    Takes a file with extention .obj
    Returns a tuple of (verts, edges, faces)
    normals and tex coords are discarded
    '''
    verticies = []
    edges = []
    faces = []

    with open(filename) as objfile:
        for line in objfile:
            words = line.split()
            if not words:
                continue

            if words[0] == 'v': # a vertex
                verticies.append(
                        list(words[1],words[2],words[3])
                    )

            elif words[0] == 'f': # a face
                current_face = []
                current_edge = []
                next_edge = []

                for face_descriptions in words[1:]: 
                    # each face is in the form of
                    # vertex1/texturecoord1/normal1 vertex2/texturecoord2/normal2 etc.
                    face_triplets = face_descriptions.split()
                    vert = face_triplets[0]
                    # ignoring tex coords and normals
                    current_face.append(vert)

                    if prev_vert:
                        edges.append(
                            list(prev_vert, vert)
                            )
                    prev_vert = vert

                faces.append(current_face)

                edges.append(
                    list(current_face[-1], current_face[0]) # join the final verts
                    )

    return tuple(verticies, edges, faces)

