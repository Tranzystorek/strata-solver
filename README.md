# strata-solver

## About

This is a solver for the [Strata](http://www.graveck.com/strata/) game.
It works based on simple searching of solution space.

## Building

```
mkdir cmake-build
cd cmake-build
cmake ..
make strata_solver
```

## Usage

### Input

The program reads a simple description of a level map from stdin:

```
4 4
p r p p
g g p g
r 0 r r
r r p g
```

First, the `width` and `height` of the map,
then a list of whitespace-separated descriptions of tile colors.
The following colors are available:

|Code   |Color    |
|-------|---------|
|`0`    |Colorless|
|`y` `Y`|Yellow   |
|`r` `R`|Red      |
|`p` `P`|Purple   |
|`g` `G`|Green    |
|`o` `O`|Orange   |

The mapping of these to in-game colors does not matter to the solver,
just needs to be unique.

The orientation of the map description
shall be as follows (using geographical directions):

```
      NW
   ---------
   |x x x x|
SW |x x x x| NE
   |x x x x|
   |x x x x|
   ---------
      SE
```

### Output

```
SOLUTION 1
ROWS ( 0 1 ), COLOR *
ROW 2, COLOR Red
ROW 3, COLOR Purple
ROW 4, COLOR Red
ROW 5, COLOR Green
```

A single solution description consists of ordered pairs
of a row number and color (according to the provided level decription).

Row numbers shall be interpreted as follows:

```
  ---------
0 |x x x x|
1 |x x x x|
2 |x x x x|
3 |x x x x|
  ---------
   4 5 6 7
```

The first line of the solution description, with the `Color *`,
shows that the highlighted rows can be assigned any color
and will not impact the correctness of the solution.
