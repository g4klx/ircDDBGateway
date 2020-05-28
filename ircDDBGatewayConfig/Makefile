OBJECTS = IRCDDBGatewayConfigApp.o IRCDDBGatewayConfigFrame.o IRCDDBGatewayConfigGatewaySet.o IRCDDBGatewayConfigIrcDDBSet.o \
	  IRCDDBGatewayConfigMiscellaneousSet.o

.PHONY: all
all:		ircddbgatewayconfig

ircddbgatewayconfig:	$(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(GUILIBS) -o ircddbgatewayconfig

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../GUICommon $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 ircddbgatewayconfig $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) ircddbgatewayconfig *.o *.d *.bak *~

../Common/Common.a:
../GUICommon/GUICommon.a:
