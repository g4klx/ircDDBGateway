OBJECTS = StarNetServerApp.o StarNetServerCallsignSet.o StarNetServerConfig.o StarNetServerFrame.o StarNetServerIrcDDBSet.o \
	  StarNetServerLogRedirect.o StarNetServerMiscellaneousSet.o StarNetServerPreferences.o StarNetServerThread.o \
	  StarNetServerThreadHelper.o

all:		starnetserver

starnetserver:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o starnetserver

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -I../ircDDB -c -o $@ $<

install:
		install -g bin -o root -m 0775 starnetserver $(BINDIR)

clean:
		$(RM) starnetserver *.o *.d *.bak *~

