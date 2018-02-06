
class node:
    def __init__(self, label, next=None):
        self.label = label
        self.next = next
    def __str__(self):
        return str(self.label)

class linkedlist:
    def __init__(self):
        self.head = None

    def add(self, label):
        self.head = node(label, self.head)

    def is_empty(self):
        return self.head == None

    def append(self, label):
        head = self.head
        if not head:
            self.add(label)
        else:
            while head.next != None:
                head = head.next
            head.next = node(label)

    def reverse(self):
        prev = None
        cur = self.head
        while cur:
            next = cur.next 
            cur.next = prev
            prev = cur
            cur = next
        self.head = prev
    
    def __add__(self, other):
        if self.head is None:
            self.head = other.head 
            return
        tail = self.head
        while tail.next:
            tail = tail.next 
        tail.next = other.head

    def lookup(self, label):
        head = self.head
        while head != None and head.label != label:
            head = head.next
        return head

    def delete(self, label):
        if self.head.label == label:
            self.head = self.head.next
        else:
            head = self.head
            while head.next != None:
                if head.next.label == label:
                   head.next = head.next.next 
                   break
                head = head.next

    def __eq__(self, other):
        cur1 = self.head
        cur2 = other.head
        while cur1 and cur2: 
            if cur1.label != cur2.label:
                return False
            cur1 = cur1.next
            cur2 = cur2.next
        return cur1 is None and cur2 is None

    def __str__(self):
        head = self.head
        s = ''
        while head != None:
            s += '%s->'%str(head.label) 
            head = head.next
        s += 'None'
        return s
        
if __name__ == '__main__':
    foo = linkedlist()
    bar = linkedlist()
    for i in range(1, 10):
        foo.append(i)
        bar.add(i)
    print('foo: %s'%str(foo))
    print('bar: %s'%str(bar))
    print('foo == bar ? ', end='')
    print(foo == bar)
    foo.reverse()
    print('reverse foo: %s'%str(foo))
    print('foo == bar ? ', end='')
    print(foo == bar)

    head = foo.lookup(6)
    print('6 in foo: %s'%str(head))

    foo.delete(4)
    print('foo delete 4: %s'%str(foo))
