OBJECTS = AddressTextCtrl.o CallsignTextCtrl.o DCSSet.o DescriptionTextCtrl.o DExtraSet.o DPlusSet.o DPRSSet.o MobileGPSSet.o PortTextCtrl.o RemoteSet.o \
	  RepeaterDataSet.o RepeaterInfoSet.o RestrictedTextCtrl.o StarNetSet.o XLXSet.o

all:		GUICommon.a

GUICommon.a:	$(OBJECTS)
		$(AR) rcs GUICommon.a $(OBJECTS)

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<

clean:
		$(RM) GUICommon.a *.o *.d *.bak *~

