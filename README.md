<!--
  ** File Name: README.md
  ** Author:    Aditya Ramesh
  ** Date:      08/25/2015
  ** Contact:   _@adityaramesh.com
-->

# Overview

This project is an attempt to study and reproduce the optimizations used by
Blaze in evaluating various mathematical expressions.

## Notes

- Directories of interest in Blaze:
  - `include/blaze-2.4/blaze/math/expressions`: contains the implementations of
    the mathematical operations.
  - `include/blaze-2.4/blaze/math/intrinsics`: definitions of SIMD instrinsics.

## Operations

- I plan to study the implementations of the following operations. Structured
  matrices (including sparse matrices) are not yet considered.
  - Elementwise operations.
  - Inner product.
  - Outer product.
  - Matrix multiplication.
