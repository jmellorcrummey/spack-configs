This directory contains the various files, scripts, and instructions for installing hpctoolkit
at various sites, using Spack to do the install.

The top-level directory has an [install.txt](install.txt) script with detailed,
and hopefully, idiot-proof instructions for using Spack to install hpctoolkit.

It has a `bin` directory, containing a script named `spacklink` that will set up a spack
repository to do the installation at a specific `<site>` on a specific `<machine>`.

It has a number of sub-directories, named by `<site>`.
Each of those subdirectories contains one or more subdirectories, named by `<machine>`.

Each of those `<site>/<machine>` subdirectories contains several files:

- `<machine>.config.yaml`:

  specifies the directories in which to put the module files and packages for a particular install.

- `<machine>.modules.yaml`:

  specifies information about the modules to be built

- `<machine>.packages.yaml`:

  this includes configuration for the software environment, including MPI, CUDA, python, perl, etc.;
  specifies the build-dependency version for installing hpctoolkit

- `<machine>.spack.yaml`:

  this specifies a Spack environment file, which allows building several HPCToolkit configurations
  with Spack in one go. If present, the `spacklink` script will create a new directory parallel to
  the Spack repository called `spack-env`. The installation steps then become:

```shell
  $ spack/bin/spack -e spack-env concretize # add "-f" to re-concretize as needed
  $ spack/bin/spack -e spack-env install
```
