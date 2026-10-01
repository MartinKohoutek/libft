#!/bin/bash

set -e

VERSION="2.0.2"
PREFIX="$(dirname "$0")/cmocka"
TMP="${TMPDIR:-/tmp}/cmocka-install-$$"
URL="https://gitlab.com/cmocka/cmocka/-/archive/cmocka-${VERSION}/cmocka-${VERSION}.tar.gz"

CC="${CC:-cc}"
AR="${AR:-ar}"

echo "==> Installing CMocka ${VERSION}"
echo "    prefix: $PREFIX"

rm -rf "$TMP"
mkdir -p "$TMP"

echo "==> Downloading CMocka..."
curl -L "$URL" -o "$TMP/cmocka.tar.gz"

echo "==> Extracting..."
tar -xf "$TMP/cmocka.tar.gz" -C "$TMP"

SRC=$(find "$TMP" -mindepth 1 -maxdepth 1 -type d | head -n 1)

echo "    source: $SRC"
BUILD="$TMP/build"

echo "==> Checking source..."

test -f "$SRC/include/cmocka.h"
test -f "$SRC/include/cmocka_pbc.h"
test -f "$SRC/include/cmocka_version.h.cmake"
test -f "$SRC/src/cmocka.c"

mkdir -p "$BUILD/include"

echo "==> Creating config.h..."

cat > "$BUILD/config.h" <<'EOF'
#define PACKAGE "cmocka"
#define VERSION "2.0.2"
#define LIBDIR "lib"
#define PLUGINDIR "-0"

#define HAVE_ASSERT_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_MALLOC_H 1
#define HAVE_MEMORY_H 1
#define HAVE_SETJMP_H 1
#define HAVE_SIGNAL_H 1
#define HAVE_STDARG_H 1
#define HAVE_STDDEF_H 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_TIME_H 1
#define HAVE_UNISTD_H 1

#define HAVE_STRUCT_TIMESPEC 1
#define HAVE_UINTPTR_T 1

#define HAVE_CALLOC 1
#define HAVE_EXIT 1
#define HAVE_FPRINTF 1
#define HAVE_SNPRINTF 1
#define HAVE_VSNPRINTF 1
#define HAVE_FREE 1
#define HAVE_LONGJMP 1
#define HAVE_SIGLONGJMP 1
#define HAVE_MALLOC 1
#define HAVE_MEMCPY 1
#define HAVE_MEMSET 1
#define HAVE_PRINTF 1
#define HAVE_SETJMP 1
#define HAVE_SIGNAL 1
#define HAVE_STRCMP 1
#define HAVE_STRSIGNAL 1
#define HAVE_CLOCK_GETTIME 1

#define HAVE_GCC_THREAD_LOCAL_STORAGE 1
#define HAVE_CLOCK_REALTIME 1

#define WORDS_SIZEOF_VOID_P 8
EOF

echo "==> Creating cmocka_version.h..."

sed \
	-e 's/@cmocka_VERSION_MAJOR@/2/' \
	-e 's/@cmocka_VERSION_MINOR@/0/' \
	-e 's/@cmocka_VERSION_PATCH@/2/' \
	"$SRC/include/cmocka_version.h.cmake" \
	> "$BUILD/include/cmocka_version.h"

echo "==> Compiling..."

"$CC" \
	-std=c99 \
	-Wall \
	-Wextra \
	-Werror \
	-D_GNU_SOURCE \
	-D_XOPEN_SOURCE=700 \
	-DHAVE_CONFIG_H \
	-I"$SRC/include" \
	-I"$BUILD" \
	-c "$SRC/src/cmocka.c" \
	-o "$BUILD/cmocka.o"

echo "==> Creating static library..."

"$AR" rcs "$BUILD/libcmocka.a" "$BUILD/cmocka.o"

echo "==> Installing..."

rm -rf "$PREFIX"

mkdir -p "$PREFIX/include" "$PREFIX/lib"

cp "$SRC/include/cmocka.h" "$PREFIX/include/"
cp "$SRC/include/cmocka_pbc.h" "$PREFIX/include/"
cp "$BUILD/include/cmocka_version.h" "$PREFIX/include/"
cp "$BUILD/libcmocka.a" "$PREFIX/lib/"

echo "==> Done."
echo
echo "CMocka installed to:"
echo "  $PREFIX"
echo
echo "Files:"

find "$PREFIX" -type f -print

rm -rf "$TMP"