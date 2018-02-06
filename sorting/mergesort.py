def merge(alist, p, mid, q):
    i = p
    j = mid+1
    tmp = []
    while i <= mid and j <= q:
        if alist[i] < alist[j]:
            tmp.append(alist[i])
            i += 1
        else:
            tmp.append(alist[j])
            j += 1
    tmp += alist[i:mid+1]
    tmp += alist[j:q+1]
    alist[p:q+1] = tmp

def merge_sort(alist, p, q):
    if p >= q:
        return
    middle = (p+q)//2
    merge_sort(alist, p, middle)
    merge_sort(alist, middle+1, q)
    merge(alist, p, middle, q)
