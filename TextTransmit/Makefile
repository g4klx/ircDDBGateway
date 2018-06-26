OBJECTS = TextTransmit.o

all:		texttransmitd

texttransmitd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o texttransmitd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 texttransmitd $(BINDIR)

clean:
		$(RM) texttransmitd *.o *.d *.bak *~

