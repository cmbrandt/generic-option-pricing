# Generic Option Pricing

This was a graduate school research project exploring different approaching for designing a Monte Carlo option pricing engine, developed between 2014 and 2015. My advisor for this work was Dr. Andrew Sutton, author and original implementer of the C++ Concepts Technical Specification.

The basis for this work was adapted from the book [C++ Design Patterns and Derivatives Pricing 2nd Edition](https://www.amazon.com/Patterns-Derivatives-Pricing-Mathematics-Finance/dp/0521721628) by Mark Joshi, where the author developed an option pricing framework based on an object-oriented (OO) design.  Our aim was to translate this first OO design to a generic programming design, then incorporate the (circa 2015) experimental language feature Concepts into the framework.

Over the coming weeks, I will be updating this repository to include an adaption of an unpublished white paper to the accompany the source code herein.  This white paper conducted an informal comparison of the above mentioned designs, elaborating on the complexity, maintainability, and reuse of different design approaches.  A simple performance comparison was performed, where we recognized a (roughly) 9-10% improvement for the generic programming and concept-driven designs over the object-oriented design, with the improvement coming entirely from the removal of virtual function calls.
