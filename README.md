# CSE167-Final

poggers poggers jar on and k at yay wawhahwhwahwahwhwa

## Introduction

This project implements the **tennis racket theorem**, also known as the **Dzhanibekov effect**, which affects rigid bodies (i.e., those that don't change shape) with three moments of inertia (if an object can rotate around three different axes and "look" different). When rotating around two of the principal axes, the object only rotates around that axis. However, when rotating around the remaining axis, the object also produces a half-rotation around another axis.

## The Physics

Suppose we have an object that can experience the Dzhanibekov effect. Then, it must have **three principal axes** and **three distinct moments of inertia**. This means that the object has three distinct "shapes" on each axis, and as such, the axes require a different amount of torque to rotate around. Two of these axes will have the smallest and largest moments of inertia of the object, which we can call the **first** and **third** principal axes respectively. The other, which we call the **secondary principal axis** or "**intermediate axis**," will have a moment of inertia that is somewhere in between. 

Suppose we then rotate the object around these axes. Rotations around the **first** and **third principal axes** are "*stable*" -- in other words, if some disturbance is applied to the rotation, it will *stabilize* and continue rotating as if nothing has happened. However, the **intermediate axis** is "*unstable*" -- if a disturbance is applied to a rotation around it, the object will *accelerate* and begin to rotate around *another* axis.

A mathematical analysis of this phenomenon can be found on the theorem's [Wikipedia page](https://en.wikipedia.org/wiki/Tennis_racket_theorem#Theory). To summarize in words, we can use Euler's equations to describe the rotation of the object. Performing algebraic manipulation on these equations yields that the second derivative of the angular velocity of an axis is simply some quantity times the angular velocity itself. For the **first** and **third principal axes**, this quantity is negative, and as such, the second derivative decreases, which leads angular velocity to decrease. For the **intermediate axis**, this quantity is positive, which causes the angular velocity to increase.

## The Algorithm

Assume the mass is evenly distributed through the object, and that the center is fixed (meaning the only possible motion is rotation).

- Initialize velocity, model (/rotation) matrix, moment of inertia on model's xyz axes
- Initialize moment of inertia on world's xyz axes, angular momentum in world coords
- For every frame:
   - Based on the angular momentum, the velocity vectors of the model's points are updated to be orthogonal to the axis that the object is being rotated around.
   - And based on this new velocity vector, the rotation matrix (that converts from model to world coordinates) rotates model points in that direction.
   - Object is re-rendered for this frame, to reflect its new position after some time t (since last frame) has passed.

The Dzhanibekov effect occurs if we have the appropriate initial velocity vectors, aka what direction the object initially tries to move in, which should be close to the intermediate axis. Though the effect can occur for any rigid body independent of its physical complexity, the assumption of an evenly dense object means that any shape, as long as it has the same three moments of inertia, will rotate identically.

- Because the object itself does not warp, the moment of inertia in the model coordinate will not change. (Rigidity) The moment of inertia in the world coordinate, because of the rotation, will.
- Since there are no external forces and the mass does not change, angular momentum in the world coordinate is preserved (Conservation of angular momentum).
- Since there are no external forces, energy in the world coordinate is preserved (Conversation of energy).

## Conclusion

We were able to implement Sam Buss's algorithm for animating rigid body rotations that preserve energy more efficiently. However, we were unable to accurately recreate the Dzhanikebov effect in its entirety. In the end, though, we were able to find several rotational examples (depending on the initial velocity vectors and model's moments of inertia) that align with the principle of unpredictable intermediate axis rotation. :)

In the future, we would've liked to determine which starting parameters would give us a more accurate representation, as well as put in some funny models (e.g. rubber duckies, T-handles), and implement translation.
