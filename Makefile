jdn: jdn.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

.PHONY: clean
clean:
	rm -f jdn
