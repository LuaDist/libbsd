VERSION := $(shell ./get-version)

LIB_NAME := libbsd
LIB_VERSION_MAJOR := 0
LIB_VERSION_MINOR := 2
LIB_VERSION_MICRO := 0
LIB_VERSION := $(LIB_VERSION_MAJOR).$(LIB_VERSION_MINOR).$(LIB_VERSION_MICRO)

LIB_PKGCONFIG := $(LIB_NAME).pc
LIB_PKGCONFIG_OVERLAY := $(LIB_NAME)-overlay.pc
LIB_STATIC := $(LIB_NAME).a
LIB_SHARED_SO := $(LIB_NAME).so
LIB_SONAME := $(LIB_SHARED_SO).$(LIB_VERSION_MAJOR)
LIB_SHARED := $(LIB_SONAME).$(LIB_VERSION_MINOR).$(LIB_VERSION_MICRO)

TAR_NAME := $(LIB_NAME)-$(VERSION)
TAR_FILE := $(TAR_NAME).tar.gz

LIB_DIST := \
	ChangeLog

LIB_SRCS_GEN := \
	hash/md5hl.c
LIB_SRCS := \
	arc4random.c \
	bsd_getopt.c \
	err.c \
	fgetln.c \
	flopen.c \
	fpurge.c \
	getpeereid.c \
	heapsort.c \
	merge.c \
	humanize_number.c \
	dehumanize_number.c \
	inet_net_pton.c \
	hash/md5.c \
	pidfile.c \
	readpassphrase.c \
	reallocf.c \
	setmode.c \
	setproctitle.c \
	strmode.c \
	strtonum.c \
	strlcat.c strlcpy.c \
	fmtcheck.c \
	nlist.c \
	progname.c \
	radixsort.c \
	vis.c unvis.c \
	$(LIB_SRCS_GEN)
LIB_SRCS_GEN := $(patsubst %,src/%,$(LIB_SRCS_GEN))
LIB_SRCS := $(patsubst %,src/%,$(LIB_SRCS))

LIB_INCLUDES := \
	bsd/cdefs.h \
	bsd/queue.h \
	bsd/ip_icmp.h \
	bsd/sys/cdefs.h \
	bsd/sys/bitstring.h \
	bsd/sys/endian.h \
	bsd/sys/poll.h \
	bsd/sys/queue.h \
	bsd/sys/tree.h \
	bsd/netinet/ip_icmp.h \
	bsd/err.h \
	bsd/getopt.h \
	bsd/inet.h \
	bsd/random.h \
	bsd/md5.h \
	bsd/string.h \
	bsd/bsd.h \
	bsd/stdio.h \
	bsd/stdlib.h \
	bsd/readpassphrase.h \
	bsd/unistd.h \
	bsd/nlist.h \
	bsd/vis.h \
	bsd/libutil.h \
	nlist.h \
	vis.h \
	libutil.h

LIB_MANS_GEN := \
	md5.3bsd
LIB_MANS := \
	arc4random.3 \
	arc4random_addrandom.3 \
	arc4random_buf.3 \
	arc4random_stir.3 \
	arc4random_uniform.3 \
	dehumanize_number.3 \
	strtonum.3 \
	strlcpy.3 \
	strlcat.3 \
	fgetln.3 \
	flopen.3 \
	getpeereid.3 \
	readpassphrase.3 \
	reallocf.3 \
	heapsort.3 \
	humanize_number.3 \
	fmtcheck.3 \
	mergesort.3 \
	radixsort.3 \
	sradixsort.3 \
	nlist.3 \
	pidfile.3 \
	setmode.3 \
	getmode.3 \
	strmode.3 \
	unvis.3 \
	vis.3 \
	$(LIB_MANS_GEN)
LIB_MANS_GEN := $(patsubst %,src/%,$(LIB_MANS_GEN))
LIB_MANS := $(patsubst %,src/%,$(LIB_MANS))

LIB_STATIC_OBJS := $(LIB_SRCS:%.c=%.o)
LIB_SHARED_OBJS := $(LIB_SRCS:%.c=%.lo)

AR = ar
CC = gcc
CCLD = $(CC)

# Set default values for user variables
CPPFLAGS ?=
CFLAGS ?= -g -Wall -Wextra -Wno-unused-variable
LDFLAGS ?=

# Internal makefile variables
MK_CPPFLAGS := -Iinclude/bsd/ -Iinclude/ \
	-DLIBBSD_OVERLAY -DLIBBSD_DISABLE_DEPRECATED \
	-D_GNU_SOURCE -D__REENTRANT
MK_CFLAGS :=
MK_LDFLAGS :=

COMPILE = $(CC) $(MK_CPPFLAGS) $(CPPFLAGS) $(MK_CFLAGS) $(CFLAGS)
LINK = $(CCLD) $(MK_CFLAGS) $(CFLAGS) $(MK_LDFLAGS) $(LDFLAGS)

