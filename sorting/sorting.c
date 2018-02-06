/* C implementation of shell sort */


void swap(int alist[], int i, int j) {
    int tmp;
    tmp = alist[i];
    alist[i] = alist[j];
    alist[j] = tmp;
}

void shell_sort(int alist[], int n) {
    /* Version provided by Robert Sedgewick's Algorithms */
    int h = 1;
    int length = n/3;
    while (h < length)
        h = h*3 + 1;

    int i, j;
    while (h >= 1) {
        for (i = h; i < n; i++) {
            for (j = i; j >= h&& alist[j-h] > alist[j]; j -= h) {
                swap(alist, j-h, j);
            }
        }
        h /= 3;
    }
}

void insertion_sort(int alist[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = i; j > 0 && alist[j-1] > alist[j]; j--) {
            swap(alist, j-1, j);
        }
    }
}

void selection_sort(int alist[], int n) {
    int i, j, min;
    for (i = 0; i < n; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (alist[j] < alist[min]) {
                min = j;
            }
        }
        swap(alist, i, min);
    }
}

void bubble_sort(int alist[], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 1; j < n-i; j++) {
            if (alist[j] < alist[j-1]) {
                swap(alist, j, j-1);
            }
        }
    }
}

void _quick_sort_kr(int alist[], int p, int q) {
    if (p >= q)
        return;

    int pivot = alist[p];
    int i, j;
    j = p;
    for (i = p+1; i <= q; i++) {
        if (alist[i] < pivot) {
            swap(alist, ++j, i);
        }
    }
    swap(alist, p, j);
    _quick_sort_kr(alist, p, j-1);
    _quick_sort_kr(alist, j+1, q);
}

void _quick_sort_sedgewick(int alist[], int p, int q){
    if (p >= q)
        return;

    int pivot = alist[p];
    int i = p+1, j = q;
    while (1) {
        while (i <= j && alist[i] < pivot)
            i++;
        while (j >= i && alist[j] >= pivot)
            j--;
        if (i > j)
            break;
        swap(alist, i, j);
    }
    swap(alist, p, j);
    _quick_sort_sedgewick(alist, p, j-1);
    _quick_sort_sedgewick(alist, j+1, q);
}

void quick_sort_kr(int alist[], int n) {
    _quick_sort_kr(alist, 0, n-1);
}

void quick_sort_sedgewick(int alist[], int n) {
    _quick_sort_sedgewick(alist, 0, n-1);
}

void _merge(int alist[], int p, int mid, int q, int buffer[]) {
    int pos;
    for (pos = p; pos <= q; pos++) {
        buffer[pos] = alist[pos];
    }
    int i = p, j = mid+1;
    for (pos = p; pos <= q; pos++) {
        if (i > mid) {
            alist[pos] = buffer[j++];
        } else if (j > q) {
            alist[pos] = buffer[i++];
        } else if (buffer[j] > buffer[i]) {
            alist[pos] = buffer[i++];
        } else {
            alist[pos] = buffer[j++];
        }
    }
}

void _merge_sort(int alist[], int p, int q, int buffer[]) {
    if (p >= q)
        return;
    int mid = (p+q)/2;
    _merge_sort(alist, p, mid, buffer);
    _merge_sort(alist, mid+1, q, buffer);
    _merge(alist, p, mid, q, buffer);
}

void merge_sort(int alist[], int n) {
    int buffer[n];
    _merge_sort(alist, 0, n-1, buffer);
}
