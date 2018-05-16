OBJECTS = TimeServerD.o TimeServerConfig.o TimeServerThread.o TimeServerThreadHelper.o

all:		timeserverd

timeserverd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o timeserverd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 timeserverd $(BINDIR)

clean:
		$(RM) timeserverd *.o *.d *.bak *~

