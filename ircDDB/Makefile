OBJECTS = IRCClient.o IRCDDBApp.o IRCDDBClient.o IRCDDB.o IRCDDBMultiClient.o IRCMessage.o IRCMessageQueue.o IRCProtocol.o IRCReceiver.o \
	  IRCutils.o

.PHONY: all
all:		IRCDDB.a

IRCDDB.a:	$(OBJECTS)
		$(AR) rcs IRCDDB.a $(OBJECTS)

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) $< > $*.d

.PHONY: clean
clean:
		$(RM) IRCDDB.a *.o *.d *.bak *~

