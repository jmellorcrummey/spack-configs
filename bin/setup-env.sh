#!/bin/sh

# This script must be sourced
sourced=0
if [ -n "$ZSH_VERSION" ]; then
  case ${ZSH_EVAL_CONTEXT} in *:file) sourced=1 ;; esac
elif [ -n "$KSH_VERSION" ]; then
  [ "$(cd -- "$(dirname -- "$0")" && \
  pwd -P)/$(basename -- "$0")" != "$(cd -- "$(dirname -- "${.sh.file}")" && \
  pwd -P)/$(basename -- "${.sh.file}")" ] && \
  sourced=1
elif [ -n "$BASH_VERSION" ]; then
  (return 0 2>/dev/null) && sourced=1
else
  # All other shells: examine $0 for known shell binary filenames.
  # Detects `sh` and `dash`; add additional shell filenames as needed.
  case ${0##*/} in
    csh|-csh|tcsh|-tcsh) echo "csh/tcsh is unsupported" ; exit 1 ;;
    sh|-sh|dash|-dash) sourced=1 ;;
  esac
fi

if [ "${sourced}" = 0 ]; then
  echo "This script must be sourced!" >&2
  exit 1
fi

if [ "x$1" = "x" ]; then
  echo "Usage: $0 <root-deploy-dir>"
  echo "  root-deploy-dir should contain spack, spack-config, and cfg subdirectories"
else
  spack_root="$1"
fi

# Determine the system we're running on
case "${LMOD_SYSTEM_NAME}" in
  summit|frontier|crusher) ;;
*)
  echo "Unrecognized system '${LMOD_SYSTEM_NAME}', where are you?" >&2 ; return ;;
esac

# Detach from the user installation
export SPACK_SYSTEM_CONFIG_PATH="${root}/../cfg/${LMOD_SYSTEM_NAME}.system"
export SPACK_USER_CONFIG_PATH="${root}/../cfg/${LMOD_SYSTEM_NAME}.user"
export SPACK_USER_CACHE_PATH="${root}/cache/${LMOD_SYSTEM_NAME}"

# Load Spack
. "${spack_root}/share/spack/setup-env.sh"
echo "Spack loaded at ${SPACK_ROOT}" >&2

# Set the umask to make things group-writable by default
umask u=rwx,g=rwx,o=rx
