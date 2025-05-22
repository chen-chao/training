class node:
    def __init__(self, value, next=None):
        self.value = value
        self.next = next
        
class stack:
    def __init__(self):
        self.top = None

    def push(self, value):
        self.top = node(value, self.top)

    def pop(self):
        if self.top is None:
            raise ValueError('Empty stack!')
        value = self.top.value
        self.top = self.top.next
        return value 

    def peek(self):
        if self.top:
            return self.top.value

    def is_empty(self):
        return self.top is None


class queue:
    def __init__(self):
        self.head= None
        self.tail= None

    def push(self, value):
        tail = node(value)
        if self.tail:
            self.tail.next = tail
            self.tail = tail
        else:
            self.tail = tail
            self.head = tail

    def pop(self):
        if self.head is None:
            raise ValueError("Empty queue!")
        value = self.head.value
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        return value

    def peek(self):
        if self.head:
            return self.head.value

    def valley(self):
        if self.tail:
            return self.tail.value

def ordered_push(s, value):
    if s.is_empty():
        s.push(value)
    else:
        peek = s.peek()
        if value > peek:
            s.push(value)
        else:
            top = s.pop()
            ordered_push(s, value)
            s.push(top)

def sort(s):
    if s.is_empty():
        return
    value = s.pop()
    sort(s)
    ordered_push(s, value)

    
if __name__ == '__main__':
    foo = stack()
    bar = queue()
    tiz = stack()
    for i in range(10, 0, -1):
        foo.push(i)
        bar.push(i)
        tiz.push(i)

    for i in range(10):
        svalue = foo.pop()
        qvalue = bar.pop()
        print('stack pop ', svalue, 'queue pop: ', qvalue)

    sort(tiz)
    for i in range(10):
       tvalue = tiz.pop() 
       print('stack sort ', tvalue)
