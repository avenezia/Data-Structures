import logging
import math
import random
import sys

from point import Point
from tsp_lib_parser import TSPLibParser

class TSP:
    INITIAL_TEMPERATURE = 1.0

    """ How many times do we cool: make higher to improve quality, lower to
    speed the program up. Move in tandem with the COOLING_FRACTION."""
    COOLING_STEPS = 1000

    """How much to cool each time: make higher to improve quality, lower to
       speed the program up."""
    COOLING_FRACTION = 0.99

    """Lower makes it faster, higher makes it potentially better."""
    STEPS_PER_TEMP = 2000

    """Problem specific Boltzman's constant."""
    K = 0.01


    def __init__(self, coordinates):
        self.__coordinates = coordinates
        self.__coordinates_count = len(self.__coordinates)
        self._coordinates_validation()


    def anneal(self):
        temperature = TSP.INITIAL_TEMPERATURE
        # 0-indexed array
        current_solution = self.__coordinates.keys()
        current_cost = self._solution_cost(current_solution)

        for cooling_step in xrange(TSP.COOLING_STEPS):
            cost_at_cooling_step_start = current_cost

            temperature *= TSP.COOLING_FRACTION

            for step_per_temp in xrange(TSP.STEPS_PER_TEMP):
                # Pick indices of elements to swap
                first_index = random.randint(0, self.__coordinates_count - 1)
                second_index = random.randint(1, self.__coordinates_count - 1)

                new_solution = list(current_solution)
                new_solution[first_index], new_solution[second_index] = new_solution[second_index], new_solution[first_index]
                new_cost = self._solution_cost(new_solution)

                if (current_cost > new_cost):
                    current_cost = new_cost
                    current_solution = new_solution
                elif (math.exp((current_cost - new_cost) / (TSP.K * temperature)) > random.random()):
                    current_cost = new_cost
                    current_solution = new_solution

        return current_cost, current_solution

    def _coordinates_validation(self):
        assert self.__coordinates_count > 1, "Coordinates count cannot be  <= 1"
        for i in xrange(1, self.__coordinates_count + 1):
            assert i in self.__coordinates, \
                "All coordinates in [1, " + str(self.__coordinates_count) + "] must be available"


    def _distance(self, first_coord_index, second_coord_index):
        first = self.__coordinates[first_coord_index]
        second = self.__coordinates[second_coord_index]
        delta_x = first.x - second.x
        delta_y = first.y - second.y
        return math.hypot(delta_x, delta_y)


    def _solution_cost(self, solution):
        cost = self._distance(solution[0], solution[self.__coordinates_count -1])
        for i in range(0, self.__coordinates_count - 1):
            cost += self._distance(solution[i], solution[i + 1])
        return cost

if __name__ == '__main__':
    root = logging.getLogger()
    root.setLevel(logging.DEBUG)

    stream_handler = logging.StreamHandler(sys.stdout)
    stream_handler.setLevel(logging.DEBUG)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    stream_handler.setFormatter(formatter)
    root.addHandler(stream_handler)

    #p = TSPLibParser("wi29")
    p = TSPLibParser("dj38")
    t = TSP(p.parse())
    print t.anneal()