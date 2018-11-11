OBJECTS = TimeServerD.o TimeServerConfig.o TimeServerThread.o TimeServerThreadHelper.o

.PHONY: all
all:		timeserverd

timeserverd:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o timeserverd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g bin -o root -m 0775 timeserverd $(BINDIR)

.PHONY: clean
clean:
		$(RM) timeserverd *.o *.d *.bak *~

../Common/Common.a:
