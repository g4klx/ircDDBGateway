OBJECTS = TimeServerAnnouncementsSet.o TimeServerApp.o TimeServerConfig.o TimeServerFrame.o TimeServerGatewaySet.o TimeServerLogRedirect.o \
	  TimeServerPreferences.o TimeServerThread.o TimeServerThreadHelper.o

all:		timeserver

timeserver:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(LIBS) -o timeserver

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<

clean:
		$(RM) timeserver *.o *.d *.bak *~

