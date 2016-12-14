#!/usr/bin/python

#
# Ericsson CME20 MSS14b CDR data types
#

componentHash = {}
componentHash['root'] = ['uMTSGSMPLMNCallDataRecord', 'compositeCallDataRecord']

componentHash['compositeCallDataRecord'] = ['uMTSGSMPLMNCallDataRecord']
componentHash['uMTSGSMPLMNCallDataRecord'] = [
    'transit',
    'mSOriginating',
    'roamingCallForwarding',
    'callForwarding',
    'mSTerminating',
    'mSOriginatingSMSinMSC',
    'mSOriginatingSMSinSMS_IWMSC',
    'mSTerminatingSMSinMSC',
    'mSTerminatingSMSinSMS_GMSC',
    'sSProcedure',
    'aoCEventModule',
    'sSInvocationEventModule',
    'serviceSwitchEventModule',
    'transitINOutgoingCall',
    'iNIncomingCall',
    'iNOutgoingCall',
    'iNServiceDataEventModule',
    'iSDNOriginating',
    'iSDNCallForwarding',
    'iSDNSSProcedure',
    'chargeRateChangeEventModule',
    'sCFChargingOutput',
    None,    # no component with tag value 22
    'iSDNSSInvocationEventModule',
    'locationServices',
    'handOverEventModule',
]

################################################################################
# Call Modules                                                                 #
################################################################################

##############################
# transit                    #
##############################
componentHash['transit'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'calledPartyNumber',
    'calledSubscriberIMSI',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'timeFromRegisterSeizureToStartOfCharging',
    'chargedParty',
    'originForCharging',
    'tariffClass',
    'tariffSwitchInd',
    'numberOfMeterPulses',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'incomingRoute',
    'miscellaneousInformation',
    'originatedCode',
    'iNMarkingOfMS',
    'callPosition',
    'eosInfo',
    'internalCauseAndLoc',
    'originalCalledNumber',
    'redirectingNumber',
    'redirectionCounter',
    'redirectingDropBackNumber',
    'redirectingDropBack',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'iCIOrdered',
    'outputForSubscriber',
    'lastPartialOutput',
    'partialOutputRecNum',
    'relatedCallNumber',
    'faultCode',
    'subscriptionType',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'switchIdentity',
    'networkCallReference',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'translatedNumber',
    'bCSMTDPData1',
    'bCSMTDPData2',
    'bCSMTDPData3',
    'bCSMTDPData4',
    'bCSMTDPData5',
    'bCSMTDPData6',
    'bCSMTDPData7',
    'bCSMTDPData8',
    'bCSMTDPData9',
    'bCSMTDPData10',
    'gSMCallReferenceNumber',
    'c7ChargingMessage',
    'c7FirstCHTMessage',
    'c7SecondCHTMessage',
    'aCMChargingIndicator',
    'aNMChargingIndicator',
    'mSCAddress',
    'carrierInformationBackward',
    'carrierInformationForward',
    'chargeInformation',
    'disconnectionDate',
    'disconnectionTime',
    'entryPOICA',
    'exitPOICA',
    'internationalCallIndicator',
    'mobileUserClass1',
    'mobileUserClass2',
    'originatingAccessISDN',
    'originatingCarrier',
    'originatingChargeArea',
    'tDSCounter',
    'terminatingAccessISDN',
    'terminatingCarrier',
    'terminatingChargeArea',
    'terminatingMobileUserClass1',
    'terminatingMobileUserClass2',
    'contractorNumber',
    'terminatingUserClass',
    'userClass',
    'calledPartyMNPInfo',
    'chargeNumber',
    'originatingLineInformation',
    'multimediaInformation',
    'globalCallReference',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'calledDirectoryNumber',
    'incomingPChargingVector',
    'outputType',
    'outgoingPChargingVector',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'carrierIdentificationCode',
    'carrierInformation',
    'carrierSelectionSubstitutionInformation',
    'interExchangeCarrierIndicator'
]


