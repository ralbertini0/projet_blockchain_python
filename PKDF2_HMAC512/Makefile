CPPFLAGS += -I /usr/include/python3.8
LIBS= ../lib/* -lpython3.8 
COMPOSANT = PKDF2_HMAC512

CPPFLAGS += -I../membre

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

DESTINATION_LIBSO=../tests/${LIBSO}

all: ${DESTINATION_LIBSO}

include ../gcc.mk
include ../pybind11.mk


	
clean:
	rm -f ${LIBSO}  ${LIBSO_OBJS} ${DESTINATION_LIBSO}


${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@

