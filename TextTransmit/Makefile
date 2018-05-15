OBJECTS = TextTransmit.o

all:		texttransmit

texttransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o texttransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

clean:
		$(RM) texttransmit *.o *.d *.bak *~

