========================================
NEP 47 — Adopting the array API standard
========================================

:Author: Ralf Gommers <ralf.gommers@gmail.com>
:Author: Stephan Hoyer <shoyer@gmail.com>
:Author: Aaron Meurer <asmeurer@gmail.com>
:Status: Draft
:Type: Standards Track
:Created: 2021-01-21
:Resolution: 


Abstract
--------

We propose to adopt the `Python array API standard`_, developed by the
`Consortium for Python Data API Standards`_. Implementing this as a separate
new namespace in NumPy will allow authors of libraries which depend on NumPy 
as well as end users to write code that is portable between NumPy and all
other array/tensor libraries that adopt this standard.

.. note::

    We expect that this NEP will remain in a draft state for quite a while.
    Given the large scope we don't expect to propose it for acceptance any
    time soon; instead, we want to solicit feedback on both the high-level
    design and implementation, and learn what needs describing better in this
    NEP or changing in either the implementation or the array API standard
    itself.
    

Motivation and Scope
--------------------

Python users have a wealth of choice for libraries and frameworks for
numerical computing, data science, machine learning, and deep learning. New
frameworks pushing forward the state of the art in these fields are appearing
every year. One unintended consequence of all this activity and creativity
has been fragmentation in multidimensional array (a.k.a. tensor) libraries -
which are the fundamental data structure for these fields. Choices include
NumPy, Tensorflow, PyTorch, Dask, JAX, CuPy, MXNet, Xarray, and others.

The APIs of each of these libraries are largely similar, but with enough
differences that it’s quite difficult to write code that works with multiple
(or all) of these libraries. The array API standard aims to address that
issue, by specifying an API for the most common ways arrays are constructed
and used. The proposed API is quite similar to NumPy's API, and deviates mainly
in places where (a) NumPy made design choices that are inherently not portable
to other implementations, and (b) where other libraries consistently deviated
from NumPy on purpose because NumPy's design turned out to have issues or
unnecessary complexity.

For a longer discussion on the purpose of the array API standard we refer to
the `Purpose and Scope section of the array API standard <https://data-apis.github.io/array-api/latest/purpose_and_scope.html>`__
and the two blog posts announcing the formation of the Consortium [1]_ and
the release of the first draft version of the standard for community review [2]_.

The scope of this NEP includes:

- Adopting the 2021 version of the array API standard
- Adding a separate namespace, tentatively named ``numpy.array_api``
- Changes needed outside of the new namespace, for example a new dunder
  method and a new attribute on the ``ndarray`` object
- Implementation choices, and differences between functions in the new
  namespace with those in the main ``numpy`` namespace
- Maintenance effort and testing strategy
- Impact on NumPy's total exposed API surface and on other future and
  under-discussion design choices
- Relation to existing and proposed NumPy array protocols
  (``__array_ufunc__``, ``__array_function__``, ``__array_module__``).
- Required improvements to existing NumPy functionality

Out of scope for this NEP are:

- Changes in the array API standard itself. Those are likely to come up
  during review of this NEP, but should be upstreamed as needed and this NEP
  subsequently updated.


Usage and Impact
----------------

*This section will be fleshed out later, for now we refer to the use cases given
in* `the array API standard Use Cases section <https://data-apis.github.io/array-api/latest/use_cases.html>`__

In addition to those use cases, the new namespace contains functionality that
is widely used and supported by many array libraries. As such, it is a good
set of functions to teach to newcomers to NumPy and recommend as "best
practice". That contrasts with NumPy's main namespace, which contains many
functions and objects that have been superceded or we consider mistakes - but
that we can't remove because of backwards compatibility reasons.

Adoption in downstream libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- The prototype implementation will be used with SciPy, scikit-learn and
  other libraries of interest that depend on NumPy, in order to get more
  experience with the design and find out if any important parts are missing.
- Removing or working around ``asarray`` in downstream libraries


Backward compatibility
----------------------

No deprecations or removals of existing NumPy APIs are proposed.

The only potential backwards-incompatible changes we may have to consider
are related to ``ndarray`` behaviour that cannot easily be duplicated or
worked around in the separate namespace. For example, the standard specifies
casting rules that conflict with the value-based casting NumPy currently does,
and the best way of adhering to the standard with no or minor backwards
compatibility impact is still TBD. The standard also does not support as many
indexing methods as NumPy does - how to deal with that needs to be discussed.


High-level design
-----------------