##############################
# mSOriginating              #
##############################
componentHash['mSOriginating'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'callingSubscriberIMSI',
    'callingSubscriberIMEI',
    'calledPartyNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'timeFromRegisterSeizureToStartOfCharging',
    'chargedParty',
    'originForCharging',
    'chargingCase',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'incomingRoute',
    'miscellaneousInformation',
    'originatingLocationNumber',
    'timeForTCSeizureCalling',
    'firstCallingLocationInformation',
    'lastCallingLocationInformation',
    'teleServiceCode',
    'bearerServiceCode',
    'transparencyIndicator',
    'firstRadioChannelUsed',
    'callPosition',
    'eosInfo',
    'internalCauseAndLoc',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'numberOfMeterPulses',
    'c7ChargingMessage',
    'c7FirstCHTMessage',
    'c7SecondCHTMessage',
    'calledPartyMNPInfo',
    'carrierIdentificationCode',
    'dTMFUsed',
    'iCIOrdered',
    'outputForSubscriber',
    'iNMarkingOfMS',
    'lastPartialOutput',
    'partialOutputRecNum',
    'cUGInterlockCode',
    'cUGIndex',
    'cUGOutgoingAccessUsed',
    'cUGOutgoingAccessIndicator',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'sSCode',
    'channelAllocationPriorityLevel',
    'radioChannelProperty',
    'faultCode',
    'intermediateRate',
    'firstAssignedSpeechCoderVersion',
    'speechCoderPreferenceList',
    'subscriptionType',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'originatedCode',
    'switchIdentity',
    'networkCallReference',
    'frequencyBandSupported',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'accountCode',
    'translatedNumber',
    'bCSMTDPData1',
    'bCSMTDPData2',
    'bCSMTDPData3',
    'bCSMTDPData4',
    'bCSMTDPData5',
    'bCSMTDPData6',
    'bCSMTDPData7',
    'bCSMTDPData8',
    'bCSMTDPData9',
    'bCSMTDPData10',
    'gSMCallReferenceNumber',
    'mSCAddress',
    'eMLPPPriorityLevel',
    'positionAccuracy',
    'userTerminalPosition',
    'acceptableChannelCodings',
    'incomingAssignedRoute',
    'channelCodingUsed',
    'rANAPCauseCode',
    'gsmSCFAddress',
    'fNURRequested',
    'aIURRequested',
    'numberOfChannelsRequested',
    'bSSMAPCauseCode',
    'multimediaCall',
    'guaranteedBitRate',
    'trafficClass',
    'outputType',
    'rNCidOfFirstRNC',
    'maxBitRateDownlink',
    'maxBitRateUplink',
    'transferDelay',
    'deliveryOfErroneousSDU1',
    'deliveryOfErroneousSDU2',
    'deliveryOfErroneousSDU3',
    'residualBitErrorRatio1',
    'residualBitErrorRatio2',
    'residualBitErrorRatio3',
    'sDUErrorRatio1',
    'sDUErrorRatio2',
    'sDUErrorRatio3',
    'aCMChargingIndicator',
    'aNMChargingIndicator',
    'carrierInformationBackward',
    'chargeInformation',
    'disconnectionDate',
    'disconnectionTime',
    'originatingCarrier',
    'originatingChargeArea',
    'tDSCounter',
    'terminatingAccessISDN',
    'terminatingCarrier',
    'terminatingChargeArea',
    'terminatingMobileUserClass1',
    'terminatingMobileUserClass2',
    'terminatingUserClass',
    'contractorNumber',
    'carrierInformation',
    'carrierSelectionSubstitutionInformation',
    'chargeNumber',
    'interExchangeCarrierIndicator',
    'originatingLineInformation',
    'selectedCodec',
    'wPSCallIndicator',
    'userToUserInformation',
    'callingSubscriberIMEISV',
    'globalCallReference',
    'roamingPriorityLevel',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'calledDirectoryNumber',
    'outgoingPChargingVector',
    'iuCodec',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'ccbsCallIndicator',
    'mMEName',
    'mMEIdentity',
    'sRVCCIndicator',
    'sRVCCAlertingIndicator',
    'pChargingVectorRelated',
    'emergencyServiceCategory'
]


