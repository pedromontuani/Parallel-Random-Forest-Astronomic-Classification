from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

class get_pybind_include(object):
    def __str__(self):
        import pybind11
        return pybind11.get_include()

ext_modules = [
    Extension(
        'random_forest_wrapper',
        ['random_forest_wrapper.cpp'],
        include_dirs=[get_pybind_include()],
        language='c++',
        extra_compile_args=['-O3', '-std=c++20', '-fopenmp'],
        extra_link_args=['-fopenmp'],
    ),
]

setup(
    name='random_forest_wrapper',
    version='0.1',
    author='Your Name',
    description='C++ Random Forest pybind11 wrapper',
    ext_modules=ext_modules,
    install_requires=['pybind11'],
    cmdclass={'build_ext': build_ext},
    zip_safe=False,
)