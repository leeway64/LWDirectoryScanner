LWDirectoryScanner
==================

LWDirectoryScanner is a C CLI for analyzing the contents of a given directory.

Example
--------

Usage
-------

Installing LWDirectoryScanner
------------------------------

1. Install the CBOR Conan package with ``conan install .``.

#. If you are using a Linux machine, compile the binary with ``gcc src/main.c src/scanner_helpers.h src/scanner_helpers.c '@conanbuildinfo.args' -o bin/LWDirectoryScanner``.
   
   If you are using a Windows machine, compile the binary with ``cl /EHsc src/main.c src/scanner_helpers.c @conanbuildinfo.args /link /out:bin/LWDirectoryScanner``

	- The file ``conanbuildinfo.args`` is created from the ``compiler_args`` generator in the
	  conanfile; ``conanbuildinfo.args`` contains command line arguments for ``gcc``, ``clang``,
	  and ``cl``. This allows the use of the previous compilers in compiling the program.
	
	- Refer to `this guide <docs/C_compilation_process.rst>`_ for more information on what exactly
	  happens when a C program is compiled.


+-----------------------------------------------------------------------------------------+
|Helpful Conan Tips                                                                       |
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
   
   If you are using a Windows machine, compile the test binary with ````.

#. To run the test binary, simply enter ````.


Running CBOR Deserializer Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the root directory of this project, run:

.. code-block::

    $ .venv/Scripts/activate
    $ pytest


Third-Party Tools
-----------------

- `Conan <https://conan.io/>`_ (MIT License): Package manager.
- `libcbor <https://github.com/PJK/libcbor>`_ (MIT License): C library for serializing and deserializing CBOR files.
- `tinydir <https://github.com/cxong/tinydir>`_ (BSD-2-Clause): C directory and file reader.
- `cunit <http://cunit.sourceforge.net/>`_ (BSD-3-Clause): Unit testing framework.
