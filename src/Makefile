CC=gcc
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    MYSQL_CONFIG=mysql_config5
    LOCAL_INCLUDE=/opt/local/include
else
    MYSQL_CONFIG=mysql_config
    LOCAL_INCLUDE=/usr/local/include
endif

CFLAGS=-Wall -g -O2 -I${LOCAL_INCLUDE} `${MYSQL_CONFIG} --cflags`
LFLAGS=-Wall -g -O2 -lpng
SRC:=$(shell echo *.c)
OBJ=$(SRC:.c=.o)

all: ouroboros.a remove_bad_chars

ouroboros.a: $(OBJ)
	libtool -o $@ $(OBJ)
	#ar rv $@ $(OBJ)
	#ranlib $@

remove_bad_chars: remove_bad_chars.c
	$(CC) $(CFLAGS) -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -c $<

depend:
	makedepend -- $(CFLAGS) -- $(SRC)

cleanall: clean
	-rm ouroboros.a remove_bad_chars

clean:
	rm -f $(OBJ)

# DO NOT DELETE

annotate_doc.o: /usr/include/stdio.h /usr/include/_types.h
annotate_doc.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
annotate_doc.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
annotate_doc.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
annotate_doc.o: /usr/include/ctype.h /usr/include/runetype.h
annotate_doc.o: /usr/include/string.h /usr/include/secure/_string.h log.h
annotate_doc.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
annotate_doc.o: document_list.h /usr/include/stdlib.h
annotate_doc.o: /usr/include/Availability.h
annotate_doc.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
annotate_doc.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
annotate_doc.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
annotate_doc.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
annotate_doc.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
annotate_doc.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
annotate_doc.o: /usr/include/sys/_endian.h
annotate_doc.o: /usr/include/libkern/_OSByteOrder.h
annotate_doc.o: /usr/include/libkern/i386/_OSByteOrder.h
annotate_doc.o: /usr/include/alloca.h /usr/include/machine/types.h
annotate_doc.o: /usr/include/i386/types.h distance.h word_list.h words.h
annotate_doc.o: file_analysis.h words_list.h int_list.h annotate_doc.h
char_filter.o: /usr/include/stdio.h /usr/include/_types.h
char_filter.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
char_filter.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
char_filter.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
char_filter.o: /usr/include/ctype.h /usr/include/runetype.h char_filter.h
compression.o: /usr/include/stdio.h /usr/include/_types.h
compression.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
compression.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
compression.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
compression.o: /usr/include/stdlib.h /usr/include/Availability.h
compression.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
compression.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
compression.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
compression.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
compression.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
compression.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
compression.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
compression.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
compression.o: /usr/include/machine/types.h /usr/include/i386/types.h
compression.o: /usr/include/string.h /usr/include/secure/_string.h
compression.o: /usr/include/sys/types.h /usr/include/sys/stat.h log.h
compression.o: /usr/include/errno.h /usr/include/sys/errno.h compression.h
compression.o: distance.h
database.o: /usr/include/stdio.h /usr/include/_types.h
database.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
database.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
database.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
database.o: /usr/include/string.h /usr/include/secure/_string.h database.h
database.o: /opt/local/include/mysql5/mysql/mysql.h /usr/include/sys/types.h
database.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
database.o: /usr/include/i386/types.h /usr/include/machine/endian.h
database.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
database.o: /usr/include/libkern/_OSByteOrder.h
database.o: /usr/include/libkern/i386/_OSByteOrder.h
database.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
database.o: /usr/include/i386/_structs.h
database.o: /opt/local/include/mysql5/mysql/mysql_version.h
database.o: /opt/local/include/mysql5/mysql/mysql_com.h
database.o: /opt/local/include/mysql5/mysql/mysql_time.h
database.o: /opt/local/include/mysql5/mysql/my_list.h
database.o: /opt/local/include/mysql5/mysql/typelib.h
database.o: /opt/local/include/mysql5/mysql/my_alloc.h log.h
database.o: /usr/include/errno.h /usr/include/sys/errno.h
distance.o: /usr/include/stdio.h /usr/include/_types.h
distance.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
distance.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
distance.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
distance.o: /usr/include/stdlib.h /usr/include/Availability.h
distance.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
distance.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
distance.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
distance.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
distance.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
distance.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
distance.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
distance.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
distance.o: /usr/include/machine/types.h /usr/include/i386/types.h distance.h
distance.o: log.h /usr/include/string.h /usr/include/secure/_string.h
distance.o: /usr/include/errno.h /usr/include/sys/errno.h
document_list.o: /usr/include/stdio.h /usr/include/_types.h
document_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
document_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
document_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
document_list.o: /usr/include/stdlib.h /usr/include/Availability.h
document_list.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
document_list.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
document_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
document_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
document_list.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
document_list.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
document_list.o: /usr/include/sys/_endian.h
document_list.o: /usr/include/libkern/_OSByteOrder.h
document_list.o: /usr/include/libkern/i386/_OSByteOrder.h
document_list.o: /usr/include/alloca.h /usr/include/machine/types.h
document_list.o: /usr/include/i386/types.h /usr/include/string.h
document_list.o: /usr/include/secure/_string.h /usr/include/ctype.h
document_list.o: /usr/include/runetype.h log.h /usr/include/errno.h
document_list.o: /usr/include/sys/errno.h stream.h document_list.h distance.h
document_list.o: word_list.h words.h
file_analysis.o: /usr/include/stdio.h /usr/include/_types.h
file_analysis.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
file_analysis.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
file_analysis.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
file_analysis.o: /usr/include/string.h /usr/include/secure/_string.h
file_analysis.o: /usr/include/unistd.h /usr/include/sys/unistd.h
file_analysis.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
file_analysis.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
file_analysis.o: /usr/include/i386/_structs.h /usr/include/sys/_select.h
file_analysis.o: /opt/local/include/magic.h /usr/include/sys/types.h
file_analysis.o: /usr/include/machine/types.h /usr/include/i386/types.h
file_analysis.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
file_analysis.o: /usr/include/sys/_endian.h
file_analysis.o: /usr/include/libkern/_OSByteOrder.h
file_analysis.o: /usr/include/libkern/i386/_OSByteOrder.h log.h
file_analysis.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
file_analysis.o: char_filter.h file_analysis.h words_list.h
file_analysis.o: /usr/include/stdlib.h /usr/include/Availability.h
file_analysis.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
file_analysis.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
file_analysis.o: /usr/include/i386/signal.h /usr/include/sys/resource.h
file_analysis.o: /usr/include/alloca.h distance.h word_list.h words.h
file_analysis.o: int_list.h
findonweb.o: /usr/include/stdio.h /usr/include/_types.h
findonweb.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
findonweb.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
findonweb.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
findonweb.o: /usr/include/stdlib.h /usr/include/Availability.h
findonweb.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
findonweb.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
findonweb.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
findonweb.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
findonweb.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
findonweb.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
findonweb.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
findonweb.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
findonweb.o: /usr/include/machine/types.h /usr/include/i386/types.h
findonweb.o: /usr/include/string.h /usr/include/secure/_string.h log.h
findonweb.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
findonweb.o: words_list.h distance.h word_list.h words.h file_analysis.h
findonweb.o: int_list.h substring_matching.h findonweb.h websearch.h
findonweb.o: /usr/include/regex.h
int_list.o: /usr/include/stdio.h /usr/include/_types.h
int_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
int_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
int_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
int_list.o: /usr/include/stdlib.h /usr/include/Availability.h
int_list.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
int_list.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
int_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
int_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
int_list.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
int_list.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
int_list.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
int_list.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
int_list.o: /usr/include/machine/types.h /usr/include/i386/types.h log.h
int_list.o: /usr/include/string.h /usr/include/secure/_string.h
int_list.o: /usr/include/errno.h /usr/include/sys/errno.h int_list.h
log.o: /usr/include/stdio.h /usr/include/_types.h /usr/include/sys/_types.h
log.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
log.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
log.o: /usr/include/secure/_common.h /usr/include/time.h
log.o: /usr/include/_structs.h /usr/include/sys/_structs.h
log.o: /usr/include/machine/_structs.h /usr/include/i386/_structs.h
log.o: /usr/include/sys/appleapiopts.h /usr/include/stdarg.h log.h
log.o: /usr/include/string.h /usr/include/secure/_string.h
log.o: /usr/include/errno.h /usr/include/sys/errno.h
plagiat.o: /usr/include/stdio.h /usr/include/_types.h
plagiat.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
plagiat.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
plagiat.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
plagiat.o: /usr/include/stdlib.h /usr/include/Availability.h
plagiat.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
plagiat.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
plagiat.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
plagiat.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
plagiat.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
plagiat.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
plagiat.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
plagiat.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
plagiat.o: /usr/include/machine/types.h /usr/include/i386/types.h
plagiat.o: /usr/include/string.h /usr/include/secure/_string.h
plagiat.o: /usr/include/unistd.h /usr/include/sys/unistd.h
plagiat.o: /usr/include/sys/select.h /usr/include/sys/_select.h
plagiat.o: /usr/include/sys/types.h /usr/include/sys/stat.h
plagiat.o: /usr/include/dirent.h /usr/include/sys/dirent.h log.h
plagiat.o: /usr/include/errno.h /usr/include/sys/errno.h websearch.h
plagiat.o: /usr/include/regex.h findonweb.h word_list.h document_list.h
plagiat.o: distance.h words.h annotate_doc.h transform.h file_analysis.h
plagiat.o: words_list.h int_list.h plagiat.h
remove_bad_chars.o: /usr/include/stdio.h /usr/include/_types.h
remove_bad_chars.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
remove_bad_chars.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
remove_bad_chars.o: /usr/include/secure/_stdio.h
remove_bad_chars.o: /usr/include/secure/_common.h /usr/include/stdlib.h
remove_bad_chars.o: /usr/include/Availability.h
remove_bad_chars.o: /usr/include/AvailabilityInternal.h
remove_bad_chars.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
remove_bad_chars.o: /usr/include/sys/appleapiopts.h
remove_bad_chars.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
remove_bad_chars.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
remove_bad_chars.o: /usr/include/machine/_structs.h
remove_bad_chars.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
remove_bad_chars.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
remove_bad_chars.o: /usr/include/libkern/_OSByteOrder.h
remove_bad_chars.o: /usr/include/libkern/i386/_OSByteOrder.h
remove_bad_chars.o: /usr/include/alloca.h /usr/include/machine/types.h
remove_bad_chars.o: /usr/include/i386/types.h
report.o: /usr/include/stdio.h /usr/include/_types.h
report.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
report.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
report.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
report.o: /usr/include/stdlib.h /usr/include/Availability.h
report.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
report.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
report.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
report.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
report.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
report.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
report.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
report.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
report.o: /usr/include/machine/types.h /usr/include/i386/types.h
report.o: /opt/local/include/png.h /opt/local/include/zlib.h
report.o: /opt/local/include/zconf.h /usr/include/sys/types.h
report.o: /usr/include/unistd.h /usr/include/sys/unistd.h
report.o: /usr/include/sys/select.h /usr/include/sys/_select.h
report.o: /opt/local/include/pngconf.h /usr/include/limits.h
report.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
report.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
report.o: /usr/include/setjmp.h /usr/include/machine/setjmp.h
report.o: /usr/include/i386/setjmp.h /usr/include/string.h
report.o: /usr/include/secure/_string.h /usr/include/time.h
report.o: /usr/include/_structs.h /usr/include/sys/stat.h database.h
report.o: /opt/local/include/mysql5/mysql/mysql.h
report.o: /opt/local/include/mysql5/mysql/mysql_version.h
report.o: /opt/local/include/mysql5/mysql/mysql_com.h
report.o: /opt/local/include/mysql5/mysql/mysql_time.h
report.o: /opt/local/include/mysql5/mysql/my_list.h
report.o: /opt/local/include/mysql5/mysql/typelib.h
report.o: /opt/local/include/mysql5/mysql/my_alloc.h log.h
report.o: /usr/include/errno.h /usr/include/sys/errno.h file_analysis.h
report.o: words_list.h distance.h word_list.h words.h int_list.h report.h
smith_waterman.o: /usr/include/stdio.h /usr/include/_types.h
smith_waterman.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
smith_waterman.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
smith_waterman.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
smith_waterman.o: /usr/include/string.h /usr/include/secure/_string.h
smith_waterman.o: /usr/include/math.h /usr/include/architecture/i386/math.h
smith_waterman.o: /opt/local/include/png.h /opt/local/include/zlib.h
smith_waterman.o: /opt/local/include/zconf.h /usr/include/sys/types.h
smith_waterman.o: /usr/include/sys/appleapiopts.h
smith_waterman.o: /usr/include/machine/types.h /usr/include/i386/types.h
smith_waterman.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
smith_waterman.o: /usr/include/sys/_endian.h
smith_waterman.o: /usr/include/libkern/_OSByteOrder.h
smith_waterman.o: /usr/include/libkern/i386/_OSByteOrder.h
smith_waterman.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
smith_waterman.o: /usr/include/i386/_structs.h /usr/include/unistd.h
smith_waterman.o: /usr/include/sys/unistd.h /usr/include/sys/select.h
smith_waterman.o: /usr/include/sys/_select.h /opt/local/include/pngconf.h
smith_waterman.o: /usr/include/limits.h /usr/include/machine/limits.h
smith_waterman.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
smith_waterman.o: /usr/include/sys/syslimits.h /usr/include/setjmp.h
smith_waterman.o: /usr/include/machine/setjmp.h /usr/include/i386/setjmp.h
smith_waterman.o: /usr/include/time.h /usr/include/_structs.h word_list.h
smith_waterman.o: /usr/include/stdlib.h /usr/include/Availability.h
smith_waterman.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
smith_waterman.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
smith_waterman.o: /usr/include/i386/signal.h /usr/include/sys/resource.h
smith_waterman.o: /usr/include/alloca.h file_analysis.h words_list.h
smith_waterman.o: distance.h words.h int_list.h stream.h char_filter.h
smith_waterman.o: smith_waterman.h log.h /usr/include/errno.h
smith_waterman.o: /usr/include/sys/errno.h
socket.o: /usr/include/stdio.h /usr/include/_types.h
socket.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
socket.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
socket.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
socket.o: /usr/include/stdlib.h /usr/include/Availability.h
socket.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
socket.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
socket.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
socket.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
socket.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
socket.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
socket.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
socket.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
socket.o: /usr/include/machine/types.h /usr/include/i386/types.h
socket.o: /usr/include/string.h /usr/include/secure/_string.h
socket.o: /usr/include/unistd.h /usr/include/sys/unistd.h
socket.o: /usr/include/sys/select.h /usr/include/sys/_select.h
socket.o: /usr/include/errno.h /usr/include/sys/errno.h
socket.o: /usr/include/sys/types.h /usr/include/sys/socket.h
socket.o: /usr/include/machine/_param.h /usr/include/i386/_param.h
socket.o: /usr/include/netinet/in.h /usr/include/stdint.h
socket.o: /usr/include/netinet6/in6.h /usr/include/netdb.h log.h socket.h
stream.o: /usr/include/stdio.h /usr/include/_types.h
stream.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
stream.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
stream.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
stream.o: /usr/include/stdlib.h /usr/include/Availability.h
stream.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
stream.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
stream.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
stream.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
stream.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
stream.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
stream.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
stream.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
stream.o: /usr/include/machine/types.h /usr/include/i386/types.h
stream.o: /usr/include/string.h /usr/include/secure/_string.h
stream.o: /usr/include/ctype.h /usr/include/runetype.h log.h
stream.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
substring_matching.o: /usr/include/stdio.h /usr/include/_types.h
substring_matching.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
substring_matching.o: /usr/include/machine/_types.h
substring_matching.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
substring_matching.o: /usr/include/secure/_common.h /usr/include/stdlib.h
substring_matching.o: /usr/include/Availability.h
substring_matching.o: /usr/include/AvailabilityInternal.h
substring_matching.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
substring_matching.o: /usr/include/sys/appleapiopts.h
substring_matching.o: /usr/include/machine/signal.h
substring_matching.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
substring_matching.o: /usr/include/sys/_structs.h
substring_matching.o: /usr/include/machine/_structs.h
substring_matching.o: /usr/include/sys/resource.h
substring_matching.o: /usr/include/machine/endian.h
substring_matching.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
substring_matching.o: /usr/include/libkern/_OSByteOrder.h
substring_matching.o: /usr/include/libkern/i386/_OSByteOrder.h
substring_matching.o: /usr/include/alloca.h /usr/include/machine/types.h
substring_matching.o: /usr/include/i386/types.h /usr/include/string.h
substring_matching.o: /usr/include/secure/_string.h /usr/include/ctype.h
substring_matching.o: /usr/include/runetype.h log.h /usr/include/errno.h
substring_matching.o: /usr/include/sys/errno.h char_filter.h words_list.h
substring_matching.o: distance.h word_list.h words.h file_analysis.h
substring_matching.o: int_list.h substring_matching.h
transform.o: /usr/include/stdio.h /usr/include/_types.h
transform.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
transform.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
transform.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
transform.o: /usr/include/stdlib.h /usr/include/Availability.h
transform.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
transform.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
transform.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
transform.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
transform.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
transform.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
transform.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
transform.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
transform.o: /usr/include/machine/types.h /usr/include/i386/types.h
transform.o: /usr/include/string.h /usr/include/secure/_string.h
transform.o: /usr/include/unistd.h /usr/include/sys/unistd.h
transform.o: /usr/include/sys/select.h /usr/include/sys/_select.h
transform.o: /usr/include/sys/types.h /usr/include/sys/stat.h log.h
transform.o: /usr/include/errno.h /usr/include/sys/errno.h char_filter.h
transform.o: stream.h transform.h
websearch.o: /usr/include/stdio.h /usr/include/_types.h
websearch.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
websearch.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
websearch.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
websearch.o: /usr/include/stdlib.h /usr/include/Availability.h
websearch.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
websearch.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
websearch.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
websearch.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
websearch.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
websearch.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
websearch.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
websearch.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
websearch.o: /usr/include/machine/types.h /usr/include/i386/types.h
websearch.o: /usr/include/string.h /usr/include/secure/_string.h
websearch.o: /usr/include/ctype.h /usr/include/runetype.h log.h
websearch.o: /usr/include/errno.h /usr/include/sys/errno.h char_filter.h
websearch.o: socket.h stream.h file_analysis.h words_list.h distance.h
websearch.o: word_list.h words.h int_list.h websearch.h /usr/include/regex.h
word_list.o: /usr/include/stdio.h /usr/include/_types.h
word_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
word_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
word_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
word_list.o: /usr/include/stdlib.h /usr/include/Availability.h
word_list.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
word_list.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
word_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
word_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
word_list.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
word_list.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
word_list.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
word_list.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
word_list.o: /usr/include/machine/types.h /usr/include/i386/types.h
word_list.o: /usr/include/string.h /usr/include/secure/_string.h
word_list.o: /usr/include/ctype.h /usr/include/runetype.h log.h
word_list.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
word_list.o: word_list.h
words.o: /usr/include/stdio.h /usr/include/_types.h /usr/include/sys/_types.h
words.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
words.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
words.o: /usr/include/secure/_common.h /usr/include/stdlib.h
words.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
words.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
words.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
words.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
words.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
words.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
words.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
words.o: /usr/include/libkern/_OSByteOrder.h
words.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
words.o: /usr/include/machine/types.h /usr/include/i386/types.h
words.o: /usr/include/string.h /usr/include/secure/_string.h
words.o: /usr/include/ctype.h /usr/include/runetype.h /usr/include/errno.h
words.o: /usr/include/sys/errno.h log.h stream.h words_list.h distance.h
words.o: word_list.h words.h
words_list.o: /usr/include/stdio.h /usr/include/_types.h
words_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
words_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
words_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
words_list.o: /usr/include/stdlib.h /usr/include/Availability.h
words_list.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
words_list.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
words_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
words_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
words_list.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
words_list.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
words_list.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
words_list.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
words_list.o: /usr/include/machine/types.h /usr/include/i386/types.h
words_list.o: /usr/include/string.h /usr/include/secure/_string.h
words_list.o: /usr/include/ctype.h /usr/include/runetype.h log.h
words_list.o: /usr/include/errno.h /usr/include/sys/errno.h stream.h
words_list.o: words_list.h distance.h word_list.h words.h