prefix		= /usr
exec_prefix	=
libdir		= ${exec_prefix}/lib
usrlibdir	= ${prefix}/lib
includedir	= ${prefix}/include
pkgconfigdir	= ${usrlibdir}/pkgconfig
mandir		= ${prefix}/share/man

.PHONY: libs
libs: $(LIB_STATIC) $(LIB_SHARED_SO) $(LIB_PKGCONFIG) $(LIB_PKGCONFIG_OVERLAY)

.PHONY: man
man: $(LIB_MANS)

%.lo: %.c
	$(COMPILE) -o $@ -DPIC -fPIC -c $<

%.o: %.c
	$(COMPILE) -o $@ -c $<

src/md5.3bsd:  src/mdX.3
	sed -e 's/mdX/md5/g' -e 's/mdY/md4/g' -e 's/MDX/MD5/g' $< > $@

src/hash/md5hl.c: src/hash/helper.c
	sed -e 's:hashinc:bsd/md5.h:g' -e 's:HASH:MD5:g' $< > $@

%.pc: %.pc.in
	sed -e 's:@VERSION@:$(VERSION):' \
	    -e 's:@prefix@:$(value prefix):' \
	    -e 's:@exec_prefix@:$(value exec_prefix):' \
	    -e 's:@libdir@:$(value usrlibdir):' \
	    -e 's:@includedir@:$(value includedir):' \
	    $< > $@

$(LIB_STATIC): $(LIB_STATIC_OBJS)
	$(AR) rcs $@ $^

$(LIB_SHARED_SO): $(LIB_SONAME)
	ln -fs $^ $@

$(LIB_SONAME): $(LIB_SHARED)
	ln -fs $^ $@

$(LIB_SHARED): $(LIB_SHARED_OBJS)
	$(LINK) \
	  -shared \
	  -Wl,-soname -Wl,$(LIB_SONAME) \
	  -Wl,--version-script=Versions \
	  -o $@ $^

.PHONY: ChangeLog
ChangeLog:
	-git log --stat -C >$@

.PHONY: dist
dist: $(LIB_DIST)
	mkdir $(TAR_NAME)
	echo $(VERSION) >$(TAR_NAME)/.dist-version
	cp -a --parents $(LIB_DIST) `git ls-files` $(TAR_NAME)
	tar czf $(TAR_FILE) --exclude=.gitignore $(TAR_NAME)
	rm -rf $(TAR_NAME)
	gpg -a -b $(TAR_FILE)

.PHONY: install
install: libs man
	mkdir -p $(DESTDIR)$(libdir)
	mkdir -p $(DESTDIR)$(usrlibdir)
	mkdir -p $(DESTDIR)$(includedir)/bsd/
	mkdir -p $(DESTDIR)$(includedir)/bsd/sys/
	mkdir -p $(DESTDIR)$(includedir)/bsd/netinet/
	mkdir -p $(DESTDIR)$(mandir)/man3
	mkdir -p $(DESTDIR)$(pkgconfigdir)
	install -m644 $(LIB_STATIC) $(DESTDIR)$(usrlibdir)
	install -m755 $(LIB_SHARED) $(DESTDIR)$(libdir)
	for i in $(LIB_INCLUDES); do \
	  install -m644 include/$$i $(DESTDIR)$(includedir)/$$i; \
	done
	install -m644 $(LIB_MANS) $(DESTDIR)$(mandir)/man3
	install -m644 $(LIB_PKGCONFIG) $(DESTDIR)$(pkgconfigdir)
	install -m644 $(LIB_PKGCONFIG_OVERLAY) $(DESTDIR)$(pkgconfigdir)
ifeq ($(libdir),$(usrlibdir))
	# If both dirs are the same, do a relative symlink.
	ln -sf $(LIB_SHARED) $(DESTDIR)$(usrlibdir)/$(LIB_SHARED_SO)
else
	# Otherwise, do an absolute one.
	ln -sf $(libdir)/$(LIB_SHARED) $(DESTDIR)$(usrlibdir)/$(LIB_SHARED_SO)
endif
	ln -sf $(LIB_SHARED) $(DESTDIR)$(libdir)/$(LIB_SONAME)

.PHONY: clean
clean:
	rm -f $(LIB_PKGCONFIG)
	rm -f $(LIB_PKGCONFIG_OVERLAY)
	rm -f $(LIB_SRCS_GEN) $(LIB_MANS_GEN)
	rm -f $(LIB_STATIC_OBJS)
	rm -f $(LIB_STATIC)
	rm -f $(LIB_SHARED_OBJS)
	rm -f $(LIB_SHARED) $(LIB_SONAME) $(LIB_SHARED_SO)
