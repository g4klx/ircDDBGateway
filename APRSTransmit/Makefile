OBJECTS = APRSParser.o APRSTransmitApp.o APRSTransmit.o

all:		aprstransmit

aprstransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o aprstransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

clean:
		$(RM) aprstransmit *.o *.d *.bak *~

