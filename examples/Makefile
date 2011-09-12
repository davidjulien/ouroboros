CC=gcc
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    MYSQL_CONFIG=mysql_config5
    LOCAL_INCLUDE=/opt/local/include
    LOCAL_LIB=/opt/local/lib
else
    MYSQL_CONFIG=mysql_config
    LOCAL_INCLUDE=/usr/local/include
    LOCAL_LIB=/usr/local/lib
endif

CFLAGS=-Wall -g -O2 -I ../src -I${LOCAL_INCLUDE} `${MYSQL_CONFIG} --cflags`
LFLAGS=-Wall -g -O2 -L${LOCAL_LIB} `${MYSQL_CONFIG} --libs` -lm -lpng -lmagic
SRC:=$(shell echo *.c)
OBJ=$(SRC:.c=.o)
EXEC=test_websearch test_log test_substring_matching test_findonweb test_list test_webget test_words_list test_compare_document test_transform test_ldoc test_file_analysis test_plagiat test_url test_compression test_file_type test_extract_words test_smith_waterman test_sparse_matrix test_report test_database
 
all: $(EXEC)
	cp ../src/remove_bad_chars .

test_build_map: test_build_map.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_extract_words: test_extract_words.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_file_type: test_file_type.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_compression: test_compression.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_url: test_url.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_plagiat: test_plagiat.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_file_analysis: test_file_analysis.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_ldoc: test_ldoc.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_words_list: test_words_list.o  ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_websearch: test_websearch.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_log: test_log.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_substring_matching: test_substring_matching.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_list: test_list.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_findonweb: test_findonweb.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_webget: test_webget.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_compare_document: test_compare_document.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_transform: test_transform.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_smith_waterman: test_smith_waterman.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

test_sparse_matrix: sparse_matrix.o ../src/ouroboros.a 
	$(CC) $(LFLAGS) -o $@ $^

test_report:  test_report.o ../src/ouroboros.a 
	$(CC) $(LFLAGS) -o $@ $^