##############################
# roamingCallForwarding      #
##############################
componentHash['roamingCallForwarding'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'calledPartyNumber',
    'calledSubscriberIMSI',
    'mobileStationRoamingNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'timeFromRegisterSeizureToStartOfCharging',
    'chargedParty',
    'originForCharging',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'incomingRoute',
    'miscellaneousInformation',
    'subscriptionType',
    'callPosition',
    'eosInfo',
    'internalCauseAndLoc',
    'originalCalledNumber',
    'redirectingNumber',
    'redirectionCounter',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'numberOfMeterPulses',
    'c7ChargingMessage',
    'c7FirstCHTMessage',
    'c7SecondCHTMessage',
    'iCIOrdered',
    'outputForSubscriber',
    'lastPartialOutput',
    'partialOutputRecNum',
    'relatedCallNumber',
    'cUGInterlockCode',
    'cUGOutgoingAccessIndicator',
    'presentationAndScreeningIndicator',
    'faultCode',
    'incompleteCallDataIndicator',
    'multimediaInformation',
    'switchIdentity',
    'networkCallReference',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'gSMCallReferenceNumber',
    'mSCAddress',
    'carrierInformationBackward',
    'originatingAccessISDN',
    'originatingCarrier',
    'originatingChargeArea',
    'terminatingAccessISDN',
    'terminatingCarrier',
    'terminatingChargeArea',
    'contractorNumber',
    'carrierIdentificationCode',
    'carrierInformation',
    'carrierSelectionSubstitutionInformation',
    'chargeNumber',
    'interExchangeCarrierIndicator',
    'originatingLineInformation',
    'userToUserInformation',
    'globalCallReference',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'mobileSubscriberNumberForHLRInterrogation',
    'outgoingPChargingVector',
    'bladeID',
    'trafficIsolationIndicator',
    'mTRFIndicator',
    'buddyBladeIndicator'
]

# pad out to 122 elements, and fill in indices 102 and 121
componentHash['roamingCallForwarding'] = componentHash['roamingCallForwarding'] + [None] * (122 - len(componentHash['roamingCallForwarding']))
componentHash['roamingCallForwarding'][102] = 'outputType'
componentHash['roamingCallForwarding'][121] = 'reroutingIndicator'


##############################
# callForwarding      #
##############################
componentHash['callForwarding'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'calledPartyNumber',
    'originalCalledNumber',
    'redirectingNumber',
    'redirectionCounter',
    'redirectingSPN',
    'redirectingIMSI',
    'mobileStationRoamingNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'timeFromRegisterSeizureToStartOfCharging',
    'chargedParty',
    'originForCharging',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'incomingRoute',
    'miscellaneousInformation',
    'originatingLocationNumber',
    'callPosition',
    'eosInfo',
    'internalCauseAndLoc',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'numberOfMeterPulses',
    'c7ChargingMessage',
    'c7FirstCHTMessage',
    'c7SecondCHTMessage',
    'iCIOrdered',
    'outputForSubscriber',
    'iNMarkingOfMS',
    'lastPartialOutput',
    'partialOutputRecNum',
    'relatedCallNumber',
    'cUGInterlockCode',
    'cUGIndex',
    'cUGOutgoingAccessUsed',
    'cUGOutgoingAccessIndicator',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'presentationAndScreeningIndicator',
    'faultCode',
    'subscriptionType',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'originatedCode',
    'switchIdentity',
    'networkCallReference',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'translatedNumber',
    'cAMELInitiatedCallForwarding',
    'bCSMTDPData1',
    'bCSMTDPData2',
    'bCSMTDPData3',
    'bCSMTDPData4',
    'bCSMTDPData5',
    'bCSMTDPData6',
    'bCSMTDPData7',
    'bCSMTDPData8',
    'bCSMTDPData9',
    'bCSMTDPData10',
    'gSMCallReferenceNumber',
    'mSCAddress',
    'aCMChargingIndicator',
    'aNMChargingIndicator',
    'carrierInformationBackward',
    'chargeInformation',
    'disconnectionDate',
    'disconnectionTime',
    'exitPOICA',
    'originatingCarrier',
    'originatingChargeArea',
    'terminatingAccessISDN',
    'terminatingCarrier',
    'terminatingChargeArea',
    'terminatingMobileUserClass1',
    'terminatingMobileUserClass2',
    'terminatingUserClass',
    'originatingAccessISDN',
    'contractorNumber',
    'calledPartyMNPInfo',
    'carrierIdentificationCode',
    'carrierInformation',
    'carrierSelectionSubstitutionInformation',
    'chargeNumber',
    'interExchangeCarrierIndicator',
    'originatingLineInformation',
    'optimalRoutingType',
    'optimalRoutingInvocationFailed',
    'userToUserInformation',
    'outputType',
    'multimediaInformation',
    'globalCallReference',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'calledDirectoryNumber',
    'outgoingPChargingVector',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
]

# pad out to 122 elements, and fill in index 121
componentHash['callForwarding'] = componentHash['callForwarding'] + [None] * (122 - len(componentHash['callForwarding']))
componentHash['callForwarding'][121] = 'reroutingIndicator'


