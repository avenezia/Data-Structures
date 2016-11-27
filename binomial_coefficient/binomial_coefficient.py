import argparse
from pprint import pprint

def binomial_coefficient(n, k, verbose):
    table_size = n + 1
    coefficient_table = [[0 for column in range(table_size)] for row in range (table_size)]
    # Only one way to choose 0 things from a set.
    for row_index in range(table_size):
        coefficient_table[row_index][0] = 1
    # Only one way to choose k things from a k-element set.
    for column_index in range(table_size):
        coefficient_table[column_index][column_index] = 1
    #                                                                                       (n)
    # Explanation of the recurrence: consider whether the nth element appears in one of the (k)
    # subsets of k elements. If so, we can complete the subset by picking k - 1 other
    # items from the other n - 1. If not, we must pick all k items from the remaining n - 1.
    # cit. "Skiena, The Algorithm Design Manual"
    for row_index in range (1, table_size):
        for column_index in range(1, row_index):
            coefficient_table[row_index][column_index] = (coefficient_table[row_index-1][column_index-1] +
                                                          coefficient_table[row_index-1][column_index])
        if verbose:
            pprint(coefficient_table)
            print "\n"
    return coefficient_table[n][k];

def parse_arguments():
    parser = argparse.ArgumentParser(description='It calculates the binomial coefficients (n choose k) using dynamic programming.')
    parser.add_argument('-n', type=int, help='The size of the set.', required=True)
    parser.add_argument('-k', type=int, help='The size of the subset we want to extract.', required=True)
    parser.add_argument('-v', action="store_true", help='Verbose mode, to print the evolution of the dynamic programming table.')
    args = parser.parse_args()
    assert args.k >= 0 and args.k <= args.n, "Please provide valid arguments, 0 <= k <= n."
    return args.n, args.k, args.v

def main():
    n, k, verbose = parse_arguments()
    print "Number of ways to choose {} things out of {} possibilities: {}".format(k, n, binomial_coefficient(n, k, verbose))

if __name__ == '__main__':
    main()
