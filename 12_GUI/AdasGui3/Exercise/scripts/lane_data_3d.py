import copy
import os
import json
from typing import TypedDict

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


np.random.seed(42)


DATA_FILENAME = "lane_data.json"
GIF_FILENAME = "example.gif"

DATA_PATH = os.path.join(os.path.dirname(os.path.dirname(__file__)), "data")
DATA_FILEPATH = os.path.join(DATA_PATH, DATA_FILENAME)
GIF_FILEPATH = os.path.join(DATA_PATH, GIF_FILENAME)


class Poly3(TypedDict):
    a: float
    b: float
    c: float
    d: float


POLY = Poly3(a=0.0, b=0.0, c=0.0, d=0.0)

fig, ax = plt.subplots()
p2 = POLY


def p(x: np.ndarray, poly: Poly3) -> np.ndarray:
    y = (poly['a']*x)**3 + (poly['b']*x)**2 + (poly['c']*x)**1 + poly['d']
    return y


def pertubation(scale: float = 0.1):
    eps = np.random.normal(scale=scale)
    return eps


def update(frame: int):
    x = np.linspace(start=0.0, stop=100.0, num=50)
    ax.clear()
    plt.xlim(-100.0, 100.0)
    plt.ylim(-5.0, 5.0)
    plt.yticks([-4.5, -1.5, 0.0, 1.5, 4.5])
    plt.hlines(y=-4.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=-1.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=1.5, xmin=-100.0, xmax=0.0, colors='black')
    plt.hlines(y=4.5, xmin=-100.0, xmax=0.0, colors='black')
    p2['a'] += pertubation(scale=0.00001)
    p2['b'] += pertubation(scale=0.00020)
    p2['c'] += pertubation(scale=0.00010)
    a = round(p2['a'], 5)
    b = round(p2['b'], 5)
    c = round(p2['c'], 5)
    title_str = (
        f'p(x) = {a}$x^3$ + {b}$x^2$ + {c}$x^1$ + $x_0$'
    )
    plt.title(title_str)
    p2['d'] = -4.5
    y = p(x, p2)
    plt.plot(x, y, color="black")
    p2['d'] = -1.5
    y = p(x, p2)
    plt.plot(x, y, color="black")
    p2['d'] = 1.5
    y = p(x, p2)
    plt.plot(x, y, color="black")
    p2['d'] = 4.5
    y = p(x, p2)
    plt.plot(x, y, color="black")
    plt.gca().invert_yaxis()
    return ax


def generate_data(num_frames: int):
    lane_data = {i: {j: {k: Poly3(a=0.0, b=0.0, c=0.0, d=0.0)
                 for k in range(num_frames)} for j in range(2)} for i in range(3)}
    p2 = POLY
    for i in range(num_frames):
        p2['a'] += pertubation(scale=0.00001)
        p2['b'] += pertubation(scale=0.00020)
        p2['c'] += pertubation(scale=0.00010)
        p2['a'] = round(p2['a'], 5)
        p2['b'] = round(p2['b'], 5)
        p2['c'] = round(p2['c'], 5)
        # Left lane
        p2['d'] = -4.5
        lane_data[0][0][i] = copy.deepcopy(p2)
        p2['d'] = -1.5
        lane_data[0][1][i] = copy.deepcopy(p2)
        # Center lane
        p2['d'] = -1.5
        lane_data[1][0][i] = copy.deepcopy(p2)
        p2['d'] = 1.5
        lane_data[1][1][i] = copy.deepcopy(p2)
        # Right lane
        p2['d'] = 1.5
        lane_data[2][0][i] = copy.deepcopy(p2)
        p2['d'] = 4.5
        lane_data[2][1][i] = copy.deepcopy(p2)
    return lane_data


def animation():
    animation = FuncAnimation(fig, update, frames=200)
    animation.save(GIF_FILEPATH)


def main() -> int:
    # animation()
    lane_data = generate_data(num_frames=1000)
    with open(DATA_FILEPATH, "w") as file_object:
        json.dump(lane_data, file_object)
    return 0


if __name__ == "__main__":
    main()
