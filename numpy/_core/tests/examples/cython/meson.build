project('checks', 'c', 'cython')

py = import('python').find_installation(pure: false)

cc = meson.get_compiler('c')
cy = meson.get_compiler('cython')

# Keep synced with pyproject.toml
if not cy.version().version_compare('>=3.0.6')
  error('tests requires Cython >= 3.0.6')
endif

np_dep = dependency('numpy')

cython_args = []
if cy.version().version_compare('>=3.1.0')
  cython_args += ['-Xfreethreading_compatible=True']
endif

py.extension_module(
    'checks',
    'checks.pyx',
    install: false,
    c_args: [
      '-DNPY_NO_DEPRECATED_API=0',  # Cython still uses old NumPy C API
      # Require 1.25+ to test datetime additions
      '-DNPY_TARGET_VERSION=NPY_2_0_API_VERSION',
    ],
    dependencies: [np_dep],
    cython_args: cython_args,
)
