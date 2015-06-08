# LsystemDrawer
A tool to evaluate and draw L-system.

[![Screenshot](https://github.com/tobiasberling/LsystemDrawer/blob/master/Screenshot_fplant_small.png)](https://github.com/tobiasberling/LsystemDrawer/blob/master/Screenshot_fplant.png) [![Screenshot](https://github.com/tobiasberling/LsystemDrawer/blob/master/Screenshot_striangle_small.png)](https://github.com/tobiasberling/LsystemDrawer/blob/master/Screenshot_striangle.png)

## Usage

For information about [L-systems](http://en.wikipedia.org/wiki/L-system) you can read the  [Wikipedia article](http://en.wikipedia.org/wiki/L-system).

This implementations allows every ASCII character to be a variable. 
Multiple rules can be given by placing each rule on its own line. 
Predecessor and successor of a rule must be separated by `->`.

When drawing the result, some variables have a special meaning:
* `0`, `1`, `F`, `A`, `B` draw a line segment
* `[` saves the current position and rotation onto thr stack
* `]` pops position and rotation from the stack and updates the current values accordingly
* `+` and `-` perform a rotation in clock- and counterclockwise direction
