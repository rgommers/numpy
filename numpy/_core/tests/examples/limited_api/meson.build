project('checks', 'c', 'cython')

py = import('python').find_installation(pure: false)

cc = meson.get_compiler('c')
cy = meson.get_compiler('cython')

# Keep synced with pyproject.toml
if not cy.version().version_compare('>=3.0.6')
  error('tests requires Cython >= 3.0.6')
endif

np_dep = dependency('numpy')

py.extension_module(
    'limited_api1',
    'limited_api1.c',
    dependencies: [np_dep],
    limited_api: '3.6',
)

py.extension_module(
    'limited_api_latest',
    'limited_api_latest.c',
    dependencies: [np_dep],
    limited_api: py.language_version(),
)

py.extension_module(
    'limited_api2',
    'limited_api2.pyx',
    install: false,
    c_args: [
      # Require 1.25+ to test datetime additions
      '-DNPY_TARGET_VERSION=NPY_2_0_API_VERSION',
    ],
    dependencies: [np_dep],
    limited_api: '3.7',
)