The array API standard consists of approximately 120 objects, all of which
have a direct NumPy equivalent. This figure shows what is included at a high level:

*TODO: insert scope figure from https://data-apis.github.io/array-api/latest/purpose_and_scope.html*

The most important changes are:

- Functions in the ``array_api`` namespace:

    - do not accept ``array_like`` inputs, only ``ndarray``,
    - do not support ``__array_ufunc__`` and ``__array_function__``,
    - use positional-only and keyword-only parameters in their signatures,
    - have inline type annotations,
    - may have minor changes to signatures and semantics of individual
      functions compared to their equivalents already present in NumPy,
    - only support dtype literals, not format strings or other ways of
      specifying dtypes

- DLPack_ support will be added to NumPy,
- New syntax for "device support" will be added, through a ``.device``
  attribute added to ``ndarray`` and ``device=`` keywords in array creation
  functions in the ``array_api`` namespace.

Improvements to existing NumPy functionality that are needed include:

- Add support for stacks of matrices to some functions in ``numpy.linalg``
  that are currently missing such support.
- Add the ``keepdims`` keyword to ``np.argmin`` and ``np.argmax``.


Functions in the ``array_api`` namespace
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

work these out:

- do not accept ``array_like`` inputs, only ``ndarray``,
- do not support ``__array_ufunc__`` and ``__array_function__``,
- use positional-only and keyword-only parameters in their signatures,
- have inline type annotations,


DLPack support for zero-copy data interchange
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ability to convert one kind of array into another kind is valuable, and
indeed necessary when downstream libraries want to support multiple kinds of
arrays. This requires a well-specified data exchange protocol. NumPy already
supports two of these, namely the buffer protocol (i.e., PEP 3118), and
the ``__array_interface__`` (Python side) / ``__array_struct__`` (C side)
protocol. Both work similarly, letting the "producer" describe how the data
is laid out in memory so the "consumer" can construct its own kind of array
with a view on that data. 

DLPack works in a very similar way. The main reasons to prefer DLPack over
the options already present in NumPy are:

1. DLPack is the only protocol with device support (e.g., GPUs using CUDA or
   ROCm drivers, TPUs). NumPy is CPU-only, but other array libraries are not.
   Having one protocol per device isn't tenable, hence device support is a
   must.
2. Widespread support. DLPack has the widest adoption of all protocols, only
   NumPy is missing support. And the experiences of other libraries with it
   are positive. This contrasts with the protocols NumPy does support, which
   are used very little - when other libraries want to interoperate with
   NumPy, they typically use the (more limited, and NumPy-specific)
   ``__array__`` protocol.

Adding support for DLPack to NumPy entails:

- Adding a ``ndarray.__dlpack__`` method
- Adding a ``from_dlpack`` function, which takes as input an object
  supporting ``__dlpack__``, and returns an ``ndarray``.

DLPack is current a ~200 LoC header, and is meant to be included directly, so
no external dependency is needed. Implementation should be straightforward.


Syntax for device support 
~~~~~~~~~~~~~~~~~~~~~~~~~


Dtypes and casting rules
~~~~~~~~~~~~~~~~~~~~~~~~

- Supported dtypes
- Rationale for no complex support
- Casting rules and options for supporting them


Fancy indexing, ``ndarray`` methods, and other "extras"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- Things that will leak into the ``array_api`` namespace because they're too
  hard to keep out


Implementation
--------------

A mostly complete prototype of the ``array_api`` namespace can be found in
https://github.com/data-apis/numpy/tree/array-api/numpy/_array_api.
The docstring in ``__init__.py`` has notes on completeness of the implementation.
The code for the wrapper functions also contains ``# TODO:`` comments
everywhere there is a difference with the NumPy API.
Two parts not implemented are changes to ``ndarray``, and DLPack support.



Feedback from downstream library authors
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO - this can only be done after trying out some use cases


Related Work
------------

TODO 


Alternatives
------------



Discussion
----------

- `First discussion on the mailing list about the array API standard <https://mail.python.org/pipermail/numpy-discussion/2020-November/081181.html>`__


References and Footnotes
------------------------

.. _Python array API standard: https://data-apis.github.io/array-api/latest

.. _Consortium for Python Data API Standards: https://data-apis.org/

.. _DLPack: https://github.com/dmlc/dlpack

.. [1] https://data-apis.org/blog/announcing_the_consortium/

.. [2] https://data-apis.org/blog/array_api_standard_release/


Copyright
---------

This document has been placed in the public domain. [1]_