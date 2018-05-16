OBJECTS = TimerControlAppD.o TimerControlConfig.o TimerControlItemFile.o TimerControlRemoteControlHandler.o TimerControlThread.o \
	  TimerControlThreadHelper.o

all:		timercontrold

timercontrold:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../Common/Common.a $(LDFLAGS) $(LIBS) -o timercontrold

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../Common -c -o $@ $<

install:
		install -g bin -o root -m 0775 timercontrold $(BINDIR)

clean:
		$(RM) timercontrold *.o *.d *.bak *~

