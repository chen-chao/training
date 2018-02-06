
# bubble sort move the biggest element from head to end in every
# iteration.
def bubble_sort(alist):
    length = len(alist)
    for i in range(length):
        for j in range(1, length-i):
            if alist[j-1] > alist[j]:
                alist[j-1], alist[j] = alist[j], alist[j-1]


def selection_sort(alist):
    length = len(alist)
    for i in range(length):
        minimum = i
        for j in range(i, length):
            if alist[j] < alist[minimum]:
                minimum = j
        if i != minimum:
            alist[i], alist[minimum] = alist[minimum], alist[i]


def insertion_sort(alist):
    length = len(alist)
    for i in range(1, length):
        j = i
        while j > 0 and alist[j] < alist[j-1]:
            alist[j-1], alist[j] = alist[j], alist[j-1]
            j -= 1

