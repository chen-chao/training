#/usr/bin/env python3

from elementarysort import bubble_sort, selection_sort, insertion_sort
from quicksort import quick_sort_kr, quick_sort_sedgewick 
from mergesort import merge_sort
from shellsort import shell_sort_kr, shell_sort_shell, shell_sort_sedgewick

def test_sorting(func, size, duplicate=False):
    from random import shuffle, randint
    if duplicate:
        s = list(map(lambda x: randint(0, size-1), range(size)))
    else:
        s = list(range(size))
    shuffle(s)
    print('Testing %s'%func.__name__)
    print('----------------------')
    print(s)
    try:
        func(s)
    except TypeError: 
        func(s, 0, size-1)
    print(s)
    print('----------------------')
    
if __name__ == '__main__':
    funcs = [bubble_sort, selection_sort, insertion_sort, merge_sort,
             quick_sort_kr, quick_sort_sedgewick, shell_sort_kr,
             shell_sort_shell, shell_sort_sedgewick]
    size = 20
    duplicate = True
    for func in funcs:
        test_sorting(func, size, duplicate)
