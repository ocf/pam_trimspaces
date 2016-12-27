CFLAGS=-std=gnu99 -Wall -Werror -O3

.PHONY: all
all: pam_trimspaces.so

pam_trimspaces.so: pam_trimspaces.c
	$(CC) $(CFLAGS) -fPIC -shared -o "$@" "$<" -lpam

.PHONY: package_%
package_%: dist
	docker run -v $(CURDIR):/mnt:rw docker.ocf.berkeley.edu/theocf/debian:$* /mnt/build-in-docker

dist:
	mkdir -p "$@"

.PHONY: clean
clean:
	rm -f pam_trimspaces.so
