# parse polish notation recursively.

def is_operator(char):
    if char in '+-*/':
        return True
    return False

def calc(operator, arg1, arg2):
    if operator is '+':
        return arg1+arg2
    if operator is '-':
        return arg1-arg2
    if operator is '*':
        return arg1*arg2
    if operator is '/':
        return arg1/arg2;
    raise TypeError('invalid operator and arguments.')


            
def parse(notation):
    # extremly ugly
    char = notation[0]
    if len(notation)==1:
        if is_operator(char):
            raise TypeError('operator is taken as argument.')
        return (eval(notation[0]),)
    
    if is_operator(char ):
        args = parse(notation[1:])
        res = calc(notation[0], args[0], args[1])
        if len(args)>2:
            return (res, )+args[2:]
        return (res, )
    else:
        return (eval(char),) + parse(notation[1:])

# code is from http://stackoverflow.com/questions/5307218/prefix-notation-parsing-in-python
def parse2(notation):
    token = notation.popleft()
    if is_operator(token):
        return calc(token, parse2(notation), parse2(notation) )
    else:
        return eval(token)
    
from collections import deque
def test():
    s = '* + 5 4 - 6 3'
    res = parse2(deque(s.split() ) )
    print('%s=%s'%(s, str(res) ) )

    s = '+ - 6 5 * 2 3 '
    res = parse2(deque(s.split() ) )
    print('%s=%s'%(s, str(res) ) )

    s = '+ 6 5 - 7 3'
    res = parse2(deque(s.split()) )
    print(s, '=', res)

if __name__=="__main__":
    test()
