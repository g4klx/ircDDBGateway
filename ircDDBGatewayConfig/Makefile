OBJECTS = IRCDDBGatewayConfigApp.o IRCDDBGatewayConfigFrame.o IRCDDBGatewayConfigGatewaySet.o IRCDDBGatewayConfigIrcDDBSet.o \
	  IRCDDBGatewayConfigMiscellaneousSet.o

all:		ircddbgatewayconfig

ircddbgatewayconfig:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(LIBS) -o ircddbgatewayconfig

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<

clean:
		$(RM) ircddbgatewayconfig *.o *.d *.bak *~

