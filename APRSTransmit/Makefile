OBJECTS = APRSParser.o APRSTransmitApp.o APRSTransmit.o

all:		aprstransmit

aprstransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o aprstransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 aprstransmit $(BINDIR)

clean:
		$(RM) aprstransmit *.o *.d *.bak *~

