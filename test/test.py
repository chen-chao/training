from pycalvis import callgraph
from collections import Counter


def hello():
    c = Counter('hello')
    return c.most_common(1)


with callgraph(depth=None) as g:
    hello()

g.render().view()
