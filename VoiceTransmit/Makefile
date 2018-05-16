OBJECTS = VoiceStore.o VoiceTransmit.o

all:		voicetransmitd

voicetransmitd:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o voicetransmitd

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 voicetransmitd $(BINDIR)

clean:
		$(RM) voicetransmitd *.o *.d *.bak *~

