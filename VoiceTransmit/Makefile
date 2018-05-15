OBJECTS = VoiceStore.o VoiceTransmit.o

all:		voicetransmit

voicetransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o voicetransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 voicetransmit $(BINDIR)

clean:
		$(RM) voicetransmit *.o *.d *.bak *~