##############################
# mSTerminating      #
##############################
componentHash['mSTerminating'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'calledPartyNumber',
    'calledSubscriberIMSI',
    'calledSubscriberIMEI',
    'mobileStationRoamingNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'timeFromRegisterSeizureToStartOfCharging',
    'chargedParty',
    'originForCharging',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'incomingRoute',
    'channelAllocationPriorityLevel',
    'terminatingLocationNumber',
    'timeForTCSeizureCalled',
    'firstCalledLocationInformation',
    'lastCalledLocationInformation',
    'teleServiceCode',
    'bearerServiceCode',
    'transparencyIndicator',
    'firstRadioChannelUsed',
    'callPosition',
    'eosInfo',
    'internalCauseAndLoc',
    'originalCalledNumber',
    'redirectingNumber',
    'redirectionCounter',
    'selectedCodec',
    'userToUserInformation',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'dTMFUsed',
    'iCIOrdered',
    'outputForSubscriber',
    'lastPartialOutput',
    'partialOutputRecNum',
    'relatedCallNumber',
    'acceptanceOfCallWaiting',
    'miscellaneousInformation',
    'cUGInterlockCode',
    'cUGIndex',
    'cUGIncomingAccessUsed',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'sSCode',
    'presentationAndScreeningIndicator',
    'radioChannelProperty',
    'faultCode',
    'intermediateRate',
    'firstAssignedSpeechCoderVersion',
    'speechCoderPreferenceList',
    'subscriptionType',
    'incompleteCallDataIndicator',
    'mSCAddress',
    'switchIdentity',
    'networkCallReference',
    'frequencyBandSupported',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'accountCode',
    'gSMCallReferenceNumber',
    'eMLPPPriorityLevel',
    'positionAccuracy',
    'userTerminalPosition',
    'acceptableChannelCodings',
    'outgoingAssignedRoute',
    'channelCodingUsed',
    'multimediaCall',
    'gsmSCFAddress',
    'fNURRequested',
    'aIURRequested',
    'numberOfChannelsRequested',
    'bSSMAPCauseCode',
    'guaranteedBitRate',
    'trafficClass',
    'rANAPCauseCode',
    'rNCidOfFirstRNC',
    'maxBitRateDownlink',
    'maxBitRateUplink',
    'transferDelay',
    'deliveryOfErroneousSDU1',
    'deliveryOfErroneousSDU2',
    'deliveryOfErroneousSDU3',
    'residualBitErrorRatio1',
    'residualBitErrorRatio2',
    'residualBitErrorRatio3',
    'sDUErrorRatio1',
    'sDUErrorRatio2',
    'sDUErrorRatio3',
    'outputType',
    'aCMChargingIndicator',
    'aNMChargingIndicator',
    'chargeInformation',
    'disconnectionDate',
    'disconnectionTime',
    'internationalCallIndicator',
    'mobileUserClass1',
    'mobileUserClass2',
    'originatingCarrier',
    'originatingChargeArea',
    'terminatingCarrier',
    'terminatingChargeArea',
    'userClass',
    'calledSubscriberIMEISV',
    'globalCallReference',
    'iuCodec',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'mMEName',
    'mTRFIndicator'
]


##############################
# mSOriginatingSMSinMSC      #
##############################
componentHash['mSOriginatingSMSinMSC'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'callingSubscriberIMSI',
    'callingSubscriberIMEI',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'chargedParty',
    'originForCharging',
    'exchangeIdentity',
    'mSCIdentification',
    'incomingRoute',
    'firstCallingLocationInformation',
    'teleServiceCode',
    'serviceCentreAddress',
    'callingSubscriberIMEISV',
    None,
    'iCIOrdered',
    'outputForSubscriber',
    'miscellaneousInformation',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'channelAllocationPriorityLevel',
    'frequencyBandSupported',
    'incompleteCallDataIndicator',
    'restartDuringOutputIndicator',
    'forloppDuringOutputIndicator',
    'positionAccuracy',
    'userTerminalPosition',
    'switchIdentity',
    'destinationAddress',
    'messageReference',
    'messageTypeIndicator',
    'rNCidOfFirstRNC',
    'bCSMTDPData1',
    'cAMELCallingPartyNumber',
    'cAMELDestinationAddress',
    'cAMELSMSCAddress',
    'defaultSMSHandling',
    'freeFormatData',
    'sMSResult',
    'sMSReferenceNumber',
    'mSCAddress',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'mCASMSIndicator',
    'reroutedToServiceCentreAddress',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'firstCallingLocationInformationExtension',
    'mMEName',
    'uETimeZone',
]

