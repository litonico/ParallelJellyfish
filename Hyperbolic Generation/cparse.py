
def edgify:
    output = "Edge edges[] = {"
    for i in edges:
        output +=  "{%s, %s, %s},", i

    output += "}"

