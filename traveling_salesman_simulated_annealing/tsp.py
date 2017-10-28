import math
import random

from point import Point

class TSP:
    _initial_temperature = 1.0

    """ How many times do we cool: make higher to improve quality, lower to
    speed the program up. Move in tandem with the _cooling_fraction."""
    _cooling_steps = 500

    """How much to cool each time: make higher to improve quality, lower to
       speed the program up."""
    _cooling_fraction = 0.97

    """Lower makes it faster, higher makes it potentially better."""
    _steps_per_temp = 1000

    """Problem specific Boltzman's constant."""
    _k = 0.01

    def __init__(self, coordinates):
        self.__coordinates = coordinates
        self.__coordinates_count = len(self.__coordinates)
        self._coordinates_validation()

        self.__solution = self.__coordinates.keys()

    def _distance(self, first_index, second_index):
        first = self.__coordinates[first_index]
        second = self.__coordinates[second_index]
        delta_x = first.x - second.x
        delta_y = first.y - second.y
        return math.hypot(delta_x, delta_y)

    def _coordinates_validation(self):
        assert self.__coordinates_count > 1, "Coordinates count cannot be  <= 1"
        for i in xrange(1, self.__coordinates_count + 1):
            assert i in self.__coordinates, \
                "All coordinates in [1, " + str(self.__coordinates_count) + "] must be available"

    def _solution_cost(self):
        cost = self._distance(1, self.__coordinates_count)
        for i in range(1, self.__coordinates_count):
            cost += self._distance(i, i + 1)
        return cost

if __name__ == '__main__':
    d = {1: Point(0, 0), 2: Point(1,1), 3: Point(2,2)}
    t = TSP(d)
    print t._solution_cost()