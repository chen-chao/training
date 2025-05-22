# Shell sort's worst case performance depends on the incremental
# sequence, and the average performance for randomly ordered input
# hasn't been found yet.

# when an h-sorted array is k-sorted, it remains h-sorted.

# h-sorted: a[i] ... a[i+k] ... a[i+h] ... a[i+h+k]
# k-sorted: a[i] will be compared to a[i+k], and a[i+h] will be
# compared to a[i+h+k]
# a[i] will become the smaller one of a[i] and a[i+k], and a[i+h+k]
# will become the bigger one of a[i+h] and a[i+h+k], which is always
# bigger than a[i] and a[i+k]. So after k-sorted, the array will
# remain h-sorted.

def shell_sort_kr(alist):
    # This is given by K&R in "The C Programming Language"

    # The algorithm firstly sort all sub-arrays with big interval, and
    # then insertion sort all sub-arrays in the interval by decreasing
    # the interval. Finally the interval decreases to 1 and shell sort
    # becomes insertion sort. But each element will take at most steps
    # as last interval length to be swapped to the right position.
    # However, shell sort is still slower than merge sort because it
    # uses linear insertion to move a smaller element ahead.

    length = len(alist)
    gap = length//2
    while gap > 0:
        for i in range(gap, length):
            # for j in range(i-gap, -1, -gap):
            j = i - gap
            while j >= 0 and alist[j] > alist[j+gap]:
                alist[j+gap], alist[j] = alist[j], alist[j+gap]
                j -= gap
        gap = gap //2

def shell_sort_shell(alist):
    # This is said to be the original version by D.L.Shell in 1959 in
    # paper "Analysis of Shellsort and Related Algorithms" by Robert
    # Sedgewick.
    gaps = [1391376, 463792, 198768, 86961, 33936,
            13776, 4592, 1968, 861, 336,
            112, 48, 21, 7, 3, 1]

    length = len(alist)
    for gap in gaps:
        for i in range(gap, length):
            j = i
            v = alist[i]
            while j >= gap and alist[j-gap]>v:
                # this is better than the following line
                # alist[j], alist[j-gap] = alist[j-gap], alist[j]
                # because here we swap a[i] to position j only once
                alist[j] = alist[j-gap]
                j -= gap
            alist[j] = v


def shell_sort_sedgewick(alist):
    # This is given by Robert Sedgewick in "Algorithms".
    # It shows the intervals could be arbitrary selected.
    length = len(alist)
    gap = 1
    while gap < length//3:
        gap = gap*3 + 1

    while gap >= 1:
        for i in range(gap, length):
            # print('gap: ', gap, alist)
            # or j = i - gap; test j >= 0, alist[j] > v; alist[j+gap] = v
            j = i
            v = alist[i]
            while j >= gap and alist[j-gap] > v:
                alist[j] = alist[j-gap]
                j -= gap
            alist[j] = v
        gap = gap // 3
