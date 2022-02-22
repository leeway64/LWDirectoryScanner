LWDirectoryScanner
==================

Installation
------------

Because I am using gcc to compile this program, there needs to be a specific Conan profile (I have
called my profile gccProfile). gccProfile might look something like this:

..code-block::

   [settings]
	   arch=x86_64
	   build_type=Release
	   compiler=gcc
	   compiler.version=8
	   os=Linux

   [options]
   [build_requires]
   [env]

I need to use this specific Conan profile because, according to
`the libcbor ConanCenter page`<https://conan.io/center/libcbor?os=Linux&tab=configuration>_, all
the configurations that use gcc as the compiler has Linux as the OS.

To create a new Conan profile, use the command ``conan profile new <ProfileName>``.

Recall that all Conan profiles can be found at ``<userhome>/.conan/profiles``.

1. Install the CBOR Conan package with ``conan install . --profile gccProfile``.
	
	- If you name your profile something else, just replace ``--profile gccProfile`` with
	  ``--profile <ProfileName>``.


#. Compile the binary with ``gcc src/main.c '@conanbuildinfo.args' -o bin/main``.

	- The file ``conanbuildinfo.args`` is created from the ``compiler_args`` generator in the
	  conanfile; ``conanbuildinfo.args`` contains command line arguments for ``gcc``, ``clang``,
	  and ``cl``. This allows the use of the previous compilers in compiling the program.

Third-Party Tools
-----------------

- Conan:
- gcc:
