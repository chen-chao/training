# the idea of using the last element as the pivot is more
# elegant. However, the implementation is all the same.
def quick_sort_kr(alist, p, q):
    if p >=q:
        return
    pivot = alist[p]
    j = p
    for i in range(p+1, q+1):
        # using less to avoid duplicate comparison between elements
        # equal to the pivot
        if alist[i] < pivot:
            # this swaps a[i], a[j] even when i == j
            j += 1
            alist[i], alist[j] = alist[j], alist[i]
    # Swapping also happens when p == j
    # we already know a[j] < a[p]
    alist[p], alist[j] = alist[j], alist[p]
    quick_sort_kr(alist, p, j-1)
    quick_sort_kr(alist, j+1, q)


def quick_sort_sedgewick(alist, p, q):
    if p >= q:
        return
    pivot = alist[p]
    lo = p+1
    hi = q
    # make sure lo or hi can reach another side when there is no the
    # other loop
    while 1:
        while hi >= lo and alist[hi] > pivot:
            hi -= 1
        while lo <= hi and alist[lo] <= pivot:
            lo += 1
        if lo > hi:
            break
        alist[hi], alist[lo] = alist[lo], alist[hi]
    # hi can reach p because the loop terminates when lo > hi
    alist[hi], alist[p] = alist[p], alist[hi]
    quick_sort_sedgewick(alist, p, hi-1)
    quick_sort_sedgewick(alist, hi+1, q)
