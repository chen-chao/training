import importlib
import sys
import os.path
from runpy import _get_code_from_file, _get_module_details

from pycalvis import callgraph


def trace_script(path_name:str, *args, **kwargs):
    code, fname = _get_code_from_file('<run_path>', path_name)

    run_globals = dict(__name__='<run_path>',
                       __file__=fname,
                       __cached__=None,
                       __doc__=None,
                       __loader__=None,
                       __package__='<run_path>',
                       __spec__=None)

    with callgraph(*args, **kwargs) as g:
        exec(code, run_globals)

    g.render().view()


def trace_module(module_name:str, *args, **kwargs):
    spec = importlib.util.find_spec(module_name)
    if not spec:
        raise TypeError(f'module not found: {module_name}')

    initfile = spec.origin
    mainfile = os.path.join(os.path.dirname(initfile), '__main__.py')
    if os.path.exists(mainfile):
        trace_script(mainfile, *args, **kwargs)

    raise TypeError(f'__main__.py not found: {module_name}')


def run_tracer():
    script_or_module = sys.argv[-1]
    run = trace_script if script_or_module.endswith('.py') else trace_module
    run(script_or_module)


if __name__ == "__main__":
    run_tracer()
