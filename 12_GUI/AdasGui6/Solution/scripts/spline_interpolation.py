from typing import List

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import CubicSpline

np.random.seed(42)


def f(
    i: int,
    x: float,
    x_: List[float],
    a: List[float],
    b: List[float],
    c: List[float],
    d: List[float],
) -> float:
    return (
        a[i] * (x - x_[i]) ** 3
        + b[i] * (x - x_[i]) ** 2
        + c[i] * (x - x_[i]) ** 1
        + d[i]
    )


def main():
    s0 = [00.0, -0.0]
    s1 = [15.0, -1.5]
    s2 = [30.0, -2.5]
    s3 = [45.0, -3.0]

    plt.scatter(s0[0], s0[1], c="blue")
    plt.scatter(s1[0], s1[1], c="blue")
    plt.scatter(s2[0], s2[1], c="blue")
    plt.scatter(s3[0], s3[1], c="blue")
    plt.hlines(-1.5, xmin=0.0, xmax=50.0)
    plt.hlines(-4.5, xmin=0.0, xmax=50.0)
    plt.hlines(1.5, xmin=0.0, xmax=50.0)
    plt.xlim([0.0, 50.0])
    plt.ylim([-4.5, 4.5])

    x = np.zeros(shape=(4))
    x[0] = s0[0]
    x[1] = s1[0]
    x[2] = s2[0]
    x[3] = s3[0]
    y = np.zeros(shape=(4))
    y[0] = s0[1]
    y[1] = s1[1]
    y[2] = s2[1]
    y[3] = s3[1]

    h = np.zeros(shape=(4))
    h[0] = x[1] - x[0]
    h[1] = x[2] - x[1]
    h[2] = x[3] - x[2]
    h[3] = 0.0

    M = np.array([[2 * (h[0] + h[1]), h[1]], [h[1], 2 * (h[1] + h[2])]])
    N = np.zeros(shape=(2), dtype=np.float32)
    N[0] = ((6.0 / h[1]) * (y[2] - y[1])) - ((6.0 / h[0]) * (y[1] - y[0]))
    N[1] = ((6.0 / h[2]) * (y[3] - y[2])) - ((6.0 / h[1]) * (y[2] - y[1]))

    print(M)
    print(N)

    y_ss = np.zeros(shape=(4))
    a = np.zeros(shape=(4))
    b = np.zeros(shape=(4))
    c = np.zeros(shape=(4))
    d = np.zeros(shape=(4))
    y_ss[1:3] = np.dot(np.linalg.inv(M), N)

    for i in range(3):
        a[i] = (1.0 / (6.0 * h[i])) * (y_ss[i + 1] - y_ss[i])
        b[i] = 0.5 * y_ss[i]
        c[i] = (1.0 / h[i]) * (y[i + 1] - y[i]) - (1 / 6) * (
            y_ss[i + 1] + 2 * y_ss[i]
        )
        d[i] = y[i]

    print("a: ", a)
    print("b: ", b)
    print("c: ", c)
    print("d: ", d)

    xx = np.linspace(start=0.0, stop=x[3], num=100)
    for xx_i in xx:
        if xx_i <= x[1]:
            yy_i = f(0, xx_i, x, a, b, c, d)
            plt.scatter(xx_i, yy_i, c="red", s=5)
        elif xx_i <= x[2]:
            yy_i = f(1, xx_i, x, a, b, c, d)
            plt.scatter(xx_i, yy_i, c="orange", s=5)
        elif xx_i <= x[3]:
            yy_i = f(2, xx_i, x, a, b, c, d)
            plt.scatter(xx_i, yy_i, c="darkorange", s=5)

    plt.gca().invert_yaxis()
    plt.show()

    cs = CubicSpline(x, y)
    plt.scatter(s0[0], s0[1], c="blue")
    plt.scatter(s1[0], s1[1], c="blue")
    plt.scatter(s2[0], s2[1], c="blue")
    plt.scatter(s3[0], s3[1], c="blue")
    plt.hlines(-1.5, xmin=0.0, xmax=50.0)
    plt.hlines(-4.5, xmin=0.0, xmax=50.0)
    plt.hlines(1.5, xmin=0.0, xmax=50.0)
    plt.xlim([0.0, 50.0])
    plt.ylim([-4.5, 4.5])
    plt.plot(xx, cs(xx), '--')
    plt.gca().invert_yaxis()
    plt.show()
    for i in range(3):
        print("Poly ", i)
        for k in range(3, -1, -1):
            print(round(cs.c.T[i, k], 4))


if __name__ == "__main__":
    main()
