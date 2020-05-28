OBJECTS = StarNetServerAppD.o StarNetServerConfig.o StarNetServerThread.o StarNetServerThreadHelper.o

.PHONY: all
all:		starnetserverd

starnetserverd:	$(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a
		$(CXX) $(OBJECTS) ../Common/Common.a ../ircDDB/IRCDDB.a $(LDFLAGS) $(LIBS) -o starnetserverd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common -I../ircDDB $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 starnetserverd $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) starnetserverd *.o *.d *.bak *~

../Common/Common.a:
../ircDDB/IRCDDB.a:
