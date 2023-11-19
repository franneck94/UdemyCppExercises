import math

import numpy as np
import matplotlib.pyplot as plt


def main() -> int:
    v_long = 3.0
    v_lat = 1.0
    print(f"v_long: {v_long}")
    print(f"v_lat: {v_lat}")

    # since left is negative and right is positive in out coordinate system
    a2 = np.arctan2(v_lat * -1.0, v_long)
    print(f"arctan2: {a2}")
    deg = (a2 / np.pi) * 180.0
    if deg < 0.0:
        deg = deg + 360.0
    print(f"deg: {deg}")

    angle = [deg for _ in range(5)]
    angle = [math.radians(a) for a in angle]
    rs = [i for i in range(5)]
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})
    ax.plot(angle, rs)
    ax.grid(True)
    plt.show()

    return 0


if __name__ == "__main__":
    main()