# pad out to 103 elements, and fill in index 102
componentHash['mSOriginatingSMSinMSC'] = componentHash['mSOriginatingSMSinMSC'] + [None] * (103 - len(componentHash['mSOriginatingSMSinMSC']))
componentHash['mSOriginatingSMSinMSC'][102] = 'outputType'


###############################
# mSOriginatingSMSinSMS_IWMSC #
###############################
componentHash['mSOriginatingSMSinSMS_IWMSC'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'callingPartyNumber',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'chargedParty',
    'exchangeIdentity',
    'mSCIdentification',
    'teleServiceCode',
    'serviceCentreAddress',
    'miscellaneousInformation',
    'incompleteCallDataIndicator',
    'restartDuringOutputIndicator',
    'forloppDuringOutputIndicator',
    'switchIdentity',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['mSOriginatingSMSinSMS_IWMSC'] = componentHash['mSOriginatingSMSinSMS_IWMSC'] + [None] * (103 - len(componentHash['mSOriginatingSMSinSMS_IWMSC']))
componentHash['mSOriginatingSMSinSMS_IWMSC'][102] = 'outputType'


###############################
# mSTerminatingSMSinMSC       #
###############################
componentHash['mSTerminatingSMSinMSC'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'calledPartyNumber',
    'calledSubscriberIMSI',
    'calledSubscriberIMEI',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'originForCharging',
    'chargedParty',
    'exchangeIdentity',
    'mSCIdentification',
    'outgoingRoute',
    'firstCalledLocationInformation',
    'teleServiceCode',
    'serviceCentreAddress',
    None,
    None,
    'iCIOrdered',
    'outputForSubscriber',
    'miscellaneousInformation',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'channelAllocationPriorityLevel',
    'incompleteCallDataIndicator',
    'restartDuringOutputIndicator',
    'frequencyBandSupported',
    'forloppDuringOutputIndicator',
    'numberOfShortMessages',
    'lastCalledLocationInformation',
    'positionAccuracy',
    'userTerminalPosition',
    'switchIdentity',
    'originatingAddress',
    'messageTypeIndicator',
    'rNCidOfFirstRNC',
    'bCSMTDPData1',
    'defaultSMSHandling',
    'freeFormatData',
    'sMSResult',
    'sMSReferenceNumber',
    'mSCAddress',
    'cAMELOriginatingAddress',
    'calledSubscriberIMEISV',
    'rTCIndicator',
    'rTCSessionID',
    'rTCDefaultServiceHandling',
    'rTCFailureIndicator',
    'rTCNotInvokedReason',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'firstCalledLocationInformationExtension',
    'mMEName',
    'uETimeZone',
    'lastCalledLocationInformationExtension',
]

# pad out to 103 elements, and fill in index 102
componentHash['mSTerminatingSMSinMSC'] = componentHash['mSTerminatingSMSinMSC'] + [None] * (103 - len(componentHash['mSTerminatingSMSinMSC']))
componentHash['mSTerminatingSMSinMSC'][102] = 'outputType'


##############################
# mSTerminatingSMSinSMS_GMSC #
##############################
componentHash['mSTerminatingSMSinSMS_GMSC'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'calledPartyNumber',
    'calledSubscriberIMSI',
    'mobileStationRoamingNumber',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'chargedParty',
    'exchangeIdentity',
    'mSCIdentification',
    'teleServiceCode',
    'serviceCentreAddress',
    'mSCNumber',
    'miscellaneousInformation',
    'incompleteCallDataIndicator',
    'restartDuringOutputIndicator',
    'forloppDuringOutputIndicator',
    'numberOfShortMessages',
    'switchIdentity',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['mSTerminatingSMSinSMS_GMSC'] = componentHash['mSTerminatingSMSinSMS_GMSC'] + [None] * (103 - len(componentHash['mSTerminatingSMSinSMS_GMSC']))
componentHash['mSTerminatingSMSinSMS_GMSC'][102] = 'outputType'


###############################
# sSProcedure #
###############################
componentHash['sSProcedure'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'callingPartyNumber',
    'callingSubscriberIMSI',
    'callingSubscriberIMEI',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'originForCharging',
    'exchangeIdentity',
    'mSCIdentification',
    'firstCallingLocationInformation',
    'callingSubscriberIMEISV',
    None,
    'iCIOrdered',
    'outputForSubscriber',
    'sSCode',
    'sSRequest',
    'miscellaneousInformation',
    'regionalServiceUsed',
    'regionDependentChargingOrigin',
    'relatedCallNumber',
    'uSSDApplicationIdentifier',
    'uSSDServiceCode',
    'uSSDProcedureCode',
    'networkInitiatedUSSDOperations',
    'uSSDOperationIdentifier',
    'incompleteCallDataIndicator',
    'restartDuringOutputIndicator',
    'frequencyBandSupported',
    'forloppDuringOutputIndicator',
    'switchIdentity',
    'networkCallReference',
    'positionAccuracy',
    'userTerminalPosition',
    'rNCidOfFirstRNC',
    'globalCallReference',
    'bladeID',
    'buddyBladeIndicator',
    'mMEName',
]

# pad out to 103 elements, and fill in index 102
componentHash['sSProcedure'] = componentHash['sSProcedure'] + [None] * (103 - len(componentHash['sSProcedure']))
componentHash['sSProcedure'][102] = 'outputType'


###############################
# transitINOutgoingCall #
###############################
componentHash['transitINOutgoingCall'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'outgoingRoute',
    'subscriptionType',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'restartDuringOutputIndicator',
    'exchangeIdentity',
    'restartDuringCall',
    'networkCallReference',
    'iCIOrdered',
    'outputForSubscriber',
    'switchIdentity',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'tariffClass',
    'forloppReleaseDuringCall',
    'c7ChargingMessage',
    'c7FirstCHTMessage',
    'c7SecondCHTMessage',
    'contractorNumber',
    'calledPartyMNPInfo',
    'globalCallReference',
    'outgoingPChargingVector',
    'bladeID',
    'trafficIsolationIndicator',
]

# pad out to 103 elements, and fill in index 102
componentHash['transitINOutgoingCall'] = componentHash['transitINOutgoingCall'] + [None] * (103 - len(componentHash['transitINOutgoingCall']))
componentHash['transitINOutgoingCall'][102] = 'outputType'


###############################
# iNIncomingCall #
###############################
componentHash['iNIncomingCall'] = [
    'callIdentificationNumber',
    'switchIdentity',
    'networkCallReference',
    'iNServiceTrigger',
    'sSFChargingCase',
    'triggerData0',
    'triggerData1',
    'triggerData2',
    'triggerData3',
    'triggerData4',
    'triggerData5',
    'triggerData6',
    'triggerData7',
    'recordSequenceNumber',
    'disconnectionDueToSystemRecovery',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'restartDuringOutputIndicator',
    'restartDuringCall',
    'exchangeIdentity',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'gSMCallReferenceNumber',
    'mSCAddress',
    'defaultCallHandling',
    'defaultCallHandling2',
    'levelOfCAMELService',
    'globalCallReference',
    'bladeID',
    'trafficIsolationIndicator',
]

# pad out to 103 elements, and fill in index 102
componentHash['iNIncomingCall'] = componentHash['iNIncomingCall'] + [None] * (103 - len(componentHash['iNIncomingCall']))
componentHash['iNIncomingCall'][102] = 'outputType'


###############################
# iNOutgoingCall #
###############################
componentHash['iNOutgoingCall'] = [
    'callIdentificationNumber',
    'switchIdentity',
    'networkCallReference',
    'iNServiceTrigger',
    'sSFChargingCase',
    'triggerData0',
    'triggerData1',
    'triggerData2',
    'triggerData3',
    'triggerData4',
    'triggerData5',
    'triggerData6',
    'triggerData7',
    'recordSequenceNumber',
    'disconnectionDueToSystemRecovery',
    'incompleteCallDataIndicator',
    'incompleteCompositeCDRIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'restartDuringOutputIndicator',
    'restartDuringCall',
    'exchangeIdentity',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'gSMCallReferenceNumber',
    'mSCAddress',
    'defaultCallHandling',
    'defaultCallHandling2',
    'levelOfCAMELService',
    'gsmSCFInitiatedCallIndicator',
    'globalCallReference',
    'bladeID',
    'trafficIsolationIndicator',
]

# pad out to 103 elements, and fill in index 102
componentHash['iNOutgoingCall'] = componentHash['iNOutgoingCall'] + [None] * (103 - len(componentHash['iNOutgoingCall']))
componentHash['iNOutgoingCall'][102] = 'outputType'


###############################
# iSDNOriginating #
###############################
componentHash['iSDNOriginating'] = [
    'trafficActivityCode',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'chargedCallingPartyNumber',
    'calledPartyNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'outgoingRoute',
    'callPosition',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'cUGInterlockCode',
    'cUGIndex',
    'presentationAndScreeningIndicator',
    'incompleteCallDataIndicator',
    'networkCallReference',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'causeCode',
    'locationCode',
    'networkProvidedCallingPartyNumber',
    'calledPartyMNPInfo',
    'callingPartyNumberSpecialArrangementInd',
    'userProvidedCallingPartyNumber',
    'forloppReleaseDuringCall',
    'chargedParty',
    'callAttemptIndicator',
    'flexibleCounter1',
    'flexibleCounter2',
    'flexibleCounter3',
    'flexibleCounter4',
    'flexibleCounter5',
    'flexibleCounter6',
    'flexibleCounter7',
    'flexibleCounter8',
    'callAttemptState',
    'typeOfSignalling',
    'typeOfCalledSubscriber',
    'endToEndAccessDataMap',
    'userToUserService1Information',
    'switchIdentity',
    'aoCCurrencyAmountSentToUser',
    'globalCallReference',
    'outgoingPChargingVector',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['iSDNOriginating'] = componentHash['iSDNOriginating'] + [None] * (103 - len(componentHash['iSDNOriginating']))
componentHash['iSDNOriginating'][102] = 'outputType'


###############################
# iSDNCallForwarding #
###############################
componentHash['iSDNCallForwarding'] = [
    'trafficActivityCode',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'chargedCallingPartyNumber',
    'calledPartyNumber',
    'disconnectingParty',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'timeForStopOfCharge',
    'chargeableDuration',
    'interruptionTime',
    'tariffClass',
    'tariffSwitchInd',
    'exchangeIdentity',
    'outgoingRoute',
    'callPosition',
    'originalCalledNumber',
    'redirectingNumber',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'cUGInterlockCode',
    'cUGIndex',
    'presentationAndScreeningIndicator',
    'incompleteCallDataIndicator',
    'networkCallReference',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'causeCode',
    'locationCode',
    'networkProvidedCallingPartyNumber',
    'callingPartyNumber',
    'calledPartyMNPInfo',
    'forloppReleaseDuringCall',
    'chargedParty',
    'callAttemptIndicator',
    'flexibleCounter1',
    'flexibleCounter2',
    'flexibleCounter3',
    'flexibleCounter4',
    'flexibleCounter5',
    'flexibleCounter6',
    'flexibleCounter7',
    'flexibleCounter8',
    'callAttemptState',
    'typeOfSignalling',
    'typeOfCalledSubscriber',
    'endToEndAccessDataMap',
    'userToUserService1Information',
    'switchIdentity',
    'aoCCurrencyAmountSentToUser',
    'globalCallReference',
    'outgoingPChargingVector',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['iSDNCallForwarding'] = componentHash['iSDNCallForwarding'] + [None] * (103 - len(componentHash['iSDNCallForwarding']))
componentHash['iSDNCallForwarding'][102] = 'outputType'


###############################
# iSDNSSProcedure #
###############################
componentHash['iSDNSSProcedure'] = [
    'trafficActivityCode',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'TypeOfCallingSubscriber',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'tariffClass',
    'exchangeIdentity',
    'restartDuringOutputIndicator',
    'incompleteCallDataIndicator',
    'forloppDuringOutputIndicator',
    'servedSubscriberNumber',
    'chargedParty',
    'switchIdentity',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['iSDNSSProcedure'] = componentHash['iSDNSSProcedure'] + [None] * (103 - len(componentHash['iSDNSSProcedure']))
componentHash['iSDNSSProcedure'][102] = 'outputType'


###############################
# sCFChargingOutput #
###############################
componentHash['sCFChargingOutput'] = [
    'callIdentificationNumber',
    'exchangeIdentity',
    'gSMCallReferenceNumber',
    'restartDuringCall',
    'restartDuringOutputIndicator',
    'lastPartialOutput',
    'partialOutputRecNum',
    'switchIdentity',
    'disconnectionDueToSystemRecovery',
    'forloppDuringOutputIndicator',
    'forloppReleaseDuringCall',
    'recordSequenceNumber',
    'incompleteCallDataIndicator',
    'mSCAddress',
    'date',
    'bladeID',
]

# pad out to 103 elements, and fill in index 102
componentHash['sCFChargingOutput'] = componentHash['sCFChargingOutput'] + [None] * (103 - len(componentHash['sCFChargingOutput']))
componentHash['sCFChargingOutput'][102] = 'outputType'


###############################
# locationServices #
###############################
componentHash['locationServices'] = [
    'tAC',
    'callIdentificationNumber',
    'recordSequenceNumber',
    'typeOfCallingSubscriber',
    'targetMSISDN',
    'targetIMSI',
    'targetIMEI',
    'dateForStartOfCharge',
    'timeForStartOfCharge',
    'exchangeIdentity',
    'mSCIdentification',
    'miscellaneousInformation',
    'restartDuringOutputIndicator',
    'iCIOrdered',
    'outputForSubscriber',
    'incompleteCallDataIndicator',
    'switchIdentity',
    'networkCallReference',
    'forloppDuringOutputIndicator',
    'positioningDelivery',
    'lCSClientIdentity',
    'lCSClientType',
    'locationEstimate',
    'ageOfLocationEstimate',
    'subscriberState',
    'mLCAddress',
    'decipheringKeys',
    'typeOfLocationRequest',
    'firstTargetLocationInformation',
    'horizontalAccuracy',
    'responseTimeCategory',
    'verticalAccuracy',
    'verticalCoordinateRequest',
    'unsuccessfulPositioningDataReason',
    'lCSDeferredEventType',
    'targetIMEISV',
    'globalCallReference',
    'bladeID',
    'buddyBladeIndicator',
    'trafficIsolationIndicator',
    'mMEName',
]

# pad out to 103 elements, and fill in index 102
componentHash['locationServices'] = componentHash['locationServices'] + [None] * (103 - len(componentHash['locationServices']))
componentHash['locationServices'][102] = 'outputType'


################################################################################
# Event Modules                                                                #
################################################################################

###############################
# aoCEventModule #
###############################
componentHash['aoCEventModule'] = [
    'tAC',
    'cRIToMS',
    'cRIIndicator',
    'sSCode',
    'timeForEvent',
    'incompleteCallDataIndicator',
    'gsmSCFControlOfAoC',
]


###############################
# sSInvocationEventModule #
###############################
componentHash['sSInvocationEventModule'] = [
    'tAC',
    'sSCode',
    'sSRequest',
    'timeForEvent',
    'firstCallingLocationInformation',
    'cRIIndicator',
    'eventCRIToMS',
    'incompleteCallDataIndicator',
    None,
    'networkCallReference',
    'sSInvocationNotification',
    'globalCallReference',
]


###############################
# serviceSwitchEventModule #
###############################
componentHash['serviceSwitchEventModule'] = [
    'tAC',
    'timeForEvent',
    'serviceSwitchingType',
    'incompleteCallDataIndicator',
]


###############################
# iNServiceDataEventModule #
###############################
componentHash['iNServiceDataEventModule'] = [
    'chargePartyDistributed',
    'chargePartySingle',
    'chargingUnitsAddition',
    'genericChargingDigits',
    'genericChargingNumbers',
    'serviceFeatureCode',
    'timeForEvent',
    'incompleteCallDataIndicator[7]',
    'freeFormatData',
    'FreeFormatData',
    'freeFormatData2',
    'freeFormatDataAppendIndicator',
    'freeFormatDataAppendIndicator2',
]


###############################
# chargeRateChangeEventModule #
###############################
componentHash['chargeRateChangeEventModule'] = [
    'tAC',
    'timeForEvent',
    'radioChannelProperty',
    'changeInitiatingParty',
    'tariffClass',
    None,
    None,
    'aIURRequested',
    'numberOfChannelsRequested',
    'channelCodingUsed',
]


###############################
# iSDNSSInvocationEventModule #
###############################
componentHash['iSDNSSInvocationEventModule'] = [
    'trafficActivityCode',
    'incompleteCallDataIndicator'
]


###############################
# handOverEventModule #
###############################
componentHash['handOverEventModule'] = [
    'tAC',
    'timeForEvent',
    'rNCidOfTargetRNC',
    'incompleteCallDataIndicator',
    'targetLocationInformation',
    'radioChannelProperty',
    'channelCodingUsed',
    'bSSMAPCauseCode',
    'rANAPCauseCode',
    'interRegionHandoverIndicator',
]


################################################################################
# Data Types that are Constructors                                             #
################################################################################

##############################
# CAMELTDPData #
##############################
componentHash['CAMELTDPData'] = [
    'serviceKey',
    'gsmSCFAddress'
]

##############################
# MultimediaInformation #
##############################
componentHash['multimediaInformation'] = [
    'userRate',
    'asyncSyncIndicator',
    'uILayer1Protocol'
]

##############################
# TriggerData #
##############################
componentHash['triggerData'] = [
    'triggerDetectionPoint',
    'serviceKey',
    'co-located',
    'pointCodeAndSubSystemNumber',
    'globalTitle',
    'globalTitleAndSubSystemNumber'
]

