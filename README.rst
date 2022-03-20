LWDirectoryScanner
==================

LWDirectoryScanner is a C CLI for analyzing the contents of a given directory.

Example
--------

Usage
-------

Installing LWDirectoryScanner
------------------------------

The easiest way to get LWDirectoryScanner is to download the latest binary from the
`releases page <https://github.com/leeway64/LWDirectoryScanner/releases>`_.

You can also build LWDirectoryScanner on your own machine.

1. Clone this repository onto your machine.

#. In the root directory of this repository, install the Conan packages with ``conan install .``.

#. Add Unity Test as a Git submodule in the root directory.

#. If you are using a Linux machine, compile the binary with
   ``gcc src/main.c src/scanner_helpers.h src/scanner_helpers.c '@conanbuildinfo.args' -o bin/LWDirectoryScanner``.
   
   - If you are using a Windows machine, compile the binary with
     ``cl /EHsc src/main.c src/scanner_helpers.c @conanbuildinfo.args /link /out:bin/LWDirectoryScanner``

	 - The file ``conanbuildinfo.args`` is created from the ``compiler_args`` generator in the
	   conanfile; ``conanbuildinfo.args`` contains command line arguments for ``gcc``, ``clang``,
	   and ``cl``. This allows the use of the previous compilers in compiling the program.
	
	 - Refer to `this guide <docs/C_compilation_process.rst>`_ for more information on what exactly
	   happens when a C program is compiled.


+-----------------------------------------------------------------------------------------+
|               Helpful Conan Tips                                                        |
+=========================================================================================+
| To create a new Conan profile, use the command ``conan profile new <ProfileName>``.     |
|                                                                                         |
| Recall that all Conan profiles can be found at ``<userhome>/.conan/profiles``.          |
+-----------------------------------------------------------------------------------------+


Running Tests
--------------

Running LWDirectoryScanner Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. If you are using a Linux machine, compile the test binary with ````.
   
   - If you are using a Windows machine, compile the test binary with
     ``cl Unity/src/unity.c tests/test_suite.c /link /out:tests/test_suite.exe``.

#. To run the test binary, enter ```` if using Linux. If using Windows, enter `cd tests`, then
   `test_suite`.


Running CBOR Deserializer Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the root directory of this project, run:

.. code-block::

    $ .venv/Scripts/activate
    $ pytest


Third-Party Tools
-----------------

- `Conan <https://conan.io/>`_ (MIT License): C/C++ package manager.
- `libcbor <https://github.com/PJK/libcbor>`_ (MIT License): C library for serializing and deserializing CBOR files.
- `tinydir <https://github.com/cxong/tinydir>`_ (BSD-2-Clause): C directory and file reader.
- `Unity Test <https://github.com/ThrowTheSwitch/Unity>`_ (MIT License): C unit testing framework.
