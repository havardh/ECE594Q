# ECE 594Q - Special Topics in Image Synthesis

This repository includes solutions to the assigments given in the ECE 594Q course at UCSB Winter 2014.

## Assignment 1 - Reyes style architecture

The first assigment (tag: Assignment1-Reyes) contains a simple Rendrer with a Reyes style architecture.
It can render Cylinders, Cones and Spheres in 3D space with a couple of shaders, namely texture, color and
displacement.

## Assignment 2 - RayTracer

The second assignment (tag: Assignment2-BasicRayTracer) is a whole new rendrer based on a technique called ray tracing.
The rendrer supports shadows, refletions and to a limited degree refractions. 

## Assignment 3 - Optimized RayTracer

The third assignment (tag: Assignment3-OptimizedRayTracer) enhances the raytracer from
assignment 2. It implementes a KD tree with a Surface Area Heuristic to speed up execution time. Additinal features are color and intersection shaders and antialiasing.

## Assignment 4 - PathTracer

The fourth assignment (tag: Assignment4-PathTracer) alters the raytracer to trace paths. This technique enables diffuse to diffuse reflection causing color bleeding. A simple OBJ file format loader is included and Environment Maps.