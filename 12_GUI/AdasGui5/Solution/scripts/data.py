import os
import json
import enum
from typing import Any
from typing import Dict

import numpy as np


class LaneAssociation(enum.Enum):
    LEFT = 0
    CENTER = 1
    RIGHT = 2
    NONE = 3


class ObjectClass(enum.Enum):
    CAR = 0
    TRUCK = 1
    MOTORBIKE = 2
    NONE = 4


NUM_VEHICLES = 6
NUM_ITERATIONS = 1_000
FRAME_DURATION_MS = 50
FRAME_DURATION_S = FRAME_DURATION_MS / 1000.0

VEHICLE_FILENAME = "vehicle_data.json"
VEHICLE_FILEPATH = os.path.join(
    os.path.dirname(os.path.dirname(__file__)), "data", VEHICLE_FILENAME
)

EGO_FILENAME = "ego_data.json"
EGO_VEHICLE_FILEPATH = os.path.join(
    os.path.dirname(os.path.dirname(__file__)), "data", EGO_FILENAME
)

np.random.seed(42)


OBJECT_CLASSES = {
    0: int(ObjectClass.CAR.value),
    1: int(ObjectClass.CAR.value),
    2: int(ObjectClass.CAR.value),
    3: int(ObjectClass.MOTORBIKE.value),
    4: int(ObjectClass.CAR.value),
    5: int(ObjectClass.TRUCK.value),
}


OBJECT_WIDTHS = {
    0: 2.5,
    1: 3.25,
    2: 0.5
}


OBJECT_HEIGHTS = {
    0: 5.0,
    1: 15.0,
    2: 2.0
}


def kph_to_mps(kph: float) -> float:
    return kph / 3.6


def generate_ego_vehicle_data() -> Dict[str, list]:
    start_speed_mps = round(kph_to_mps(120), 3)
    start_lane = int(LaneAssociation.CENTER.value)

    ego_vehicle_data: Dict[str, list] = {
        "Lane": [1 for _ in range(NUM_ITERATIONS)],
        "Velocity": [0.0 for _ in range(NUM_ITERATIONS)],
    }

    ego_vehicle_data["Lane"][0] = start_lane
    ego_vehicle_data["Velocity"][0] = start_speed_mps

    for i in range(1, NUM_ITERATIONS):
        ego_vehicle_data["Lane"][i] = int(LaneAssociation.CENTER.value)
        eps = np.random.normal(loc=0.0, scale=0.5)
        new_speed = ego_vehicle_data["Velocity"][i - 1] + eps
        if new_speed >= 25.0 and new_speed <= 40.0:
            ego_vehicle_data["Velocity"][i] = round(new_speed, 3)
        else:
            ego_vehicle_data["Velocity"][i] = ego_vehicle_data["Velocity"][i - 1]

    return ego_vehicle_data


def generate_vehicle_data(id_: int, ego_speed_mps) -> dict:
    if id_ < 2:
        start_lane_associations = int(LaneAssociation.LEFT.value)
        start_speed = round(np.random.uniform(110, 130), 3)
        start_lat_distance = round(np.random.normal(loc=-3.0, scale=0.5), 3)
    elif id_ < 4:
        start_lane_associations = int(LaneAssociation.CENTER.value)
        start_speed = round(np.random.uniform(105, 125), 3)
        start_lat_distance = round(np.random.normal(loc=0.0, scale=0.5), 3)
    else:
        start_lane_associations = int(LaneAssociation.RIGHT.value)
        start_speed = round(np.random.uniform(100, 120), 3)
        start_lat_distance = round(np.random.normal(loc=3.0, scale=0.5), 3)

    if id_ == 0 or id_ == 2 or id_ == 4:
        start_long_distance = round(np.random.uniform(20, 80), 3)

    elif id_ == 1 or id_ == 3 or id_ == 5:
        start_long_distance = round(np.random.uniform(-80, -20), 3)

    start_speed = round(kph_to_mps(start_speed), 3)

    speed_data = [start_speed for _ in range(NUM_ITERATIONS)]
    for it in range(1, NUM_ITERATIONS):
        eps = np.random.normal(loc=0.0, scale=0.1)
        new_speed = speed_data[it - 1] + eps
        if new_speed >= 20.0 and new_speed <= 40.0:
            speed_data[it] = round(new_speed, 3)
        else:
            speed_data[it] = round(speed_data[it - 1], 3)

    long_distances = [0.0 for _ in range(NUM_ITERATIONS)]
    lat_distances = [0.0 for _ in range(NUM_ITERATIONS)]

    long_distances[0] = start_long_distance
    lat_distances[0] = start_lat_distance

    for it in range(1, NUM_ITERATIONS):
        ego_driven_distance_m = FRAME_DURATION_S * ego_speed_mps[it - 1]
        driven_distance_m = FRAME_DURATION_S * speed_data[it - 1]
        long_distances[it] = round(
            long_distances[it - 1]
            + (driven_distance_m - ego_driven_distance_m),
            2,
        )
        eps = np.random.normal(loc=0.0, scale=0.01)
        lat_distances[it] = round(lat_distances[it - 1] + eps, 4)

    lanes = [start_lane_associations for _ in range(NUM_ITERATIONS)]

    for it, lat_distance in enumerate(lat_distances, start=1):
        if -4.5 <= lat_distance <= -1.5:
            lanes[it - 1] = int(LaneAssociation.LEFT.value)
        elif -1.5 < lat_distance <= 1.5:
            lanes[it - 1] = int(LaneAssociation.CENTER.value)
        elif 1.5 < lat_distance <= 4.5:
            lanes[it - 1] = int(LaneAssociation.RIGHT.value)
        else:
            lanes[it - 1] = int(LaneAssociation.NONE.value)

    data_dict = {
        "Lane": lanes,
        "LongDistance": long_distances,
        "LatDistance": lat_distances,
        "ObjectClass": OBJECT_CLASSES[id_],
        "Velocity": speed_data,
        "Width": OBJECT_WIDTHS[OBJECT_CLASSES[id_]],
        "Height": OBJECT_HEIGHTS[OBJECT_CLASSES[id_]],
    }
    return data_dict


def main() -> int:
    ego_vehicle_data = generate_ego_vehicle_data()

    with open(EGO_VEHICLE_FILEPATH, "w") as file_object:
        json.dump(ego_vehicle_data, file_object)

    vehicle_datas: Dict[int, Dict[int, Any]] = {
        idx: {} for idx in range(NUM_VEHICLES)
    }
    for i in range(NUM_VEHICLES):
        data = generate_vehicle_data(i, ego_vehicle_data["Velocity"])
        vehicle_datas[i] = data

    with open(VEHICLE_FILEPATH, "w") as file_object:
        json.dump(vehicle_datas, file_object)

    return 0


if __name__ == "__main__":
    main()
