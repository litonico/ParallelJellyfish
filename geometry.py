from numpy import matrix as npMatrix
from math import *

def degrees_to_radians(angle_in_degrees):
    return (pi/180.0)*angle_in_degrees

def setPerspectiveMatrix(near, far, fov):
    scale = 1/(tan(degrees_to_radians(float(fov)/2.0)))

    persp_matrix = [ [0,0,0,0] for i in range(4) ]
    persp_matrix[0][0] = scale
    persp_matrix[1][1] = scale
    persp_matrix[2][2] = -far/float(far-near)
    persp_matrix[2][3] = -1.0
    persp_matrix[3][2] = -(far*near)/float(far-near)

    return npMatrix(persp_matrix)

def project_vert(persp_matrix, point):
    return (persp_matrix*point).take([0,1]) 

def projectVerts(persp_matrix, points_list, num_points):
    projected_verts = []

    for i in range(num_points):
        projected_verts.append(project_vert(persp_matrix, points[i]))
    
    return projected_verts