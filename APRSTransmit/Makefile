OBJECTS = APRSParser.o APRSTransmitAppD.o APRSTransmit.o

all:		aprstransmitd

aprstransmitd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o aprstransmitd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 aprstransmitd $(BINDIR)

clean:
		$(RM) aprstransmitd *.o *.d *.bak *~

