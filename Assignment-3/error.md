# ERROR

```bash

 bratin  bratin03  ../buildroot-2024.02.6  make
>>> host-gawk 5.3.0 Building
GIT_DIR=. PATH="/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/bin:/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/sbin:/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:/home/bratin/anaconda3/bin:/home/linuxbrew/.linuxbrew/bin:/home/linuxbrew/.linuxbrew/sbin:/home/bratin/anaconda3/bin:/home/bratin/.cargo/bin:/home/bratin/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/bratin/.local/bin:usr/local/lib:/home/bratin/7TH-SEMESTER-CSE/DOCS/A2/Part-2/src/utils:/home/bratin/.local/bin:usr/local/lib:/home/bratin/7TH-SEMESTER-CSE/DOCS/A2/Part-2/src/utils" PKG_CONFIG="/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/bin/pkg-config" PKG_CONFIG_SYSROOT_DIR="/" PKG_CONFIG_ALLOW_SYSTEM_CFLAGS=1 PKG_CONFIG_ALLOW_SYSTEM_LIBS=1 PKG_CONFIG_LIBDIR="/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/lib/pkgconfig:/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/share/pkgconfig"  /usr/bin/make -j9  -C /home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/build/host-gawk-5.3.0/
/usr/bin/make  all-recursive
Making all in support
make[4]: Nothing to be done for 'all'.
Making all in .
Making all in extension
/usr/bin/make  all-recursive
Making all in po
make[6]: Nothing to be done for 'all'.
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o testext.lo testext.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o filefuncs.lo filefuncs.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o gawkfts.lo gawkfts.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o fnmatch.lo fnmatch.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o fork.lo fork.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o inplace.lo inplace.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o intdiv.lo intdiv.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o ordchr.lo ordchr.c
/bin/bash ./libtool  --tag=CC   --mode=compile /usr/bin/gcc -DHAVE_CONFIG_H -I.  -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include  -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c -o readdir.lo readdir.c
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c filefuncs.c  -fPIC -DPIC -o .libs/filefuncs.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c gawkfts.c  -fPIC -DPIC -o .libs/gawkfts.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c intdiv.c  -fPIC -DPIC -o .libs/intdiv.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c testext.c  -fPIC -DPIC -o .libs/testext.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c fnmatch.c  -fPIC -DPIC -o .libs/fnmatch.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c fork.c  -fPIC -DPIC -o .libs/fork.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c inplace.c  -fPIC -DPIC -o .libs/inplace.o
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c readdir.c  -fPIC -DPIC -o .libs/readdir.o
In file included from ./../config.h:600,
                 from filefuncs.c:35:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
In file included from ./../config.h:600,
                 from fnmatch.c:31:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
compilation terminated.
In file included from ./../config.h:600,
                 from gawkfts.c:39:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
In file included from ./../config.h:600,
                 from fork.c:31:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
In file included from ./../config.h:600,
                 from intdiv.c:27:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
make[6]: *** [Makefile:841: filefuncs.lo] Error 1
make[6]: *** Waiting for unfinished jobs....
make[6]: *** [Makefile:841: gawkfts.lo] Error 1
In file included from ./../config.h:600,
                 from inplace.c:27:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
make[6]: *** [Makefile:841: fnmatch.lo] Error 1
make[6]: *** [Makefile:841: fork.lo] Error 1
make[6]: *** [Makefile:841: intdiv.lo] Error 1
make[6]: *** [Makefile:841: inplace.lo] Error 1
libtool: compile:  /usr/bin/gcc -DHAVE_CONFIG_H -I. -I./.. -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -O2 -I/home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/host/include -Wall -DNDEBUG -c ordchr.c  -fPIC -DPIC -o .libs/ordchr.o
In file included from ./../config.h:600,
                 from testext.c:28:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
make[6]: *** [Makefile:841: testext.lo] Error 1
In file included from ./../config.h:600,
                 from readdir.c:36:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
make[6]: *** [Makefile:841: readdir.lo] Error 1
In file included from ./../config.h:600,
                 from ordchr.c:34:
./../custom.h:129:10: fatal error: pma.h: No such file or directory
  129 | #include "pma.h"
      |          ^~~~~~~
compilation terminated.
make[6]: *** [Makefile:841: ordchr.lo] Error 1
make[5]: *** [Makefile:902: all-recursive] Error 1
make[4]: *** [Makefile:656: all] Error 2
make[3]: *** [Makefile:803: all-recursive] Error 1
make[2]: *** [Makefile:583: all] Error 2
make[1]: *** [package/pkg-generic.mk:283: /home/bratin/AOS-LAB/Assignment-3/buildroot-2024.02.6/output/build/host-gawk-5.3.0/.stamp_built] Error 2
make: *** [Makefile:82: _all] Error 2
```