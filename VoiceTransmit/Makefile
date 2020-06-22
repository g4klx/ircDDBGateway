OBJECTS = VoiceStore.o VoiceTransmit.o

.PHONY: all
all:		voicetransmitd

voicetransmitd:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o voicetransmitd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 voicetransmitd $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) voicetransmitd *.o *.d *.bak *~

../Common/Common.a:
