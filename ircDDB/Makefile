OBJECTS = IRCClient.o IRCDDBApp.o IRCDDBClient.o IRCDDB.o IRCDDBMultiClient.o IRCMessage.o IRCMessageQueue.o IRCProtocol.o IRCReceiver.o \
	  IRCutils.o

all:		IRCDDB.a

IRCDDB.a:	$(OBJECTS)
		$(AR) rcs IRCDDB.a $(OBJECTS)

%.o: %.cpp
		$(CXX) $(CFLAGS) -c -o $@ $<

clean:
		$(RM) IRCDDB.a *.o *.d *.bak *~

