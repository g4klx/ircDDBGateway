OBJECTS = APRSParser.o APRSTransmitAppD.o APRSTransmit.o

.PHONY: all
all:		aprstransmitd

aprstransmitd:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o aprstransmitd

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g root -o root -m 0755 aprstransmitd $(DESTDIR)$(BINDIR)

.PHONY: clean
clean:
		$(RM) aprstransmitd *.o *.d *.bak *~

../Common/Common.a:

