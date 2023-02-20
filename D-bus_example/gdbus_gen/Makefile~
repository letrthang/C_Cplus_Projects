CFLAGS := -fPIC -O3 -g -Wall -Werror
CC := gcc
NAME := example
XMLFILE := blog.letrungthang.Example.Interface.xml

GIO_CFLAGS = -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/   
GIO_LIBS = -pthread -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  

GIO_UNIX_CFLAGS = -pthread -I/usr/include/gio-unix-2.0/ -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/  
GIO_UNIX_LIBS = -pthread -lgio-2.0 -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  

GLIB_CFLAGS = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ 
GLIB_LIBS = -lglib-2.0  

GOBJECT_CFLAGS = -pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ 
GOBJECT_LIBS = -pthread -lgobject-2.0 -lgthread-2.0 -lrt -lglib-2.0  

CFLAGS += $(GIO_CFLAGS)       \
          $(GLIB_CFLAGS)      \
          $(GIO_UNIX_CFLAGS)  \
          $(GOBJECT_CFLAGS)

LIBS = $(GIO_LIBS) \
       $(GIO_UNIX_LIBS) \
       $(GLIB_LIBS) \
       $(GOBJECT_LIBS)

LDFLAGS = -L/usr/local/lib
		  
lib: lib$(NAME).so
	
lib$(NAME).so: $(NAME).o	
	$(CC) $(LDFLAGS) $(LIBS) -shared -Wall $^ -o $@ 
	
clean:	
	$(RM) *.o *.so* *.c *.h

# Create generated sources during the build
$(NAME).c $(NAME).h: $(XMLFILE)
	/usr/bin/gdbus-codegen --interface blog.letrungthang. --c-namespace Thangle --generate-c-code $(NAME) $^

	
