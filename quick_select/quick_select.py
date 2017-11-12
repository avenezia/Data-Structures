import random

def quick_select(items, k):
    random.shuffle(items)
    lo, hi = 0, len(items) - 1
    while (hi > lo):
        j = partition(items, lo, hi)
        if (j < k):
            lo = j + 1
        elif (j > k):
            hi = j - 1
        else:
            return items[k]
    return items[k]

def swap(v, i, j):
    v[i],v[j] = v[j],v[i]

def partition(items, lo, hi):
    i, j = lo, hi + 1
    while (True):
        i += 1
        while (items[i] < items[lo]):
            i += 1
            if (i == hi):
                break

        j -=1
        while (items[lo] < items[j]):
            j -= 1
            if (j == lo):
                break

        if (i >= j):
            break
        swap(items, i, j)

    swap(items, lo, j)
    return j

def main():
    size = random.randint(10, 20)
    v = [random.randint(-100, 100) for i in xrange(size)]
    k = random.randint(0, size - 1)
    result = quick_select(v, k)
    sorted_v = sorted(v)
    expected = sorted_v[k]
    print "v: {0}\nsorted: {1}\nk={2}, resulting v[k]={3}".format(v, sorted_v, k, result)
    assert result == expected, "Unexpected element from quick select"

if __name__ == '__main__':
    main()
