LWDirectoryScanner
==================

LWDirectoryScanner is a C CLI for analyzing the contents of a given directory. It can also
serialize a summary of the directory into a CBOR file.


Installing LWDirectoryScanner
-----------------------------

If you are using a Linux machine:

.. code-block::

    git clone --recursive https://github.com/leeway64/LWDirectoryScanner.git
    cd LWDirectoryScanner
    conan install . -s compiler.version=10
    gcc src/main.c src/scanner_helpers.c @conanbuildinfo.args -o bin/LWDirectoryScanner


If you are using a Windows machine:

.. code-block::

    git clone --recursive https://github.com/leeway64/LWDirectoryScanner.git
    cd LWDirectoryScanner
    conan install .
    cl /EHsc src/main.c src/scanner_helpers.c @conanbuildinfo.args /link /out:bin/LWDirectoryScanner.exe


Things to keep in mind
~~~~~~~~~~~~~~~~~~~~~~

- When using ``cl``, use the ``x64`` version. This can be easily done through the x64 Native
  Tools Command Prompt.

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
| ``conan remove <package_name>`` uninstalls ``<package_name>``.                          |
+-----------------------------------------------------------------------------------------+


Usage
-------

.. code-block::

    $ cd bin
    $ ./LWDirectoryScanner --help

    Usage: LWDirectoryScanner [OPTIONS]
    Options:
        <DIRECTORY>           Scans <DIRECTORY>, prints out a summary of the directory to the console, and serializes the summary into a CBOR file.
        --tree <DIRECTORY>    Prints out the contents of <DIRECTORY> in a tree-like structure.


Example
--------

.. code-block::

    $ ./LWDirectoryScanner --tree ../tests/test_dirs

    Directory selected: ../tests/test_dirs/
        .test_editorconfig
        a/
            test.txt
        b/
            main.cpp
            main.py
        c/
            c1/
                Document.rtf
            test.js
        e/
            d1/
                Spreadsheet.ods
            e1/
                e2/
                    CMakeLists.txt
                    e3/
                        header.hpp
                    test_html.html


    $ ./LWDirectoryScanner ../tests/test_dirs

    Directory selected: ../tests/test_dirs
            Number of directories: 9
            Number of files: 10
            Deepest folder depth: 4

    Serialization complete: Directory summary has been serialized into test_dirs_summary.cbor


Notice that ``LWDirectoryScanner ../tests/test_dirs`` will create a CBOR file containing the number
of directories, the number of files, etc., contained in ``../tests/test_dirs``.

You may deserialize this CBOR file using the included `deserializer <src/CBOR_Deserializer.py>`_


Running Tests
--------------

Running LWDirectoryScanner Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If using Linux:


.. code-block::

    gcc src/scanner_helpers.c Unity/src/unity.c tests/test_suite.c @conanbuildinfo.args -o tests/test_suite
    cd tests
    ./test_suite


If using Windows:

.. code-block::

    cl /EHsc src/scanner_helpers.c Unity/src/unity.c tests/test_suite.c @conanbuildinfo.args /link /out:tests/test_suite.exe
    cd tests
    test_suite
    


Running CBOR Deserializer Tests
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the root directory of this project, if using Linux, run:

.. code-block::

    python3 -m venv .venv
    source .venv/bin/activate
    pip install -r requirements.txt
    pytest

If using Windows, run:

.. code-block::

    py -3 -m venv .venv
    .venv/Scripts/activate
    pip install -r requirements.txt
    pytest


Third-Party Tools
-----------------

- `Conan <https://conan.io/>`_ (MIT License): C/C++ package manager.
- `libcbor <https://github.com/PJK/libcbor>`_ (MIT License): C library for serializing and deserializing CBOR files.
- `tinydir <https://github.com/cxong/tinydir>`_ (BSD-2-Clause): C directory and file reader.
- `Unity Test <https://github.com/ThrowTheSwitch/Unity>`_ (MIT License): C unit testing framework.
- `c-vector <https://github.com/eteran/c-vector>`_ (MIT License): An implementation of a C++ std::vector in C.
