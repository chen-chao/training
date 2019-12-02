# pycalvis

A simple tool to visualize call graph of python codes at runtime.

## Example

``` python
from pycalvis import callgraph

with callgraph() as g:
    # codes here
    pass

g.render().view()
```

will generated a callgraph file.

You can also run it from command line (needs improvement).

``` shell
python -m pycalvis script.py
```
