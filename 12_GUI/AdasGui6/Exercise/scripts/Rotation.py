from typing import Tuple
import math

import numpy as np
import matplotlib.pyplot as plt


def rotate_point(
    alpha: float, x: float, y: float, cx: float, cy: float
) -> Tuple[float, float]:
    c = math.cos(alpha)
    s = math.sin(alpha)

    x -= cx
    y -= cy

    x_s = x * c - y * s
    y_s = x * s + y * c

    x_s += cx
    y_s += cy

    return (x_s, y_s)


def main() -> int:
    deg = 45.0
    rad = math.radians(deg)

    xs = [23.774, 28.774]
    ys1 = [-2.213, -2.213]
    ys2 = [-3.213, -3.213]

    plt.scatter(xs, ys1, c="blue")
    plt.scatter(xs, ys2, c="blue")

    cx = np.mean(xs)
    cy = np.mean([ys1[0], ys2[0]])

    _, ys1[0] = rotate_point(rad, xs[0], ys1[0], cx, cy)
    _, ys1[1] = rotate_point(rad, xs[1], ys1[1], cx, cy)
    xs[0], ys2[0] = rotate_point(rad, xs[0], ys2[0], cx, cy)
    xs[1], ys2[1] = rotate_point(rad, xs[1], ys2[1], cx, cy)
    plt.scatter(xs[0], ys1[0], c="red")
    plt.scatter(xs[1], ys1[1], c="red")
    plt.scatter(xs[0], ys2[0], c="red")
    plt.scatter(xs[1], ys2[1], c="red")

    plt.show()

    return 0


if __name__ == "__main__":
    main()
