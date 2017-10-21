import logging
import re

class TSPParser:
    TSPParser(self):
        self.__coordinates_regex = re.compile("^([0-9]+) ([0-9]+\.[0-9]+) ([0-9]+\.[0-9]+$)")

    def parse_coordinates_line(self, line):
        match = re.match(self.__coordinates_regex, line)
        if match:
            x, y = float(match(2)), float(match(3))
        else:
            logging.error("Following line does not match coordinates regex: " + line)



