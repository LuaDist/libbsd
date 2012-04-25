# Copyright (C) 2012 LuaDist
# Submitted by David Manura.
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.

project ( libbsd C )
cmake_minimum_required ( VERSION 2.6 )
include ( cmake/dist.cmake )

add_definitions (
  -DLIBBSD_OVERLAY -DLIBBSD_DISABLE_DEPRECATED
  -D_GNU_SOURCE -D__REENTRANT
)
include_directories ( include/bsd include )

# custom builders.
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/make_md5.cmake "
  file ( READ ${CMAKE_CURRENT_SOURCE_DIR}/src/hash/helper.c _text )
  string ( REPLACE hashinc bsd/md5.h _text \"\${_text}\" )
  string ( REPLACE HASH MD5 _text \"\${_text}\" )
  file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/md5hl.c \"\${_text}\" )
" )
file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/make_man.cmake "
  file ( READ ${CMAKE_CURRENT_SOURCE_DIR}/src/mdX.3 _text )
  string ( REPLACE mdX md5 _text \"\${_text}\" )
  string ( REPLACE mdY md4 _text \"\${_text}\" )
  string ( REPLACE MDX MD5 _text \"\${_text}\" )
  file ( WRITE ${CMAKE_CURRENT_BINARY_DIR}/md5.3bsd \"\${_text}\" )
" )
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/md5hl.c
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/make_md5.cmake
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/hash/helper.c
)
add_custom_command (
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/md5.3bsd
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/make_man.cmake
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mdX.3
)
add_custom_target ( md5.3bsd_target ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/md5.3bsd )

set ( SRC
  src/arc4random.c
  src/bsd_getopt.c
  src/err.c
  src/fgetln.c
  src/flopen.c
  src/fpurge.c
  src/getpeereid.c
  src/heapsort.c
  src/merge.c
  src/humanize_number.c
  src/dehumanize_number.c
  src/inet_net_pton.c
  src/hash/md5.c
  src/pidfile.c
  src/readpassphrase.c
  src/reallocf.c
  src/setmode.c
  src/setproctitle.c
  src/strmode.c
  src/strtonum.c
  src/strlcat.c
  src/strlcpy.c
  src/fmtcheck.c
  src/nlist.c
  src/progname.c
  src/radixsort.c
  src/vis.c
  src/unvis.c
  ${CMAKE_CURRENT_BINARY_DIR}/md5hl.c
)


set ( INCLUDE_BSD_SYS
  include/bsd/sys/cdefs.h
  include/bsd/sys/bitstring.h
  include/bsd/sys/endian.h
  include/bsd/sys/poll.h
  include/bsd/sys/queue.h
  include/bsd/sys/tree.h )
set ( INCLUDE_BSD_NETINET
  include/bsd/netinet/ip_icmp.h )
set ( INCLUDE_BSD
  include/bsd/cdefs.h
  include/bsd/queue.h
  include/bsd/ip_icmp.h
  include/bsd/err.h
  include/bsd/getopt.h
  include/bsd/inet.h
  include/bsd/random.h
  include/bsd/md5.h
  include/bsd/string.h
  include/bsd/bsd.h
  include/bsd/stdio.h
  include/bsd/stdlib.h
  include/bsd/readpassphrase.h
  include/bsd/unistd.h
  include/bsd/nlist.h
  include/bsd/vis.h
  include/bsd/libutil.h )
set ( INCLUDE
  include/nlist.h
  include/vis.h
  include/libutil.h
)

set ( MAN
  src/arc4random.3
  src/arc4random_addrandom.3
  src/arc4random_buf.3
  src/arc4random_stir.3
  src/arc4random_uniform.3
  src/dehumanize_number.3
  src/strtonum.3
  src/strlcpy.3
  src/strlcat.3
  src/fgetln.3
  src/flopen.3
  src/getpeereid.3
  src/readpassphrase.3
  src/reallocf.3
  src/heapsort.3
  src/humanize_number.3
  src/fmtcheck.3
  src/mergesort.3
  src/radixsort.3
  src/sradixsort.3
  src/nlist.3
  src/pidfile.3
  src/setmode.3
  src/getmode.3
  src/strmode.3
  src/unvis.3
  src/vis.3
  ${CMAKE_CURRENT_BINARY_DIR}/md5.3bsd
)

add_library ( bsd ${SRC} )
install_library ( bsd )
install_header ( ${INCLUDE} )
install_header ( ${INCLUDE_BSD}         INTO bsd )
install_header ( ${INCLUDE_BSD_NETINET} INTO bsd/netinet )
install_header ( ${INCLUDE_BSD_SYS}     INTO bsd/sys )
install_doc ( ${MAN} INTO man )
install_data ( COPYING README TODO Versions )
