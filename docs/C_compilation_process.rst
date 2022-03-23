C Compilation Process
=======================

The following steps outline the process for compiling a C program (from 
`How the Compilation Process Works for C Programs <https://medium.datadriveninvestor.com/compilation-process-db17c3b58e62>`_).

.. contents:: **Table of Contents**

Preprocessing
-------------

The preprocessor removes comments, expands macros, and expands included files (files that come
after the #include directive)

Compiling
----------

The output of the preprocessor is converted into assembly language. The output of this step are
`object files <https://stackoverflow.com/a/7718363>`_.

Assembling
-----------

The assembly language is converted into binary (ones and zeroes).

Linking
---------

All object code is combined into a single executable file.
