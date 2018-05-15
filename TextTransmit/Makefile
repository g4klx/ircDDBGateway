OBJECTS = TextTransmit.o

all:		texttransmit

texttransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o texttransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 texttransmit $(BINDIR)

clean:
		$(RM) texttransmit *.o *.d *.bak *~

