This directory contains several files:

  package.py: 
    a new package.py file for hpctoolkit. a custom one is provided here to stick in spack/var/spack/repos/builtin/packages/hpctoolkit/
    because it specifies new capabilities not yet in hpctoolkit master: using mbedtls for MD5, the +cuda variant along with CUDA and
    CUPTI support.

  config.yaml:
    this includes paths where to put the module files and packages for a particular day's install. change the day before using it.

  packages.yaml:
    this includes configuration for LLNL's software environment, including MPI, CUDA, python, perl, etc.
    it also includes some hpctoolkit-specific information about package versions that we know we want, e.g. we must have Dyninst 10.1.0 
    because it includes new support for injecting GPU CFGs.
