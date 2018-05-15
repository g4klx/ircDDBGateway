OBJECTS = VoiceStore.o VoiceTransmit.o

all:		voicetransmit

voicetransmit:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o voicetransmit

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

clean:
		$(RM) voicetransmit *.o *.d *.bak *~

