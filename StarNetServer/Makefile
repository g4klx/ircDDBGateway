OBJECTS = StarNetServerAppD.o StarNetServerConfig.o StarNetServerThread.o StarNetServerThreadHelper.o

all:		starnetserverd

starnetserverd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o starnetserverd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB -c -o $@ $<

install:
		install -g bin -o root -m 0775 starnetserverd $(BINDIR)

clean:
		$(RM) starnetserverd *.o *.d *.bak *~

