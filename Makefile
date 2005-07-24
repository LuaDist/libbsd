
LIB_FILES = arc4random.c  fgetln.c  inet_net_pton.c  md5c.c \
  strlcat.c  strlcpy.c

# All source files have associated object files
LIBOFILES		= $(LIB_FILES:%.c=%.o)       

CFLAGS = -include bsd.h -D_GNU_SOURCE

# all is the default rule
all	: libbsd.a \
	  libbsd.so.1

insstall :
	  mkdir -p $(DESTDIR)/usr/lib/
	  mkdir -p $(DESTDIR)/usr/include/
	  install -m644 libbsd.a $(DESTDIR)/usr/lib/
	  install -m644 libbsd.so.1 $(DESTDIR)/usr/lib/
	  install -m644 bsd.h $(DESTDIR)/usr/include/
	  cd $(DESTDIR)/usr/lib/ ; ln -s libbsd.so.1 libbsd.so 
 
clean	:
	rm -f *.o
	rm -f *.a
	rm -f *.so.1

# remove the old tapestry library and remake the new one
libbsd.a:	$(LIBOFILES)
	rm -f $@
	ar cq $@ $(LIBOFILES)

libbsd.so.1:	$(LIBOFILES)
	rm -f $@
	ld -G -o $@ $(LIBOFILES)
