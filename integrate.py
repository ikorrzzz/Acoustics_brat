import numpy as np



def recur():
    res = 0
    for points in points:
        res += integrate(f, points)


def integrate(f, points, data=None):
    A, B, C = points[0], points[1], points[2]
    colloc_point = (A+B+C)/3
    b = np.array(B - A)
    c = np.array(C - A)
    res = f(colloc_point, data) * abs(np.cross(b,c)) / 2
    
    return res



