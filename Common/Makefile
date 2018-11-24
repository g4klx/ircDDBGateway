OBJECTS = AMBEData.o AnnouncementUnit.o APRSCollector.o APRSWriter.o APRSWriterThread.o AudioUnit.o CacheManager.o CallsignList.o \
	  CallsignServer.o CCITTChecksum.o CCSData.o CCSHandler.o CCSProtocolHandler.o ConnectData.o DCSHandler.o DCSProtocolHandler.o \
	  DCSProtocolHandlerPool.o DDData.o DDHandler.o DExtraHandler.o DExtraProtocolHandler.o DExtraProtocolHandlerPool.o \
	  DPlusAuthenticator.o DPlusHandler.o DPlusProtocolHandler.o DPlusProtocolHandlerPool.o DRATSServer.o DTMF.o \
	  DummyRepeaterProtocolHandler.o DVTOOLFileReader.o EchoUnit.o G2Handler.o G2ProtocolHandler.o GatewayCache.o \
	  HBRepeaterProtocolHandler.o HeaderData.o HeaderLogger.o HeardData.o HostFile.o IcomRepeaterProtocolHandler.o IRCDDBGatewayConfig.o \
	  LogEvent.o Logger.o NatTraversalHandler.o PollData.o RemoteHandler.o RemoteLinkData.o RemoteProtocolHandler.o RemoteRepeaterData.o RemoteStarNetGroup.o \
	  RemoteStarNetUser.o RepeaterCache.o RepeaterHandler.o SHA256.o SlowDataEncoder.o StarNetHandler.o StatusData.o \
	  TCPReaderWriterClient.o TCPReaderWriterServer.o TextCollector.o TextData.o Timer.o UDPReaderWriter.o UserCache.o Utils.o \
	  VersionUnit.o XLXHostsFileDownloader.o

.PHONY:		all
all:		Common.a

Common.a:	$(OBJECTS) ../ircDDB/IRCDDB.a
		$(AR) rcs Common.a $(OBJECTS)

-include $(OBJECTS:.o=.d)

%.o: %.cpp
		$(CXX) -DwxUSE_GUI=0 $(CFLAGS) -I../ircDDB -c -o $@ $<
		$(CXX) -MM -DwxUSE_GUI=0 $(CFLAGS) -I../ircDDB $< > $*.d

.PHONY: clean
clean:
		$(RM) Common.a *.o *.d *.bak *~

../ircDDB/IRCDDB.a:
