.. image:: ../_static/r_KMLSimple.png
   :width: 100px
   :align: right
   :target: https://github.com/shkevin/KML

.. _cpp_guidelines:

==============
C++ Guidelines
==============

Introduction
^^^^^^^^^^^^

The following rules present basic guidelines for the KML C++ code.
The goal is to have code that is formatted in a consistent and easily readable
way while at the same time not being overly complicated by specifying every
detail. For such guidelines to be practical, newcomers should be able to read
them within a few minutes and be able to memorize them. So these rules
intentionally do not cover every detail but rather aim at specifying only the
big, important things.

If this guide doesn't include a rule, the best practices would be to follow the
Google C++ Style Guide `Google C++ Style Guide <https://google.github.io/styleguide/cppguide.html>`_
Note, however, KML may deviate from the Google C++ coding style over time.

Folder Structure and File Naming
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Header files should be in a folder: `include/<name_of_the_project>/*`, e.g. `#include "KML/include/Example.h"`
- File extension for header files: `.h`
- Source files should be in a folder named `src/`. The file should have the same name as the header with extension `.cc`.
- When using templates:  If you want to separate declaration and definition, put the declaration to a `.h` header file as usual and the definition to a file with extension `.tcc` in the same directory (which is included at the bottom of the `.h` file).
- Preferably each class should be in a separate file with name class_name_in_lower_case.  However, this is not a strict rule, if several smaller classes are logically closely related, they may go to the same file.
- The C++/Cython code for wrapping C++ code to Python must be placed in `tools/cython/KML` in the corresponding folder, relative to the C++ folder structure.

Naming
~~~~~~

Give as descriptive a name as possible, within reason. Do not worry about saving
horizontal space as it is far more important to make your code immediately
understandable by a new reader. Do not use abbreviations that are ambiguous or
unfamiliar to readers outside of KML, and do not abbreviate by deleting
letters within a word. Abbreviations that would be familiar to someone outside
your project with relevant domain knowledge are OK. As a rule of thumb, an
abbreviation is probably OK if it's listed in Wikipedia.

Formatting of names should be as follows:

- files:
	FirstUpperCamelCase
- types (classes, structs, ...):
	FirstUpperCamelCase
- functions, methods:
	pascalCase
- member/class variables:
	m_variableName
- local variables:
	l_variableName
- constants:
	UPPER_CASE_WITH_UNDERSCORES
- global variables: Should generally be avoided but if needed, prefix them with:
    g\_, i.e. g_variable_name.

C++ Formatting
^^^^^^^^^^^^^^

Line Length
~~~~~~~~~~~

Limit the length of lines to 80 characters.

This may seem hard to follow sometimes but makes it much easier to view two or even three files
next to each other (important during code review or when resolving merge conflicts).

Indentation
~~~~~~~~~~~

- Use spaces instead of tabs.
- 4 spaces per "tab".
- Nested Namespaces should be tabbed.

.. code-block:: cpp
   :linenos:
   :caption: Example.h

    namespace bar
    {
        class Foo
        {
            public:
     	       void my_function(const Foo &foo, int *output_arg);
    	   }; // Foo
    } // namespace

Position of braces
~~~~~~~~~~~~~~~~~~

- Opening brace always goes to the next line.

Pass objects by const reference
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In general, non-primitive data types should be passed to functions by const
reference instead of by value.

.. code-block:: cpp
   :linenos:

   void foobar(const Foo &foo);  // good
   void foobar(Foo foo);  // results in copy of `foo`.

pragma once vs Include Guards
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Always use include guards instread of the `pragma once` standard. This prevents
any bugs on differing Operating Systems.
