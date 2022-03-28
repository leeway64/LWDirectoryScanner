LWDirectoryScanner
==================

LWDirectoryScanner is a C CLI for analyzing the contents of a given directory. It can also
serialize a summary of the directory into a CBOR file.

Example
--------

.. code-block::

    $ LWDirectoryScanner --tree ../tests/test_dirs

    Directory selected: ../tests/test_dirs/
        0/
        a/
            test.txt
        b/
            main.cpp
            main.py
        c/
            c1/
                c2/
                    c3/
                        header.hpp
            d1/
                Spreadsheet.ods



    $ LWDirectoryScanner ../tests/test_dirs

    Directory selected: ../tests/test_dirs
            Number of directories: 8
            Number of files: 5

    Serialization complete: Directory summary has been serialized into test_dirs_summary.cbor


Notice that ``LWDirectoryScanner ../tests/test_dirs`` will create a CBOR file containing the number
of directories, the number of files, etc., contained in ``../tests/test_dirs``.


Usage
-------

.. code-block::

    Usage: LWDirectoryScanner [OPTIONS]
    Options:
        <DIRECTORY>           Scans <DIRECTORY>, prints out a summary to the console, and serializes the summary of the directory statistics into a CBOR file.
        --tree <DIRECTORY>    Prints out the contents of <DIRECTORY> in a tree-like structure.


Installing LWDirectoryScanner
------------------------------

1. Clone this repository onto your machine using
   ``git clone --recursive https://github.com/leeway64/LWDirectoryScanner.git``.

#. In the root directory of this repository, install the Conan packages with ``conan install .``.

#. If you are using a Linux machine, compile the binary with
   ``gcc src/main.c src/scanner_helpers.h src/scanner_helpers.c '@conanbuildinfo.args' -o bin/LWDirectoryScanner``.
   
   - If you are using a Windows machine, compile the binary with
     ``cl /EHsc src/main.c src/scanner_helpers.c @conanbuildinfo.args /link /out:bin/LWDirectoryScanner.exe``

     - When using ``cl``, remember to use the ``x64`` version.

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
|                                                                                         |
| conan remove <package_name> uninstalls <package_name>.                                  |
+-----------------------------------------------------------------------------------------+


Running Tests
--------------

Running LWDirectoryScanner Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. If you are using a Linux machine, compile the test binary with ````.
   
   - If you are using a Windows machine, compile the test binary with
     ``cl /EHsc src/scanner_helpers.c Unity/src/unity.c tests/test_suite.c @conanbuildinfo.args /link /out:tests/test_suite.exe``.

#. To run the test binary, enter ```` if using Linux. If using Windows, enter ``cd tests``, then
   ``test_suite``.


Running CBOR Deserializer Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the root directory of this project, if using Linux, run:

.. code-block::

    $ python3 -m venv .venv
    $ source .venv/bin/activate
    $ pip install -r requirements.txt
    $ pytest

If using Windows, run:

.. code-block::

    $ py -3 -m venv .venv
    $ .venv/Scripts/activate
    $ pip install -r requirements.txt
    $ pytest


Third-Party Tools
-----------------

- `Conan <https://conan.io/>`_ (MIT License): C/C++ package manager.
- `libcbor <https://github.com/PJK/libcbor>`_ (MIT License): C library for serializing and deserializing CBOR files.
- `tinydir <https://github.com/cxong/tinydir>`_ (BSD-2-Clause): C directory and file reader.
- `Unity Test <https://github.com/ThrowTheSwitch/Unity>`_ (MIT License): C unit testing framework.
