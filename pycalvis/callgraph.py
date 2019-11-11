import sys
import inspect
from collections import defaultdict
import graphviz


def get_module_name(frame):
    module = inspect.getmodule(frame)
    return module.__name__ if module else '__main__'


def get_function_name(frame):
    name = frame.f_code.co_name
    if 'self' in frame.f_locals:
        instance = frame.f_locals['self']
        try:
            method = getattr(instance, name)
            name = method.__qualname__
        except AttributeError:
            pass

    caller = frame.f_back
    if caller:
        func = caller.f_locals.get(name)
        if not func:
            func = caller.f_globals.get(name)

        if func:
            try:
                name = func.__qualname__
            except AttributeError:
                pass

    return name


class digraph:
    def __init__(self):
        self._data = dict()

    def node(self, nd):
        if nd not in self._data:
            self._data[nd] = set()

    def edge(self, n1, n2):
        self.node(n1)
        self.node(n2)
        self._data[n1].add(n2)

    def dot(self, *args, **kwargs):
        d = graphviz.Digraph(*args, **kwargs)
        for n1 in self._data:
            d.node(str(n1))
            for n2 in self._data[n1]:
                d.edge(str(n1), str(n2))

        return d


class callgraph:
    def __init__(self, whitelist=None, depth=1):
        self.graph = digraph()
        self.subgraphs = {}

        self._depth = depth
        self._dependency = defaultdict(int)

        self.whitelist = whitelist if whitelist else set()

        self._original_tracer = None

    def _add(self, frame):
        curmodule = get_module_name(frame)
        curfunc = get_function_name(frame)

        if curmodule not in self.subgraphs:
            d = digraph()
            self.subgraphs[curmodule] = d
        else:
            d = self.subgraphs[curmodule]

        d.node(curfunc)

        if frame.f_back:
            prevmodule = get_module_name(frame.f_back)
            prevfunc = get_function_name(frame.f_back)

            if curmodule == prevmodule:
                d.edge(prevfunc, curfunc)
            else:
                self.graph.edge(prevfunc, curfunc)

    def reset(self):
        self.graph = digraph()
        self.subgraphs = {}
        self._dependency = defaultdict(int)

    def at_call(self, frame):
        modulename = get_module_name(frame)

        if self._depth is not None:
            if modulename not in self._dependency:
                if frame.f_back:
                    prevmodule = get_module_name(frame.f_back)
                    if modulename != prevmodule:
                        self._dependency[modulename] = self._dependency[prevmodule] + 1

            if self._dependency[modulename] > self._depth and modulename not in self.whitelist:
                return

        self._add(frame)

    def __enter__(self):
        self.reset()
        self._original_tracer = sys.gettrace()
        sys.settrace(self.tracer)
        return self

    def __exit__(self, exc_type, exc_value, exc_traceback):
        sys.settrace(self._original_tracer)
        self._original_tracer = None

    def render(self, *args, **kwargs):
        graph_attr = kwargs.get('graph_attr', {
            'rankdir': 'LR',
            'bgcolor': 'lightgray',
            'style': 'solid',
            'compound': 'true'
        })

        node_attr = kwargs.get('node_attr', {
            'shape': 'ellipse',
            'style': 'filled',
            'fillcolor': 'honeydew'
        })

        dot = self.graph.dot(graph_attr=graph_attr, node_attr=node_attr)
        for mod, sub in self.subgraphs.items():
            g = sub.dot(name='cluster_'+mod)
            g.attr(label=mod)
            dot.subgraph(graph=g)

        return dot

    def tracer(self, frame, event, args):
        # to avoid recording self.__exit__
        if event == 'return' or event == 'exception':
            self.at_call(frame)

        return self.tracer
