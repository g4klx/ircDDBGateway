OBJECTS = IRCDDBGatewayApp.o IRCDDBGatewayFrame.o IRCDDBGatewayLogRedirect.o IRCDDBGatewayStatusData.o IRCDDBGatewayThread.o \
	  IRCDDBGatewayThreadHelper.o

all:		ircddbgateway

ircddbgateway:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o ircddbgateway

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../ircDDB -c -o $@ $<

clean:
		$(RM) ircddbgateway *.o *.d *.bak *~

