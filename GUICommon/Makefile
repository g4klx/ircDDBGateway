OBJECTS = AddressTextCtrl.o CallsignTextCtrl.o DCSSet.o DescriptionTextCtrl.o DExtraSet.o DPlusSet.o DPRSSet.o PortTextCtrl.o RemoteSet.o \
	  RepeaterDataSet.o RepeaterInfoSet.o RestrictedTextCtrl.o StarNetSet.o XLXSet.o

.PHONY: all
all:		GUICommon.a

GUICommon.a:	$(OBJECTS)
		$(AR) rcs GUICommon.a $(OBJECTS)

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) $(CFLAGS) -I../Common -c -o $@ $<
		$(CXX) -MM $(CFLAGS) -I../Common $< > $*.d

.PHONY: clean
clean:
		$(RM) GUICommon.a *.o *.d *.bak *~

