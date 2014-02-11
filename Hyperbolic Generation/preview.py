from graphics import *
from generate_hyperbolic import *

verts, edges = make_hyperbolic(5,[0,2])
radius = 2
scale = 20
offset = 10

for i in edges:
    assert(len(i) == 2)
    # assert((i[0] >= len(verts)) and (i[1] >= len(verts)))

win = GraphWin("Hyperbolic Preview", 500, 500)

for k in verts: # scale verts
    k[1] = k[1]*scale + offset
    k[2] = k[2]*scale + offset

for j in verts: # draw verts
    Circle(Point(j[1], j[2]), radius).draw(win)

for i in edges: # draw edges
    v1 = verts[i[0]]
    try:
        v2 = verts[i[1]]
        Line(Point(v1[1], v1[2]), Point(v2[1], v2[2])).draw(win)
    except:
        pass

win.getMouse()