test_database: test_database.o ../src/ouroboros.a
	$(CC) $(LFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $<

depend:
	makedepend -- $(CFLAGS) -- $(SRC)

cleanall: clean
	rm remove_bad_chars
	rm -f $(EXEC) log

clean:
	rm -f $(OBJ)

# DO NOT DELETE

sparse_matrix.o: /usr/include/stdio.h /usr/include/_types.h
sparse_matrix.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
sparse_matrix.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
sparse_matrix.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
sparse_matrix.o: /usr/include/stdlib.h /usr/include/Availability.h
sparse_matrix.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
sparse_matrix.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
sparse_matrix.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
sparse_matrix.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
sparse_matrix.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
sparse_matrix.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
sparse_matrix.o: /usr/include/sys/_endian.h
sparse_matrix.o: /usr/include/libkern/_OSByteOrder.h
sparse_matrix.o: /usr/include/libkern/i386/_OSByteOrder.h
sparse_matrix.o: /usr/include/alloca.h /usr/include/machine/types.h
sparse_matrix.o: /usr/include/i386/types.h ../src/log.h /usr/include/string.h
sparse_matrix.o: /usr/include/secure/_string.h /usr/include/errno.h
sparse_matrix.o: /usr/include/sys/errno.h sparse_matrix.h
test_compare_document.o: /usr/include/stdio.h /usr/include/_types.h
test_compare_document.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_compare_document.o: /usr/include/machine/_types.h
test_compare_document.o: /usr/include/i386/_types.h
test_compare_document.o: /usr/include/secure/_stdio.h
test_compare_document.o: /usr/include/secure/_common.h ../src/stream.h
test_compare_document.o: ../src/char_filter.h ../src/annotate_doc.h
test_compare_document.o: ../src/document_list.h /usr/include/stdlib.h
test_compare_document.o: /usr/include/Availability.h
test_compare_document.o: /usr/include/AvailabilityInternal.h
test_compare_document.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_compare_document.o: /usr/include/sys/appleapiopts.h
test_compare_document.o: /usr/include/machine/signal.h
test_compare_document.o: /usr/include/i386/signal.h
test_compare_document.o: /usr/include/i386/_structs.h
test_compare_document.o: /usr/include/sys/_structs.h
test_compare_document.o: /usr/include/machine/_structs.h
test_compare_document.o: /usr/include/sys/resource.h
test_compare_document.o: /usr/include/machine/endian.h
test_compare_document.o: /usr/include/i386/endian.h
test_compare_document.o: /usr/include/sys/_endian.h
test_compare_document.o: /usr/include/libkern/_OSByteOrder.h
test_compare_document.o: /usr/include/libkern/i386/_OSByteOrder.h
test_compare_document.o: /usr/include/alloca.h /usr/include/machine/types.h
test_compare_document.o: /usr/include/i386/types.h ../src/distance.h
test_compare_document.o: ../src/word_list.h ../src/words.h
test_compression.o: /usr/include/stdlib.h /usr/include/Availability.h
test_compression.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
test_compression.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_compression.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_compression.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_compression.o: /usr/include/sys/appleapiopts.h
test_compression.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_compression.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_compression.o: /usr/include/machine/_structs.h
test_compression.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
test_compression.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
test_compression.o: /usr/include/libkern/_OSByteOrder.h
test_compression.o: /usr/include/libkern/i386/_OSByteOrder.h
test_compression.o: /usr/include/alloca.h /usr/include/machine/types.h
test_compression.o: /usr/include/i386/types.h /usr/include/string.h
test_compression.o: /usr/include/secure/_string.h
test_compression.o: /usr/include/secure/_common.h ../src/compression.h
test_compression.o: ../src/distance.h ../src/substring_matching.h
test_database.o: ../src/database.h /opt/local/include/mysql5/mysql/mysql.h
test_database.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
test_database.o: /usr/include/sys/cdefs.h /usr/include/machine/types.h
test_database.o: /usr/include/i386/types.h /usr/include/i386/_types.h
test_database.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
test_database.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_database.o: /usr/include/sys/_endian.h
test_database.o: /usr/include/libkern/_OSByteOrder.h
test_database.o: /usr/include/libkern/i386/_OSByteOrder.h
test_database.o: /usr/include/sys/_structs.h /usr/include/machine/_structs.h
test_database.o: /usr/include/i386/_structs.h
test_database.o: /opt/local/include/mysql5/mysql/mysql_version.h
test_database.o: /opt/local/include/mysql5/mysql/mysql_com.h
test_database.o: /opt/local/include/mysql5/mysql/mysql_time.h
test_database.o: /opt/local/include/mysql5/mysql/my_list.h
test_database.o: /opt/local/include/mysql5/mysql/typelib.h
test_database.o: /opt/local/include/mysql5/mysql/my_alloc.h ../src/log.h
test_database.o: /usr/include/string.h /usr/include/_types.h
test_database.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
test_database.o: /usr/include/errno.h /usr/include/sys/errno.h
test_extract_words.o: /usr/include/stdio.h /usr/include/_types.h
test_extract_words.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_extract_words.o: /usr/include/machine/_types.h
test_extract_words.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
test_extract_words.o: /usr/include/secure/_common.h ../src/word_list.h
test_extract_words.o: /usr/include/stdlib.h /usr/include/Availability.h
test_extract_words.o: /usr/include/AvailabilityInternal.h
test_extract_words.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_extract_words.o: /usr/include/sys/appleapiopts.h
test_extract_words.o: /usr/include/machine/signal.h
test_extract_words.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
test_extract_words.o: /usr/include/sys/_structs.h
test_extract_words.o: /usr/include/machine/_structs.h
test_extract_words.o: /usr/include/sys/resource.h
test_extract_words.o: /usr/include/machine/endian.h
test_extract_words.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
test_extract_words.o: /usr/include/libkern/_OSByteOrder.h
test_extract_words.o: /usr/include/libkern/i386/_OSByteOrder.h
test_extract_words.o: /usr/include/alloca.h /usr/include/machine/types.h
test_extract_words.o: /usr/include/i386/types.h ../src/file_analysis.h
test_extract_words.o: ../src/words_list.h ../src/distance.h ../src/words.h
test_extract_words.o: ../src/int_list.h
test_file_analysis.o: /usr/include/stdio.h /usr/include/_types.h
test_file_analysis.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_file_analysis.o: /usr/include/machine/_types.h
test_file_analysis.o: /usr/include/i386/_types.h /usr/include/secure/_stdio.h
test_file_analysis.o: /usr/include/secure/_common.h ../src/word_list.h
test_file_analysis.o: /usr/include/stdlib.h /usr/include/Availability.h
test_file_analysis.o: /usr/include/AvailabilityInternal.h
test_file_analysis.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_file_analysis.o: /usr/include/sys/appleapiopts.h
test_file_analysis.o: /usr/include/machine/signal.h
test_file_analysis.o: /usr/include/i386/signal.h /usr/include/i386/_structs.h
test_file_analysis.o: /usr/include/sys/_structs.h
test_file_analysis.o: /usr/include/machine/_structs.h
test_file_analysis.o: /usr/include/sys/resource.h
test_file_analysis.o: /usr/include/machine/endian.h
test_file_analysis.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
test_file_analysis.o: /usr/include/libkern/_OSByteOrder.h
test_file_analysis.o: /usr/include/libkern/i386/_OSByteOrder.h
test_file_analysis.o: /usr/include/alloca.h /usr/include/machine/types.h
test_file_analysis.o: /usr/include/i386/types.h ../src/file_analysis.h
test_file_analysis.o: ../src/words_list.h ../src/distance.h ../src/words.h
test_file_analysis.o: ../src/int_list.h
test_file_type.o: /usr/include/stdio.h /usr/include/_types.h
test_file_type.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_file_type.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_file_type.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_file_type.o: ../src/word_list.h /usr/include/stdlib.h
test_file_type.o: /usr/include/Availability.h
test_file_type.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_file_type.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_file_type.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_file_type.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_file_type.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_file_type.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_file_type.o: /usr/include/sys/_endian.h
test_file_type.o: /usr/include/libkern/_OSByteOrder.h
test_file_type.o: /usr/include/libkern/i386/_OSByteOrder.h
test_file_type.o: /usr/include/alloca.h /usr/include/machine/types.h
test_file_type.o: /usr/include/i386/types.h ../src/file_analysis.h
test_file_type.o: ../src/words_list.h ../src/distance.h ../src/words.h
test_file_type.o: ../src/int_list.h
test_findonweb.o: /usr/include/stdio.h /usr/include/_types.h
test_findonweb.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_findonweb.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_findonweb.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_findonweb.o: /usr/include/stdlib.h /usr/include/Availability.h
test_findonweb.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_findonweb.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_findonweb.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_findonweb.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_findonweb.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_findonweb.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_findonweb.o: /usr/include/sys/_endian.h
test_findonweb.o: /usr/include/libkern/_OSByteOrder.h
test_findonweb.o: /usr/include/libkern/i386/_OSByteOrder.h
test_findonweb.o: /usr/include/alloca.h /usr/include/machine/types.h
test_findonweb.o: /usr/include/i386/types.h ../src/websearch.h
test_findonweb.o: /usr/include/regex.h ../src/findonweb.h ../src/word_list.h
test_ldoc.o: /usr/include/stdio.h /usr/include/_types.h
test_ldoc.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_ldoc.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_ldoc.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_ldoc.o: /usr/include/stdlib.h /usr/include/Availability.h
test_ldoc.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_ldoc.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_ldoc.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_ldoc.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_ldoc.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_ldoc.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_ldoc.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
test_ldoc.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
test_ldoc.o: /usr/include/machine/types.h /usr/include/i386/types.h
test_ldoc.o: /usr/include/string.h /usr/include/secure/_string.h
test_ldoc.o: ../src/document_list.h ../src/distance.h ../src/word_list.h
test_ldoc.o: ../src/words.h
test_list.o: /usr/include/stdio.h /usr/include/_types.h
test_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_list.o: /usr/include/string.h /usr/include/secure/_string.h ../src/log.h
test_list.o: /usr/include/errno.h /usr/include/sys/errno.h ../src/word_list.h
test_list.o: /usr/include/stdlib.h /usr/include/Availability.h
test_list.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_list.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_list.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_list.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_list.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
test_list.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
test_list.o: /usr/include/machine/types.h /usr/include/i386/types.h
test_list.o: ../src/substring_matching.h ../src/distance.h
test_log.o: ../src/log.h /usr/include/string.h /usr/include/_types.h
test_log.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_log.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_log.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
test_log.o: /usr/include/errno.h /usr/include/sys/errno.h
test_plagiat.o: /usr/include/stdio.h /usr/include/_types.h
test_plagiat.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_plagiat.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_plagiat.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_plagiat.o: ../src/plagiat.h ../src/websearch.h /usr/include/regex.h
test_report.o: ../src/log.h /usr/include/string.h /usr/include/_types.h
test_report.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_report.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_report.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
test_report.o: /usr/include/errno.h /usr/include/sys/errno.h
test_report.o: /usr/include/stdlib.h /usr/include/Availability.h
test_report.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_report.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_report.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_report.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_report.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_report.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_report.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
test_report.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
test_report.o: /usr/include/machine/types.h /usr/include/i386/types.h
test_report.o: ../src/report.h ../src/word_list.h ../src/database.h
test_report.o: /opt/local/include/mysql5/mysql/mysql.h
test_report.o: /usr/include/sys/types.h
test_report.o: /opt/local/include/mysql5/mysql/mysql_version.h
test_report.o: /opt/local/include/mysql5/mysql/mysql_com.h
test_report.o: /opt/local/include/mysql5/mysql/mysql_time.h
test_report.o: /opt/local/include/mysql5/mysql/my_list.h
test_report.o: /opt/local/include/mysql5/mysql/typelib.h
test_report.o: /opt/local/include/mysql5/mysql/my_alloc.h
test_smith_waterman.o: /usr/include/stdio.h /usr/include/_types.h
test_smith_waterman.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_smith_waterman.o: /usr/include/machine/_types.h
test_smith_waterman.o: /usr/include/i386/_types.h
test_smith_waterman.o: /usr/include/secure/_stdio.h
test_smith_waterman.o: /usr/include/secure/_common.h /usr/include/string.h
test_smith_waterman.o: /usr/include/secure/_string.h /usr/include/math.h
test_smith_waterman.o: /usr/include/architecture/i386/math.h
test_smith_waterman.o: ../src/word_list.h /usr/include/stdlib.h
test_smith_waterman.o: /usr/include/Availability.h
test_smith_waterman.o: /usr/include/AvailabilityInternal.h
test_smith_waterman.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_smith_waterman.o: /usr/include/sys/appleapiopts.h
test_smith_waterman.o: /usr/include/machine/signal.h
test_smith_waterman.o: /usr/include/i386/signal.h
test_smith_waterman.o: /usr/include/i386/_structs.h
test_smith_waterman.o: /usr/include/sys/_structs.h
test_smith_waterman.o: /usr/include/machine/_structs.h
test_smith_waterman.o: /usr/include/sys/resource.h
test_smith_waterman.o: /usr/include/machine/endian.h
test_smith_waterman.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
test_smith_waterman.o: /usr/include/libkern/_OSByteOrder.h
test_smith_waterman.o: /usr/include/libkern/i386/_OSByteOrder.h
test_smith_waterman.o: /usr/include/alloca.h /usr/include/machine/types.h
test_smith_waterman.o: /usr/include/i386/types.h ../src/file_analysis.h
test_smith_waterman.o: ../src/words_list.h ../src/distance.h ../src/words.h
test_smith_waterman.o: ../src/int_list.h ../src/stream.h ../src/char_filter.h
test_smith_waterman.o: ../src/smith_waterman.h ../src/log.h
test_smith_waterman.o: /usr/include/errno.h /usr/include/sys/errno.h
test_substring_matching.o: /usr/include/stdio.h /usr/include/_types.h
test_substring_matching.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_substring_matching.o: /usr/include/machine/_types.h
test_substring_matching.o: /usr/include/i386/_types.h
test_substring_matching.o: /usr/include/secure/_stdio.h
test_substring_matching.o: /usr/include/secure/_common.h
test_substring_matching.o: ../src/substring_matching.h /usr/include/stdlib.h
test_substring_matching.o: /usr/include/Availability.h
test_substring_matching.o: /usr/include/AvailabilityInternal.h
test_substring_matching.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_substring_matching.o: /usr/include/sys/appleapiopts.h
test_substring_matching.o: /usr/include/machine/signal.h
test_substring_matching.o: /usr/include/i386/signal.h
test_substring_matching.o: /usr/include/i386/_structs.h
test_substring_matching.o: /usr/include/sys/_structs.h
test_substring_matching.o: /usr/include/machine/_structs.h
test_substring_matching.o: /usr/include/sys/resource.h
test_substring_matching.o: /usr/include/machine/endian.h
test_substring_matching.o: /usr/include/i386/endian.h
test_substring_matching.o: /usr/include/sys/_endian.h
test_substring_matching.o: /usr/include/libkern/_OSByteOrder.h
test_substring_matching.o: /usr/include/libkern/i386/_OSByteOrder.h
test_substring_matching.o: /usr/include/alloca.h /usr/include/machine/types.h
test_substring_matching.o: /usr/include/i386/types.h ../src/distance.h
test_transform.o: /usr/include/stdio.h /usr/include/_types.h
test_transform.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_transform.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_transform.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_transform.o: /usr/include/string.h /usr/include/secure/_string.h
test_transform.o: ../src/transform.h
test_url.o: /usr/include/stdio.h /usr/include/_types.h
test_url.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_url.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_url.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_url.o: ../src/websearch.h /usr/include/regex.h
test_webget.o: /usr/include/stdio.h /usr/include/_types.h
test_webget.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_webget.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_webget.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_webget.o: /usr/include/stdlib.h /usr/include/Availability.h
test_webget.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_webget.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_webget.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_webget.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_webget.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_webget.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_webget.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
test_webget.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
test_webget.o: /usr/include/machine/types.h /usr/include/i386/types.h
test_webget.o: /usr/include/string.h /usr/include/secure/_string.h
test_webget.o: ../src/websearch.h /usr/include/regex.h
test_websearch.o: /usr/include/stdio.h /usr/include/_types.h
test_websearch.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_websearch.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_websearch.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_websearch.o: /usr/include/stdlib.h /usr/include/Availability.h
test_websearch.o: /usr/include/AvailabilityInternal.h /usr/include/sys/wait.h
test_websearch.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
test_websearch.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_websearch.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_websearch.o: /usr/include/machine/_structs.h /usr/include/sys/resource.h
test_websearch.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
test_websearch.o: /usr/include/sys/_endian.h
test_websearch.o: /usr/include/libkern/_OSByteOrder.h
test_websearch.o: /usr/include/libkern/i386/_OSByteOrder.h
test_websearch.o: /usr/include/alloca.h /usr/include/machine/types.h
test_websearch.o: /usr/include/i386/types.h ../src/websearch.h
test_websearch.o: /usr/include/regex.h
test_words_list.o: /usr/include/stdio.h /usr/include/_types.h
test_words_list.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
test_words_list.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
test_words_list.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
test_words_list.o: /usr/include/stdlib.h /usr/include/Availability.h
test_words_list.o: /usr/include/AvailabilityInternal.h
test_words_list.o: /usr/include/sys/wait.h /usr/include/sys/signal.h
test_words_list.o: /usr/include/sys/appleapiopts.h
test_words_list.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
test_words_list.o: /usr/include/i386/_structs.h /usr/include/sys/_structs.h
test_words_list.o: /usr/include/machine/_structs.h
test_words_list.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
test_words_list.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
test_words_list.o: /usr/include/libkern/_OSByteOrder.h
test_words_list.o: /usr/include/libkern/i386/_OSByteOrder.h
test_words_list.o: /usr/include/alloca.h /usr/include/machine/types.h
test_words_list.o: /usr/include/i386/types.h /usr/include/string.h
test_words_list.o: /usr/include/secure/_string.h ../src/words_list.h
test_words_list.o: ../src/distance.h ../src/word_list.h ../src/words.h
