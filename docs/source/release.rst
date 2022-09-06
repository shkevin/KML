===============
Release Process
===============

If substantial changes were made to the code:

#. Ensure C++ and Cython/Python integration works correctly.
#. Write any necessary examples for new code.
#. Ensure any new public interfaces have been added to the documentation

Then:

#. All tests pass on continuous integration
#. The changelog is up-to-date and dated
#. The version number is correct in:
    * setup.py
    * docs/conf.py
#. Check for new authors: ``git log --invert-grep --author='Kevin Cox'``
#. Tag the release: ``git tag -a x.y.z -m 'x.y.z release.'; git push --follow-tags``
#. Upload to PyPI: ``rm -rf dist; python setup.py sdist bdist_wheel; twine upload dist/*``
#. Build the documentation on manually and verify it is correct.
