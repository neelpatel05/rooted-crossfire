
AC_DEFUN([CF_CHECK_PYTHON],
[
	PYTHON_LIB=""
	PY_LIBS=""
	PY_INCLUDES=""
	dir=""
	if test "x$PYTHON_HOME" != "x"; then
		for dir in $PYTHON_HOME/include/python{,2.5,2.4,2.3,2.2,2.1,2.0} ; do
			AC_CHECK_HEADERS(["$dir/Python.h"],[cf_have_python_h=yes])
			if test "x$cf_have_python_h" != "x" ; then
				PY_INCLUDES="-I$dir"
				break
			fi
		done
		PYTHON_SEARCH=$PYTHON
	else
		AC_CHECK_HEADERS([Python.h],[cf_have_python_h=yes])
		if test "x$cf_have_python_h" = "x"  ; then
			for dir in  /usr{,/local}/include/python{,2.5,2.4,2.3,2.2,2.1,2.0} ; do
				AC_CHECK_HEADERS(["$dir/Python.h"],[cf_have_python_h=yes])
				if test "x$cf_have_python_h" != "x" ; then
					PY_INCLUDES="-I$dir"
					break
				fi
			done
		else
			PY_INCLUDES=""
		fi
	fi

	if test "x$cf_have_python_h" = "xyes" ; then
		PYTHON_LIB=""
		if test "x$PYTHON_HOME" != "x"; then
			# I am going of how manually compiled python installed on
			# my system.  We can't use AC_CHECK_LIB, because that will
			# find the one in the stanard location, which is what we
			# want to avoid.
			python=`echo $dir | awk -F/ '{print $NF}'`;
			AC_MSG_CHECKING([For python lib in various places])
			if test -f $PYTHON_HOME/lib/lib$python.so ; then
				# Hopefully -R is a universal option
				AC_MSG_RESULT([found in $PYTHON_HOME/lib/])
				if test -n "$hardcode_libdir_flag_spec" ; then
					oldlibdir=$libdir
					libdir="$PYTHON_HOME/lib/"
					rpath=`eval echo $hardcode_libdir_flag_spec`
					PYTHON_LIB="$rpath -L$PYTHON_HOME/lib/ -l$python"
					echo "rpath=$rpath"
					libdir=$oldlibdir
				else
					PYTHON_LIB="-L$PYTHON_HOME/lib/ -l$python"
				fi

			elif test -f $PYTHON_HOME/lib/$python/lib$python.a ; then
				PYTHON_LIB="$PYTHON_HOME/lib/$python/lib$python.a"
				AC_MSG_RESULT([found in $PYTHON_HOME/lib/$python])
			elif test -f $PYTHON_HOME/lib/$python/config/lib$python.a ; then
				PYTHON_LIB="$PYTHON_HOME/lib/$python/config/lib$python.a"
				AC_MSG_RESULT([found in $PYTHON_HOME/lib/$python/config])
			fi

		else
	                for lib in python{,2.5,2.4,2.3,2.2,2.1,2.0} ; do
	                        AC_CHECK_LIB($lib, PyArg_ParseTuple,[PYTHON_LIB="-l$lib"])
	                        if test "x$PYTHON_LIB" != "x" ; then
	                                break
	                        fi
	                done

			# These checks are a bit bogus - would be better to use AC_CHECK_LIB,
			# but it caches the result of the first check, even if we run AC_CHECK_LIB
			# with other options.
			python=`echo $dir | awk -F/ '{print $NF}'`;
			if test "x$PYTHON_LIB" = "x"  ; then
				AC_MSG_CHECKING([For python lib in various places])
				if test -f /usr/lib/$python/lib$python.a ; then
					PYTHON_LIB="/usr/lib/$python/lib$python.a"
					AC_MSG_RESULT([found in /usr/lib/$python])
				elif test -f /usr/lib/$python/config/lib$python.a ; then
					PYTHON_LIB="/usr/lib/$python/config/lib$python.a"
					AC_MSG_RESULT([found in /usr/lib/$python/config])
				fi
			fi
		fi
		if test "x$PYTHON_LIB" != "x"  ; then
			AC_CHECK_LIB(pthread, main,  PY_LIBS="$PY_LIBS -lpthread", , $PY_LIBS )
			AC_CHECK_LIB(util, main,  PY_LIBS="$PY_LIBS -lutil", , $PY_LIBS )
			AC_CHECK_LIB(dl, main,  PY_LIBS="$PY_LIBS -ldl", , $PY_LIBS )

			AC_MSG_CHECKING([whether python supports the "L" format specifier])
			saved_LIBS="$LIBS"
			LIBS="$LIBS $PYTHON_LIB $PY_LIBS"
			saved_CFLAGS="$CFLAGS"
			CFLAGS="$CFLAGS $PY_INCLUDES"
			AC_TRY_RUN([
#include <Python.h>
#include <stdlib.h>

static PyObject *callback(PyObject *self, PyObject *args)
{
    long long val;

    if (!PyArg_ParseTuple(args, "L", &val))
	return NULL;
    if (val != 1)
	exit(1);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef methods[] = {
    {"callback", callback, METH_VARARGS},
    {NULL, NULL, 0, NULL},
};

int main()
{
    Py_Initialize();
    Py_InitModule("test", methods);
    return(PyRun_SimpleString("import test\ntest.callback(1)\n") != 0);
}
				], [
				AC_MSG_RESULT([yes])
				], [
				AC_MSG_RESULT([no])
				PYTHON_LIB=""
				PYLIBS=""
				PY_INCLUDE=""
				],
				[
				AC_MSG_RESULT([skipped because cross compiling])
				])
			LIBS="$saved_LIBS"
			CFLAGS="$saved_CFLAGS"
		fi
	fi

	if test "x$PYTHON_LIB" = "x"  ; then
		$2
	else
		$1
	fi

	AC_SUBST(PYTHON_LIB)
	AC_SUBST(PY_LIBS)
	AC_SUBST(PY_INCLUDES)
])
