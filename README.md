# luciart
A simple stochastic ray Tracer implementation in C++

## Features

This ray tracer includes an implementation of Whitted Tracer and a stochastic one with the following sampling techniques:

- Regular
- Random
- Jittered
- Monte Carlo Adaptive

All these sampling techniques can be used in **anti-aliasing**, camera **depth of field** (square or disk) and to produce **soft shadows**. This implementation uses an uniform grid acceleration structure with intersection "mailboxes".

## Usage

The program will render the scene as a .tga file and output a log file with the rendering information.
 
 > Run the program:

```shell
$ ./lucia <file>

    <file>      The scene description file. NFF and PLY formats are supported.
```

## Results

Right now all the rendering options are hard-coded. Change boolean variables ``USE_DOF``, ``USE_SOFT_SHADOWS`` and ``USE_GLOSSY_REFLECTION`` to turn on or off the rendering effects.
 

|![](https://github.com/nekrotzar/luciart/blob/master/data/results/box_test_effects.nff.png?raw=true)|![](https://github.com/nekrotzar/luciart/blob/master/data/results/test_dof_2.nff.png?raw=true)|
|----|---|

## Authors
- [Luís Fonseca](https://github.com/nekrotzar)
- [Ricardo Fonseca](https://github.com/rpsfonseca)
