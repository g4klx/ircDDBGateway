OBJECTS = IRCDDBGatewayConfigApp.o IRCDDBGatewayConfigFrame.o IRCDDBGatewayConfigGatewaySet.o IRCDDBGatewayConfigIrcDDBSet.o \
	  IRCDDBGatewayConfigMiscellaneousSet.o

all:		ircddbgatewayconfig

ircddbgatewayconfig:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(LIBS) -o ircddbgatewayconfig

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<

install:
		install -g bin -o root -m 0775 ircddbgatewayconfig $(BINDIR)

clean:
		$(RM) ircddbgatewayconfig *.o *.d *.bak *~

