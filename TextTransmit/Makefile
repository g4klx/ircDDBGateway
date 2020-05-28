OBJECTS = TextTransmit.o

.PHONY: all
all:		texttransmitd

texttransmitd:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o texttransmitd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 texttransmitd $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) texttransmitd *.o *.d *.bak *~

../Common/Common.a:
