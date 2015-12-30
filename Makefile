CFLAGS += -Wall -Wextra -O2 -g -pipe
LDLIBS += -lms

MV := mv
RM := rm -f

ms5.cgi: ms5-cgi
	$(MV) "$<" "$@"

.PHONY: clean
clean:
	$(RM) ms5.cgi
	$(RM) ms5-cgi
	$(RM) ms5-cgi.o
