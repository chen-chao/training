# encoding:utf-8

class btree:
    def __init__(self, value=None):
        self.value = value
        self.left = None
        self.right = None

    def add(self, value):
        if self.value is None:
            self.value = value
            self.left = btree()
            self.right = btree()
        elif self.value < value:
            self.right.add(value)
        elif self.value > value:
            self.left.add(value)

    def __contains__(self, value):
        if self.value == value:
            return True
        if self.value < value:
            return value in self.right
        return value in self.left
        
    def delete(self, value):
        pass

    def show(self):
        if self.value is not None:
            print(self.value)
            self.left.show()
            self.right.show()
            
if __name__ == '__main__':
    from random import shuffle
    foo = list(range(10))
    shuffle(foo)
    print('foo', foo)
    bt = btree()
    for v in foo:
        bt.add(v)
    print('5 in bt: ',end='')
    print(5 in bt)
    bt.show()
