# CSE167-Final

poggers poggers jar on and k at yay wawhahwhwahwahwhwa

## Introduction

This project implements the **tennis racket theorem**, also known as the **Dzhanibekov effect**, which affects rigid bodies (i.e., those that don't change shape) with three moments of inertia (if an object can rotate around three different axes and "look" different). When rotating around two of the principal axes, the object only rotates around that axis. However, when rotating around the remaining axis, the object also produces a half-rotation around another axis.

## The Physics

Suppose we have an object that can experience the Dzhanibekov effect. Then, it must have three principal axes and three distinct moments of inertia. This means that the object has three distinct "shapes" on each axis, and as such, the axes require a different amount of torque to rotate around. Two of these axes will have the smallest and largest moments of inertia of the object, which we can call the first and third principal axes respectively. The other, which we call the secondary principal axis or "intermediate axis," will have a moment of inertia that is somewhere in between. 

Suppose we then rotate the object around these axes. Rotations around the first and third principal axes are "stable" -- in other words, if some disturbance is applied to the rotation, it will stabilize and continue rotating as if nothing has happened. However, the intermediate axis is "unstable" -- if a disturbance is applied to a rotation around it, the object will accelerate and begin to rotate around another axis.

A mathematical analysis of this phenomenon can be found on the theorem's [Wikipedia page](https://en.wikipedia.org/wiki/Tennis_racket_theorem#Theory). To summarize in words, we can use Euler's equations to describe the rotation of the object. Performing algebraic manipulation on these equations yields that the second derivative of the angular velocity of an axis is simply some quantity times the angular velocity itself. For the first and third principal axes, this quantity is negative, and as such, the second derivative decreases, which leads angular velocity to decrease. For the intermediate axis, this quantity is positive, which causes the angular velocity to increase.
