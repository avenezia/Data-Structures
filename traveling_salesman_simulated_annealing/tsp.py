import argparse
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
    COOLING_STEPS = 500

    """How much to cool each time: make higher to improve quality, lower to
       speed the program up."""
    COOLING_FRACTION = 0.97

    """Lower makes it faster, higher makes it potentially better."""
    STEPS_PER_TEMP = 1000

    """Problem specific Boltzman's constant."""
    K = 1e3


    def __init__(self, coordinates, configuration):
        self.__coordinates = coordinates
        self.__coordinates_count = len(self.__coordinates)
        self._coordinates_validation()

        self.__configuration = configuration
        logging.info("Starting annealing with the following configuration: " + str(self.__configuration))

    def anneal(self):
        temperature = TSP.INITIAL_TEMPERATURE
        # 0-indexed array
        current_solution = self.__coordinates.keys()
        current_cost = self._solution_cost(current_solution)

        for cooling_step in xrange(self.__configuration["cooling_steps"]):
            cost_at_cooling_step_start = current_cost

            temperature *= self.__configuration["cooling_fraction"]

            for step_per_temp in xrange(self.__configuration["steps_per_temp"]):
                # Pick indices of elements to swap
                first_index = random.randint(0, self.__coordinates_count - 1)
                second_index = random.randint(0, self.__coordinates_count - 1)

                if (first_index != second_index):
                    new_solution = list(current_solution)
                    new_solution[first_index], new_solution[second_index] = new_solution[second_index], new_solution[first_index]
                    new_cost = self._solution_cost(new_solution)

                    if (current_cost > new_cost):
                        current_cost = new_cost
                        current_solution = new_solution
                        logging.debug("Found better solution with cost " + str(current_cost))
                    elif (math.exp((current_cost - new_cost) / (self.__configuration["k"] * temperature)) > random.random()):
                        # Accepting worse solutions should mainly happen when close to the starting temperature.
                        current_cost = new_cost
                        current_solution = new_solution
                        logging.debug("Accepting worse solution with cost " + str(current_cost))

        logging.info("Solution cost: " + str(current_cost))
        logging.info("Solution: " + str(current_solution))

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

def parse_command_line():
    parser = argparse.ArgumentParser()
    parser.add_argument("-cs", help="Cooling steps: how many times the cooling is performed (higher: +quality, lower: +speed",
        dest="cooling_steps", type=int, default=TSP.COOLING_STEPS)
    parser.add_argument("-cf", help="Cooling fraction: how much to cool each time (higher: +quality, lower: +speed",
        dest="cooling_fraction", type=float, default=TSP.COOLING_FRACTION)
    parser.add_argument("-st", help="Steps per temperature (higher: +quality, lower: +speed",
        dest="steps_per_temp", type=int, default=TSP.STEPS_PER_TEMP)
    parser.add_argument("-k", help="Problem specific Boltzman's constant",  dest="k", type=float, default=TSP.K)
    parser.add_argument("-f", help="The TSPLIB instance file", dest="tsplib_file", required=True)
    return vars(parser.parse_args())

if __name__ == '__main__':
    root = logging.getLogger()
    root.setLevel(logging.DEBUG)

    stream_handler = logging.StreamHandler(sys.stdout)
    formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
    stream_handler.setFormatter(formatter)
    root.addHandler(stream_handler)

    args = parse_command_line()
    parser = TSPLibParser(args["tsplib_file"])
    tsp = TSP(parser.parse(), args)
    tsp.anneal()