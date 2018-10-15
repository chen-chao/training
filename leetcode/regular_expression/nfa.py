'''Python implementation of a regular expression matcher using non determined
finite autonama(NFA), refer to Russ Cox,
https://swtch.com/~rsc/regexp/regexp1.html'''


from enum import Enum

class _pareninfo:
    def __init__(self, nalt, natom):
        self.nalt = nalt
        self.natom = natom


def re2postfix(re):
    nalt = 0
    natom = 0
    parens = []
    dst = []

    for char in re:
        # print(char)
        if char == '(':
            if natom > 1:
                natom -= 1
                dst.append('.')
            parens.append(_pareninfo(nalt, natom))
            nalt = 0
            natom = 0
        elif char == '|':
            if natom == 0:
                raise TypeError('symbol | need at least two elements.')
            natom -= 1
            while natom > 0:
                dst.append('.')
                natom -= 1
            nalt += 1
        elif char == ')':
            if not parens:
                raise TypeError('unmatching parenthesis.')
            if natom == 0:
                raise TypeError('empty parenthesis.')
            natom -= 1
            while natom > 0:
                dst.append('.')
                natom -= 1
            for i in range(nalt):
                dst.append('|')
            nalt = 0
            p = parens.pop()
            nalt = p.nalt
            natom = p.natom + 1
        elif char in ('*', '?', '+'):
            if natom == 0:
                raise TypeError('symbol *, ?, + can not be used alone.')
            dst.append(char)
        else:
            if natom > 1:
                natom -= 1
                dst.append('.')
            dst.append(char)
            natom += 1

    if parens:
        raise TypeError('unmatching parenthesis.')

    while natom > 1:
        dst.append('.')
        natom -= 1
    for i in range(nalt):
        dst.append('|')

    return ''.join(dst)


class StateStatus(Enum):
    Split = -2
    Match = -3


class State:
    def __init__(self, char, *states):
        self.char = char
        self.next = list(states)
        self.listid = None

    def match(self, char):
        return self.char == '.' or self.char == char

    def isfinal(self):
        return self.char == StateStatus.Match

    def connect(self, state):
        self.next.append(state)

    def __str__(self):
        if self.char == StateStatus.Split:
            return '%s->%s' % (self.char, ' '.join(self.next))
        elif self.char == StateStatus.Match:
            return 'Match!'
        else:
            return self.char


class StateList:
    id = 0
    def __init__(self):
        self.state = []

    def addstate(self, state):
        if state.listid != StateList.id:
            state.listid = StateList.id
            if state.char == StateStatus.Split:
                for state in state.next:
                    self.addstate(state)
            else:
                self.state.append(state)

    def clean(self):
        self.state = []

    def __iter__(self):
        return iter(self.state)

    def __str__(self):
        return ', '.join(map(str, self.state))


class Fragment:
    def __init__(self, start, out):
        # starting state of the fragment
        self.start = start
        # self.out is the output states of the fragment
        self.out = out

    def append(self, states):
        # neglect duplicate states because we don't have such states in fragment
        self.out += states

    # connecting all output states with state
    def patch(self, state):
        for out in self.out:
            out.connect(state)


MatchState = State(StateStatus.Match)
class NFA:
    def __init__(self, postfix):
        self.start = self.to_nfa(postfix)

    def to_nfa(self, postfix):
        fragments = []

        for c in postfix:
            if c == '.':
                e2 = fragments.pop()
                e1 = fragments.pop()
                e1.patch(e2.start)
                fragments.append(Fragment(e1.start, e2.out))
            elif c == '|':
                e2 = fragments.pop()
                e1 = fragments.pop()
                state = State(StateStatus.Split, e1.start, e2.start)
                frag = Fragment(state, e1.out+e2.out)
                fragments.append(frag)
            elif c == '?':
                e = fragments.pop()
                state = State(StateStatus.Split, e.start)
                # state is still open for next connection
                frag = Fragment(state, e.out+[state])
                fragments.append(frag)
            elif c == '*':
                e = fragments.pop()
                state = State(StateStatus.Split, e.start)
                e.patch(state)
                # state is still open for next connection
                fragments.append(Fragment(state, [state]))
            elif c == '+':
                e = fragments.pop()
                e.patch(e.start)
                # e.out is still open for next connection
                fragments.append(e)
            else:
                state = State(c)
                fragments.append(Fragment(state, [state]))

        e = fragments.pop()
        if fragments:
            raise TypeError('invalid postfix.')
        else:
            e.patch(MatchState)
            return e.start

    def match(self, s):
        clist = StateList()
        clist.addstate(self.start)
        nlist = StateList()
        for char in s:
            StateList.id += 1
            for state in clist:
                if state.match(char):
                    # since state will never be a split state, state.next will always be a
                    # single element list(see statelist.addstate). how to improve that?
                    for nstate in state.next:
                        nlist.addstate(nstate)

            clist, nlist = nlist, clist
            nlist.clean()
            if not clist:
                break
        return MatchState in clist


if __name__ == '__main__':
    import sys
    argv = sys.argv
    if len(argv) < 3:
        print('Usage: python nfa.py pattern s1 [s2...] ')
    else:
        postfix = re2postfix(argv[1])
        print('postfix: ', postfix)
        nfa = NFA(postfix)
        for s in argv[2:]:
            if nfa.match(s):
                print('Found match: ', s)
