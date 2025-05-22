from setuptools import setup

setup(
    name='pycalvis',
    version='0.01',
    description='runtime callgraph of python code',
    author='chenchao',
    author_email='cchao.im@gmail.com',
    url='https://github.com/chen-chao/pycalvis',
    packages=['pycalvis'],
    setup_requires=[
        'setuptools',
    ],
    install_requires=[
        'graphviz>=0.13',
    ],
    license='MIT license',
    classifiers=[
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
    ],
)
