import logging
import re
import sys

from point import Point

class TSPLibParser:
    def __init__(self, filename):
        self.__coordinates = {}
        self.__coordinates_regex = re.compile("^([0-9]+) ([0-9]+\.[0-9]+) ([0-9]+\.[0-9]+$)")
        self.__filename = filename

    def parse(self):
        with open(self.__filename, 'r') as f:
            for line in f:
                if line.startswith("NAME"):
                    self._parse_tsplib_name(line)
                elif len(line) > 0 and line[0].isdigit():
                    self._parse_coordinates_line(line.strip(' \n'))
        logging.info("Parsed " + str(len(self.__coordinates)) + " coordinates")
        logging.debug(self.__coordinates)
        return self.__coordinates

    def _parse_coordinates_line(self, line):
        match = re.match(self.__coordinates_regex, line)
        if match:
            node_id, point = int(match.group(1)), Point(float(match.group(2)), float(match.group(3)))
            self.__coordinates[node_id] = point
        else:
            logging.error("Following line does not match coordinates regex: " + line)

    def _parse_tsplib_name(self, line):
        tokens = line.split(":")
        assert len(tokens) == 2, "Unexpected format for name attribute"
        logging.info("TSPLIB instance " + tokens[1].strip())