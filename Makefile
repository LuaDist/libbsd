#
# libbsd
#
# $Id$
#

LIB_SRCS = arc4random.c fgetln.c inet_net_pton.c strlcat.c strlcpy.c md5c.c fmtcheck.c

LIB_INCLUDES = bsd.h md5.h

LIB_STATIC_OBJS = $(LIB_SRCS:%.c=%.o)
LIB_SHARED_OBJS = $(LIB_SRCS:%.c=%.lo)

LIB_NAME = libbsd
LIB_VERSION_MAJOR = 0
LIB_VERSION_MINOR = 0

LIB_STATIC = $(LIB_NAME).a

LIB_SHARED_SO = $(LIB_NAME).so
LIB_SONAME = $(LIB_SHARED_SO).$(LIB_VERSION_MAJOR)
LIB_SHARED = $(LIB_SONAME).$(LIB_VERSION_MINOR)

MK_CFLAGS = -Iinclude/ -include bsd/bsd.h -D_GNU_SOURCE

libs: $(LIB_STATIC) $(LIB_SHARED_SO)

%.lo: %.c
	$(CC) -o $@ $(MK_CFLAGS) $(CFLAGS) -DPIC -fPIC -c $<

%.o: %.c
	$(CC) -o $@ $(MK_CFLAGS) $(CFLAGS) -c $<

$(LIB_STATIC): $(LIB_STATIC_OBJS)
	ar rcs $@ $^

$(LIB_SHARED_SO): $(LIB_SONAME)
	ln -fs $^ $@

$(LIB_SONAME): $(LIB_SHARED)
	ln -fs $^ $@

$(LIB_SHARED): $(LIB_SHARED_OBJS)
	gcc -shared \
	  -Wl,-soname -Wl,$(LIB_SONAME) \
	  -Wl,--version-script=Versions \
	  -o $@ $^

install: libs
	mkdir -p $(DESTDIR)/usr/lib/
	mkdir -p $(DESTDIR)/usr/include/bsd/
	install -m644 $(LIB_STATIC) $(DESTDIR)/usr/lib/
	#install -m644 $(LIB_SONAME) $(DESTDIR)/usr/lib/
	install -m644 $(LIB_SHARED) $(DESTDIR)/usr/lib/
	#install -m644 $(LIB_SHARED_SO) $(DESTDIR)/usr/lib/
	install -m644 $(LIB_INCLUDES) $(DESTDIR)/usr/include/bsd/
	cd $(DESTDIR)/usr/lib/ ; ln -fs $(LIB_SHARED) $(LIB_SHARED_SO)
	cd $(DESTDIR)/usr/lib/ ; ln -fs $(LIB_SHARED) $(LIB_SONAME)

clean:
	rm -f $(LIB_STATIC_OBJS)
	rm -f $(LIB_STATIC)
	rm -f $(LIB_SHARED_OBJS)
	rm -f $(LIB_SHARED) $(LIB_SONAME) $(LIB_SHARED_SO)

