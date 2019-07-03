OBJECTS = TimerControlAppD.o TimerControlConfig.o TimerControlItemFile.o TimerControlRemoteControlHandler.o TimerControlThread.o \
	  TimerControlThreadHelper.o

.PHONY: all
all:		timercontrold

timercontrold:	$(OBJECTS) ../Common/Common.a
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o timercontrold

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../Common $< > $*.d

.PHONY: install
install:
		install -g bin -o root -m 0775 timercontrold $(BINDIR)

.PHONY: clean
clean:
		$(RM) timercontrold *.o *.d *.bak *~

../Common/Common.a:

