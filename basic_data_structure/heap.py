'''heap and heap sorting'''


class minheap:
    def __init__(self, array=None, inplace=False):
        if array is not None:
            self._from_array(array, inplace)
        else:
            self.data = []
            self.size = 0

    def _from_array(self, array, inplace=False):
        if not inplace:
            self.data = array[:]
        else:
            self.data = array
        self.size = len(self.data)
        for ind in range((self.size-1)//2, -1, -1):
            self._sink(ind)

    def push(self, value):
        self.data.append(value)
        self._swim(self.size)
        self.size += 1

    def _swap(self, p1, p2):
        tmp = self.data[p1]
        self.data[p1] = self.data[p2]
        self.data[p2] = tmp

    def _swim(self, ind):
        parent = (ind-1)//2
        while ind > 0 and self.data[ind] < self.data[parent]:
            self._swap(ind, parent)
            ind = parent
            parent = (ind-1)//2

    def _sink(self, ind):
        while ind < self.size//2:
            child = ind*2 + 1
            if child < self.size-1 and self.data[child+1] < self.data[child]:
                child += 1
            if self.data[ind] <= self.data[child]:
                break
            self._swap(ind, child)
            ind = child

    def delmin(self):
        if self.size == 0:
            raise TypeError('heap is empty.')
        self._swap(0, self.size-1)
        value = self.data.pop()
        self.size -= 1
        self._sink(0)
        return value

    @classmethod
    def heapsort(cls, array):
        if array is None or len(array) < 2:
            return
        pq = minheap(array, inplace=True)
        print(pq.data)
        while pq.size > 0:
            pq._swap(0, pq.size-1)
            pq.size -= 1
            pq._sink(0)
        array.reverse()


def test():
    from random import shuffle
    array = list(range(20))
    shuffle(array)
    pq = minheap()
    for i in array:
        pq.push(i)
    while pq.size > 0:
        value = pq.delmin()
        print(value, end=' ')
    print('\narray: ', array)
    minheap.heapsort(array)
    print(array)


if __name__ == '__main__':
    test()
