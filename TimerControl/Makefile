OBJECTS = TimerControlApp.o TimerControlConfig.o TimerControlFrame.o TimerControlItemFile.o TimerControlPreferences.o \
	  TimerControlRemoteControlHandler.o TimerControlRemoteSet.o TimerControlRepeaterPanel.o TimerControlThread.o TimerControlThreadHelper.o

all:		timercontrol

timercontrol:	$(OBJECTS)
		$(CXX) $(OBJECTS) ../GUICommon/GUICommon.a ../Common/Common.a $(LDFLAGS) $(LIBS) -o timercontrol

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -I../GUICommon -c -o $@ $<

clean:
		$(RM) timercontrol *.o *.d *.bak *~

