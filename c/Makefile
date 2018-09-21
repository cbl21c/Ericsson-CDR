#
# Makefile for Ericsson CDR decoder
#
#
TARGET  = fastdecode

CME20_OBJS = components.o \
	cme20mss16a.o \
	transit.o \
	msoriginating.o \
	roamingcallforwarding.o \
	callforwarding.o \
	msterminating.o \
	msoriginatingsmsinmsc.o \
	msoriginatingsmsinsmsiwmsc.o \
	msterminatingsmsinmsc.o \
	msterminatingsmsinsmsgmsc.o \
	ssprocedure.o \
	aoceventmodule.o \
	ssieventmodule.o \
	serviceswitcheventmodule.o \
	transitinoutgoingcall.o \
	inincomingcall.o \
	inoutgoingcall.o \
	inservicedataeventmodule.o \
	# isdnoriginating.o \
	isdncallforwarding.o \
	isdnssprocedure.o \
	chargeratechangeeventmodule.o \
	scfchargingoutput.o \
	isdnssinvocationeventmodule.o \
	locationservices.o \
	handovereventmodule.o

CME20_C = components.c \
	cme20mss16a.c \
	transit.c \
	msoriginating.c \
	roamingcallforwarding.c \
	callforwarding.c \
	msterminating.c \
	msoriginatingsmsinmsc.c \
	msoriginatingsmsinsmsiwmsc.c \
	msterminatingsmsinmsc.c \
	msterminatingsmsinsmsgmsc.c \
	ssprocedure.c \
	aoceventmodule.c \
	ssieventmodule.c \
	serviceswitcheventmodule.c \
	transitinoutgoingcall.c \
	inincomingcall.c \
	inoutgoingcall.c \
	inservicedataeventmodule.c \
	# isdnoriginating.c \
	isdncallforwarding.c \
	isdnssprocedure.c \
	chargeratechangeeventmodule.c \
	scfchargingoutput.c \
	isdnssinvocationeventmodule.c \
	locationservices.c \
	handovereventmodule.c

CME20_H = components.h \
	cme20mss16a.h \
	transit.h \
	msoriginating.h \
	roamingcallforwarding.h \
	callforwarding.h \
	msterminating.h \
	msoriginatingsmsinmsc.h \
	msoriginatingsmsinsmsiwmsc.h \
	msterminatingsmsinmsc.h \
	msterminatingsmsinsmsgmsc.h \
	ssprocedure.h \
	aoceventmodule.h \
	ssieventmodule.h \
	serviceswitcheventmodule.h \
	transitinoutgoingcall.h \
	inincomingcall.h \
	inoutgoingcall.h \
	inservicedataeventmodule.h \
	# isdnoriginating.h \
	isdncallforwarding.h \
	isdnssprocedure.h \
	chargeratechangeeventmodule.h \
	scfchargingoutput.h \
	isdnssinvocationeventmodule.h \
	locationservices.h \
	handovereventmodule.h

OBJS    = fastdecode.o stack.o $(CME20_OBJS)
SOURCE  = fastdecode.c stack.c stack.h $(CME20_C) $(CME20_H) ingest.c sqlrecord.c sqlrecord.h
          
INGEST_OBJS = ingest.o stack.o sqlrecord.o $(CME20_OBJS)
IIC_OBJS = vmrin.o stack.o sqlrecord.o $(CME20_OBJS)

CC      = /usr/bin/gcc
CFLAGS  = -o fastdecode
LIBDIR  =
LIBS    =
INCLUDE = -I /usr/include /usr/local/include


all:	$(TARGET)

$(TARGET):	$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBDIR) $(LIBS)

ingest:	ingest.o $(INGEST_OBJS)
	$(CC) -o ingest $(INGEST_OBJS) $(LIBDIR) $(LIBS)

vmrin:	vmrin.o $(IIC_OBJS)
	$(CC) -o vmrin $(IIC_OBJS) $(LIBDIR) $(LIBS)

.c.o:
	$(CC) -c $<

clean:
	rm -f $(TARGET) *.o

tar:
	tar -cvf fastdecode.tar $(SOURCE) Makefile


