// CNTDEF.H
//
// Copyright (c) Symbian Software Ltd 1997-2007.  All rights reserved.
//

#ifndef __CNTDEF_H__
#define __CNTDEF_H__

#include <e32base.h>

#if !( defined __SYMBIAN_CNTMODEL_HIDE_DBMS__ && defined __SYMBIAN_CNTMODEL_USE_SQLITE__ )
#include <d32dbms.h>
#else
#include <s32std.h>
#include <f32file.h>
#endif

#include <cntdef.hrh>


// Constants

/**
@internalTechnology

*/
const TInt KSpeedDialPhoneLength = 64;

/**
@internalTechnology

*/
const TInt KCntMinSpeedDialIndex = 1;

/**
@internalTechnology

*/
const TInt KCntMaxSpeedDialIndex = 9;

/**
Phone Match Length
@internalTechnology

*/
const TInt KMaxPhoneMatchLength = 15;

/**
@internalTechnology

*/
const TInt KLowerSevenDigits = 7;

/**
Used for firstname, lastname, companyname, secondname and their
associated pronunciation fields and e-mail address
@internalTechnology

*/
const TInt KCntMaxTextFieldLength=255;

// Type definitions

/**
@internalTechnology

*/
typedef TBuf<KSpeedDialPhoneLength> TSpeedDialPhoneNumber;

/** Contact item ID. These are used to uniquely identify contact items within a
contacts database. Contact items include contact cards, contact card templates,
contact card groups and own cards. Contact item IDs are also used to uniquely
identify agents.
@publishedAll

*/
typedef TInt32 TContactItemId;

/** A UID which identifies a contact item field's type. The possible values are
defined as UIDs in cntdef.h.
@publishedAll

*/
typedef TUid TFieldType;

/** A contact item field's storage type.

This is an unsigned integer value which identifies the type of data stored
in a contact item field. The possible values are defined in cntdef.hrh as:

- KStorageTypeText (used by CContactTextFields)

- KStorageTypeStore (used by CContactStoreFields)

- KStorageTypeContactItemId (used by CContactAgentFields)

- KStorageTypeDateTime (used by CContactDateFields)

Note that numeric fields are not supported. Numbers (e.g. telephone
numbers) are stored in the database using text fields.
@publishedAll

*/
typedef TUint TStorageType;

/** Machine identifier.

This is used when synchronising the contact database to identify the
machine with which the database has been synchronised.
@see CContactDatabase::SetLastSyncDateL()
@see CContactDatabase::GetLastSyncDateL().
@publishedAll

*/
typedef TInt32 TContactSyncId;

/** Stores the value of KUidContactsDbFile as an integer.
@publishedAll

*/
const TInt KUidContactsDbFileValue=0x100065FF;
/**
The third UID of the contacts database file, c:\\system\\data\\contacts.cdb.
This should be used by file recogniser implementations.
@publishedAll

*/
const TUid KUidContactsDbFile={KUidContactsDbFileValue};


/** NULL contact item ID. Indicates that no contact item is present.
@publishedAll

*/
const TContactItemId KNullContactId=-1;
/**
The ID of the system template.
@publishedAll

*/
const TContactItemId KGoldenTemplateId=0;

/** Identifies a vCard that has been pasted from the clipboard into the Contacts application.
@publishedAll

*/
const TUid KClipboardUidTypeVCard={0x100038f6};

/** Identifies a contact card (CContactCard).
@publishedAll

*/
const TUid KUidContactCard={KUidContactCardValue};
/** Identifies a contact group (CContactGroup).
@publishedAll

*/
const TUid KUidContactGroup={KUidContactGroupValue};
/** Identifies the system template (CContactTemplate).
@publishedAll

*/
const TUid KUidContactTemplate={KUidContactTemplateValue};
/** Identifies an own card (CContactOwnCard).
@publishedAll

*/
const TUid KUidContactOwnCard={KUidContactOwnCardValue}; 
/** Identifies a non-system template (CContactCardTemplate). 
@publishedAll

*/
const TUid KUidContactCardTemplate={KUidContactCardTemplateValue};
/** The UID that identifies ICC entries. These are a special type of
contact item that are stored in the SIM (ICC) card on the phone.

@publishedAll

*/
const TUid KUidContactICCEntry={KUidContactICCEntryValue};

/** Identifies any CContactItem-derived class (all of the above).
@publishedAll

*/
const TUid KUidContactItem={0x10005673};
/** This identifies the CContactCard and CContactGroup classes.
It is used internally by the contacts model.
@publishedAll

*/
const TUid KUidContactCardOrGroup={0x10005F71};


/*
 * Speed-dial UIDs.
 * These are used to indicate the speed-dial position for a particular field.
 * They are added to the content type of a phone number field set as a
 * speed-dial using CContactDatabase::SetFieldAsSpeedDialL().
 */
/** Field maps to the first speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialOne={KUidSpeedDialOneValue};
/** Field maps to the second speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialTwo={KUidSpeedDialTwoValue};
/** Field maps to the third speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialThree={KUidSpeedDialThreeValue};
/** Field maps to the fourth speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialFour={KUidSpeedDialFourValue};
/** Field maps to the fifth speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialFive={KUidSpeedDialFiveValue};
/** Field maps to the sixth speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialSix={KUidSpeedDialSixValue};
/** Field maps to the seventh speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialSeven={KUidSpeedDialSevenValue};
/** Field maps to the eighth speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialEight={KUidSpeedDialEightValue};
/** Field maps to the ninth speed dial position.
@publishedAll

*/
const TUid KUidSpeedDialNine={KUidSpeedDialNineValue};

/*
 * Contact field type UIDs.
 */
/** Address field.
@publishedAll

*/
const TUid KUidContactFieldAddress={KUidContactFieldAddressValue};
/** Post office box field.
@publishedAll

*/
const TUid KUidContactFieldPostOffice={KUidContactFieldPostOfficeValue};
/** Extended address field.
@publishedAll

*/
const TUid KUidContactFieldExtendedAddress={KUidContactFieldExtendedAddressValue};
/** Locality field.
@publishedAll

*/
const TUid KUidContactFieldLocality={KUidContactFieldLocalityValue};
/** Region field.
@publishedAll

*/
const TUid KUidContactFieldRegion={KUidContactFieldRegionValue};
/** Post code field.
@publishedAll

*/
const TUid KUidContactFieldPostcode={KUidContactFieldPostCodeValue};
/** Country field.
@publishedAll

*/
const TUid KUidContactFieldCountry={KUidContactFieldCountryValue};

/** Company name field.
@publishedAll

*/
const TUid KUidContactFieldCompanyName={KUidContactFieldCompanyNameValue};
/** Company name pronunciation field.
@publishedAll

*/
const TUid KUidContactFieldCompanyNamePronunciation={KUidContactFieldCompanyNamePronunciationValue};
/** Phone number field.
@publishedAll

*/
const TUid KUidContactFieldPhoneNumber={KUidContactFieldPhoneNumberValue};
/** Given name field.
@publishedAll

*/
const TUid KUidContactFieldGivenName={KUidContactFieldGivenNameValue};
/** Family name field.
@publishedAll

*/
const TUid KUidContactFieldFamilyName={KUidContactFieldFamilyNameValue};
/** Given name pronunciation field.
@publishedAll

*/
const TUid KUidContactFieldGivenNamePronunciation={KUidContactFieldGivenNamePronunciationValue};
/** Family name pronunciation field.
@publishedAll

*/
const TUid KUidContactFieldFamilyNamePronunciation={KUidContactFieldFamilyNamePronunciationValue};
/** Middle name field.
@publishedAll

*/
const TUid KUidContactFieldAdditionalName={KUidContactFieldAdditionalNameValue};
/** Name suffix field.
@publishedAll

*/
const TUid KUidContactFieldSuffixName={KUidContactFieldSuffixNameValue};
/** Name prefix field.
@publishedAll

*/
const TUid KUidContactFieldPrefixName={KUidContactFieldPrefixNameValue};
/** Hidden field.
@publishedAll

*/
const TUid KUidContactFieldHidden={KUidContactFieldHiddenValue};
/** Hidden field.
@publishedAll

*/
const TUid KUidContactFieldDefinedText={KUidContactFieldDefinedTextValue};
/** Email address field.
@publishedAll

*/
const TUid KUidContactFieldEMail={KUidContactFieldEMailValue};
/** Telephone number used for a messaging service.
@publishedAll

*/
const TUid KUidContactFieldMsg={KUidContactFieldMsgValue};
/** Telephone number used for SMS messages.
@publishedAll

*/
const TUid KUidContactFieldSms={KUidContactFieldSmsValue};
/** Fax number field.
@publishedAll

*/
const TUid KUidContactFieldFax={KUidContactFieldFaxValue};
/** Comment field.
@publishedAll

*/
const TUid KUidContactFieldNote={KUidContactFieldNoteValue};
/** Comment field.
@publishedAll

*/
const TUid KUidContactStorageInline={KUidContactFieldStorageInlineValue};
/** Birthday field.
@publishedAll

*/
const TUid KUidContactFieldBirthday={KUidContactFieldBirthdayValue};
/** URL field.
@publishedAll

*/
const TUid KUidContactFieldUrl={KUidContactFieldUrlValue};
/** Template label field (a label which is used to refer to a template, for instance "work
template", "personal template").
@publishedAll

*/
const TUid KUidContactFieldTemplateLabel={KUidContactFieldTemplateLabelValue};
/** A picture field, for instance a logo or a photo.
@publishedAll

*/
const TUid KUidContactFieldPicture={KUidContactFieldPictureValue};
/** Used internally by the contacts model.
@publishedAll

*/
const TUid KUidContactFieldDTMF={KUidContactFieldDTMFValue};
/** Identifies a ring tone field. This is a ring tone that is associated with a contact item.
@publishedAll

*/
const TUid KUidContactFieldRingTone={KUidContactFieldRingToneValue};
/** Identifies a job title field.
@publishedAll

*/
const TUid KUidContactFieldJobTitle={KUidContactFieldJobTitleValue};
/** Identifies an instant messaging address field.
@publishedAll

*/
const TUid KUidContactFieldIMAddress = { KUidContactFieldIMAddressValue };
/** Identifies a USIM second name field. This field is provided to
store an additional representation of the contact's name, such as a
nickname or a different representation. An example could be a Japanese
contact which has a romanised name and an alternative representation using
kanji (pictogram) characters.
@publishedAll

*/
const TUid KUidContactFieldSecondName = { KUidContactFieldSecondNameValue };
/** Identifies a SIP identity field.
@publishedAll

*/
const TUid KUidContactFieldSIPID = { KUidContactFieldSIPIDValue };
/** Identifies a Assistant field.
@publishedAll

*/
const TUid KUidContactFieldAssistant = { KUidContactFieldAssistantValue };
/** Identifies an Anniversary field.
@publishedAll

*/
const TUid KUidContactFieldAnniversary = { KUidContactFieldAnniversaryValue };
/** Identifies a Spouse field.
@publishedAll

*/
const TUid KUidContactFieldSpouse = { KUidContactFieldSpouseValue };
/** Identifies a Children field.
@publishedAll

*/
const TUid KUidContactFieldChildren = { KUidContactFieldChildrenValue };
/** Identifies a Class field.
@publishedAll

*/
const TUid KUidContactFieldClass = { KUidContactFieldClassValue };
/** Identifies a Department field.
@publishedAll

*/
const TUid KUidContactFieldDepartmentName = { KUidContactFieldDepartmentNameValue };
/*
* CContactICCEntry (Telephony specific) UIDs.
 */
/** Identifies an ICC slot contact field in the contact item.
@publishedAll

*/
const TUid KUidContactFieldICCSlot={KUidContactFieldICCSlotValue};
/** Identifies an ICC Phonebook contact field in the contact item.
@publishedAll

*/
const TUid KUidContactFieldICCPhonebook={KUidContactFieldICCPhonebookValue};
/** Identifies an ICC Group contact field in the contact item.
@publishedAll

*/
const TUid KUidContactFieldICCGroup={KUidContactFieldICCGroupValue};

/** Identifies a voice dial field. This is a voice recording associated with a telephone number
field in the item.
@publishedAll

*/
const TUid KUidContactsVoiceDialField={KUidContactsVoiceDialFieldValue};

/** Indicates no field present.
@publishedAll

*/
const TUid KUidContactFieldNone={KUidContactFieldNoneValue};
/** Used in field type matching to indicate that all field types match.
@publishedAll

*/
const TInt32 KUidContactFieldMatchAllValue=0x110FFF22;
const TUid KUidContactFieldMatchAll={KUidContactFieldMatchAllValue};

/*
 * Contact field type vCard mappings.
 * The vCard mapping describes how the field should be handled by the
 * vCard import/export code.
 */
/** Field type maps to the Post office box field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPOSTOFFICE={KIntContactFieldVCardMapPOSTOFFICE};
/** Field type maps to the Extended address field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapEXTENDEDADR={KIntContactFieldVCardMapEXTENDEDADR};
/** Field type maps to vCard property ADR.
@publishedAll

*/
const TUid KUidContactFieldVCardMapADR={KIntContactFieldVCardMapADR};
/** Field type maps to the Locality field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapLOCALITY={KIntContactFieldVCardMapLOCALITY};
/** Field type maps to the Region field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapREGION={KIntContactFieldVCardMapREGION};
/** Field type maps to the Postcode field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPOSTCODE={KIntContactFieldVCardMapPOSTCODE};
/** Field type maps to the Country field in an ADR vCard property value.
@publishedAll

*/
const TUid KUidContactFieldVCardMapCOUNTRY={KIntContactFieldVCardMapCOUNTRY};

/** Field type maps to vCard property AGENT.
@publishedAll

*/
const TUid KUidContactFieldVCardMapAGENT={KIntContactFieldVCardMapAGENT};
/** Field type maps to vCard property BDAY.
@publishedAll

*/
const TUid KUidContactFieldVCardMapBDAY={KIntContactFieldVCardMapBDAY};
/** Field type maps to vCard property EMAIL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapEMAILINTERNET={KIntContactFieldVCardMapEMAILINTERNET};
/** Field type maps to vCard property GEO.
@publishedAll

*/
const TUid KUidContactFieldVCardMapGEO={KIntContactFieldVCardMapGEO};
/** Field type maps to vCard property LABEL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapLABEL={KIntContactFieldVCardMapLABEL};
/** Field type maps to vCard property LOGO.
@publishedAll

*/
const TUid KUidContactFieldVCardMapLOGO={KIntContactFieldVCardMapLOGO};
/** Field type maps to vCard property MAILER.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMAILER={KIntContactFieldVCardMapMAILER};
/** Field type maps to vCard property NOTE.
@publishedAll

*/
const TUid KUidContactFieldVCardMapNOTE={KIntContactFieldVCardMapNOTE};
/** Field type maps to vCard property ORG.
@publishedAll

*/
const TUid KUidContactFieldVCardMapORG={KIntContactFieldVCardMapORG};
/** Field type maps to vCard X-IRMC-ORG parameter of property SOUND.
@publishedAll

*/
const TUid KUidContactFieldVCardMapORGPronunciation={KIntContactFieldVCardMapORGPronunciation};
/** Field type maps to vCard property PHOTO.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPHOTO={KIntContactFieldVCardMapPHOTO};
/** Field type maps to vCard property ROLE.
@publishedAll

*/
const TUid KUidContactFieldVCardMapROLE={KIntContactFieldVCardMapROLE};
/** Field type maps to vCard property SOUND.
@publishedAll

*/
const TUid KUidContactFieldVCardMapSOUND={KIntContactFieldVCardMapSOUND};
/** Field type maps to vCard property TEL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapTEL={KIntContactFieldVCardMapTEL};
/** Field type maps to vCard property parameter FAX.
@publishedAll

*/
const TUid KUidContactFieldVCardMapTELFAX={KIntContactFieldVCardMapTELFAX};
/** Field type maps to vCard property TITLE.
@publishedAll

*/
const TUid KUidContactFieldVCardMapTITLE={KIntContactFieldVCardMapTITLE};
/** Field type maps to vCard property URL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapURL={KIntContactFieldVCardMapURL};
/** Field maps to the vCard property N (name). Must be used in conjunction with
a name-related field type (e.g. KUidContactFieldGivenName) to form the given
name field mapping.
@publishedAll

*/
const TUid KUidContactFieldVCardMapUnusedN={KIntContactFieldVCardMapUnusedN};
/** Field type maps to vCard property FN (the display name).
@publishedAll

*/
const TUid KUidContactFieldVCardMapUnusedFN={KIntContactFieldVCardMapUnusedFN};
/** Mapping between the vCard property and field type is not required.
@publishedAll

*/
const TUid KUidContactFieldVCardMapNotRequired={KIntContactFieldVCardMapNotRequired};
/** Unknown mapping between a field type and a vCard extension property.
@publishedAll

*/
const TUid KUidContactFieldVCardMapUnknownXDash={KIntContactFieldVCardMapUnknownXDash};
/** Unknown mapping between field type and non-extension vCard property.
@publishedAll

*/
const TUid KUidContactFieldVCardMapUnknown={KIntContactFieldVCardMapUnknown};
/** Field type maps to vCard property UID.
@publishedAll

*/
const TUid KUidContactFieldVCardMapUID={KIntContactFieldVCardMapUID};
/** Field type maps to vCard property parameter WORK.
@publishedAll

*/
const TUid KUidContactFieldVCardMapWORK={KIntContactFieldVCardMapWORK};
/** Field type maps to vCard property parameter HOME.
@publishedAll

*/
const TUid KUidContactFieldVCardMapHOME={KIntContactFieldVCardMapHOME};
/** Field type maps to vCard property parameter MSG.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMSG={KIntContactFieldVCardMapMSG};
/** Field type maps to vCard property parameter VOICE.
@publishedAll

*/
const TUid KUidContactFieldVCardMapVOICE={KIntContactFieldVCardMapVOICE};
/** Field type maps to vCard property parameter FAX.
@publishedAll

*/
const TUid KUidContactFieldVCardMapFAX={KIntContactFieldVCardMapFAX};
/** Field type maps to vCard property parameter PREF.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPREF={KIntContactFieldVCardMapPREF};
/** Field type maps to vCard property parameter CELL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapCELL={KIntContactFieldVCardMapCELL};
/** Field type maps to vCard property parameter PAGER.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPAGER={KIntContactFieldVCardMapPAGER};
/** Field type maps to vCard property parameter BBS.
@publishedAll

*/
const TUid KUidContactFieldVCardMapBBS={KIntContactFieldVCardMapBBS};
/** Field type maps to vCard property parameter MODEM.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMODEM={KIntContactFieldVCardMapMODEM};
/** Field type maps to vCard property parameter CAR.
@publishedAll

*/
const TUid KUidContactFieldVCardMapCAR={KIntContactFieldVCardMapCAR};
/** Field type maps to vCard property parameter ISDN.
@publishedAll

*/
const TUid KUidContactFieldVCardMapISDN={KIntContactFieldVCardMapISDN};
/** Field type maps to vCard property parameter VIDEO.
@publishedAll

*/
const TUid KUidContactFieldVCardMapVIDEO={KIntContactFieldVCardMapVIDEO};
/** Field type maps to vCard property parameter DOM.
@publishedAll

*/
const TUid KUidContactFieldVCardMapDOM={KIntContactFieldVCardMapDOM};
/** Field type maps to vCard property parameter INTL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapINTL={KIntContactFieldVCardMapINTL};
/** Field type maps to vCard property parameter POSTAL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPOSTAL={KIntContactFieldVCardMapPOSTAL};
/** Field type maps to vCard property parameter PARCEL.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPARCEL={KIntContactFieldVCardMapPARCEL};
/** Field type maps to vCard property parameter value GIF.
@publishedAll

*/
const TUid KUidContactFieldVCardMapGIF={KIntContactFieldVCardMapGIF};
/** Field type maps to vCard property parameter value CGM.
@publishedAll

*/
const TUid KUidContactFieldVCardMapCGM={KIntContactFieldVCardMapCGM};
/** Field type maps to vCard property parameter value WMF.
@publishedAll

*/
const TUid KUidContactFieldVCardMapWMF={KIntContactFieldVCardMapWMF};
/** Field type maps to vCard property parameter value BMP.
@publishedAll

*/
const TUid KUidContactFieldVCardMapBMP={KIntContactFieldVCardMapBMP};
/** Field type maps to vCard property parameter value MET.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMET={KIntContactFieldVCardMapMET};
/** Field type maps to vCard property parameter value PMB.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPMB={KIntContactFieldVCardMapPMB};
/** Field type maps to vCard property parameter value DIB.
@publishedAll

*/
const TUid KUidContactFieldVCardMapDIB={KIntContactFieldVCardMapDIB};
/** Field type maps to vCard property parameter value PICT.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPICT={KIntContactFieldVCardMapPICT};
/** Field type maps to vCard property parameter value TIFF.
@publishedAll

*/
const TUid KUidContactFieldVCardMapTIFF={KIntContactFieldVCardMapTIFF};
/** Field type maps to vCard property parameter value PDF.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPDF={KIntContactFieldVCardMapPDF};
/** Field type maps to vCard property parameter value PS.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPS={KIntContactFieldVCardMapPS};
/** Field type maps to vCard property parameter value JPEG.
@publishedAll

*/
const TUid KUidContactFieldVCardMapJPEG={KIntContactFieldVCardMapJPEG};
/** Field type maps to vCard property parameter value MPEG.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMPEG={KIntContactFieldVCardMapMPEG};
/** Field type maps to vCard property parameter value MPEG2.
@publishedAll

*/
const TUid KUidContactFieldVCardMapMPEG2={KIntContactFieldVCardMapMPEG2};
/** Field type maps to vCard property parameter value AVI.
@publishedAll

*/
const TUid KUidContactFieldVCardMapAVI={KIntContactFieldVCardMapAVI};
/** Field type maps to vCard property parameter value QTIME.
@publishedAll

*/
const TUid KUidContactFieldVCardMapQTIME={KIntContactFieldVCardMapQTIME};
/** Field type maps to vCard property TZ.
@publishedAll

*/
const TUid KUidContactFieldVCardMapTZ={KIntContactFieldVCardMapTZ};
/** Field type maps to vCard property KEY.
@publishedAll

*/
const TUid KUidContactFieldVCardMapKEY={KIntContactFieldVCardMapKEY};
/** Field type maps to vCard property parameter value X509.
@publishedAll

*/
const TUid KUidContactFieldVCardMapX509={KIntContactFieldVCardMapX509};
/** Field type maps to vCard property parameter value PGP.
@publishedAll

*/
const TUid KUidContactFieldVCardMapPGP={KIntContactFieldVCardMapPGP};
/** Used internally by the contacts model.
@publishedAll

*/
const TUid KUidContactFieldVCardMapSMIME={KIntContactFieldVCardMapSMIME};
/** The field contains a Wireless Village instant messaging ID.
@publishedAll

*/
const TUid KUidContactFieldVCardMapWV={KIntContactFieldVCardMapWV};
/** Field type mapping of a vCard property to contacts Second Name Field
@publishedAll

*/
const TUid KUidContactFieldVCardMapSECONDNAME={KIntContactFieldVCardMapSECONDNAME};
/** Field type mapping of a vCard property to contacts SIP Identity Field.
@publishedAll

*/
const TUid KUidContactFieldVCardMapSIPID={KIntContactFieldVCardMapSIPID};
/** Field type maps to vCard extension property parameter value POC
(Push to Talk Over Cellular).
@publishedAll

*/
const TUid KUidContactFieldVCardMapPOC={KIntContactFieldVCardMapPOC};
/** Field type maps to vCard extension property parameter value SWIS
("See What I See").
@publishedAll

*/
const TUid KUidContactFieldVCardMapSWIS={KIntContactFieldVCardMapSWIS};
/** Field type maps to vCard extension property parameter value VOIP
(Voice Over IP).
@publishedAll

*/
const TUid KUidContactFieldVCardMapVOIP={KIntContactFieldVCardMapVOIP};
/** Field type maps to vCard extension property parameter value Assistant
@publishedAll

*/
const TUid KUidContactFieldVCardMapAssistant={KIntContactFieldVCardMapAssistant};
/** Field type maps to vCard extension property parameter value AssistantTel
@publishedAll

*/
const TUid KUidContactFieldVCardMapAssistantTel={KIntContactFieldVCardMapAssistantTel};
/** Field type maps to vCard extension property parameter value Anniversary
@publishedAll

*/
const TUid KUidContactFieldVCardMapAnniversary={KIntContactFieldVCardMapAnniversary};
/** Field type maps to vCard extension property parameter value Spouse
@publishedAll

*/
const TUid KUidContactFieldVCardMapSpouse={KIntContactFieldVCardMapSpouse};
/** Field type maps to vCard extension property parameter value Children
@publishedAll

*/
const TUid KUidContactFieldVCardMapChildren={KIntContactFieldVCardMapChildren};
/** Field type maps to vCard extension property parameter value Class
@publishedAll

*/
const TUid KUidContactFieldVCardMapClass={KIntContactFieldVCardMapClass};
/** Field type maps to vCard extension property parameter value Department
@publishedAll

*/
const TUid KUidContactFieldVCardMapDepartment={KIntContactFieldVCardMapDepartment};

/** Name of the TYPE property parameter, for which the values are work, home etc. 
@publishedAll

*/
_LIT(KVersitParamType,"TYPE");
/** Name of the WORK property parameter.
@publishedAll

*/
_LIT(KVersitParamWork,"WORK");
/** Name of the HOME property parameter.
@publishedAll

*/
_LIT(KVersitParamHome,"HOME");
/** Name of the MSG property parameter.
@publishedAll

*/
_LIT(KVersitParamMsg,"MSG");
/** Name of the VOICE property parameter.
@publishedAll

*/
_LIT(KVersitParamVoice,"VOICE");
/** Name of the FAX property parameter.
@publishedAll

*/
_LIT(KVersitParamFax,"FAX");
/** Name of the PREF property parameter.
@publishedAll

*/
_LIT(KVersitParamPref,"PREF");
/** Name of the CELL property parameter.
@publishedAll

*/
_LIT(KVersitParamCell,"CELL");
/** Name of the PAGER property parameter.
@publishedAll

*/
_LIT(KVersitParamPager,"PAGER");
/** Name of the BBS property parameter.
@publishedAll

*/
_LIT(KVersitParamBbs,"BBS");
/** Name of the MODEM property parameter.
@publishedAll

*/
_LIT(KVersitParamModem,"MODEM");
/** Name of the CAR property parameter.
@publishedAll

*/
_LIT(KVersitParamCar,"CAR");
/** Name of the ISDN property parameter.
@publishedAll

*/
_LIT(KVersitParamIsdn,"ISDN");
/** Name of the VIDEO property parameter.
@publishedAll

*/
_LIT(KVersitParamVideo,"VIDEO");
/** Name of the DOM property parameter.
@publishedAll

*/
_LIT(KVersitParamDom,"DOM");
/** Name of the GIF property parameter.
@publishedAll

*/
_LIT(KVersitParamGif,"GIF");
/** Name of the CGM property parameter.
@publishedAll

*/
_LIT(KVersitParamCgm,"CGM");
/** Name of the WMF property parameter.
@publishedAll

*/
_LIT(KVersitParamWmf,"WMF");
/** Name of the BMP property parameter.
@publishedAll

*/
_LIT(KVersitParamBmp,"BMP");
/** Name of the MET property parameter.
@publishedAll

*/
_LIT(KVersitParamMet,"MET");
/** Name of the PMB property parameter.
@publishedAll

*/
_LIT(KVersitParamPmb,"PMB");
/** Name of the DIB property parameter.
@publishedAll

*/
_LIT(KVersitParamDib,"DIB");
/** Name of the PICT property parameter.
@publishedAll

*/
_LIT(KVersitParamPict,"PICT");
/** Name of the TIFF property parameter.
@publishedAll

*/
_LIT(KVersitParamTiff,"TIFF");
/** Name of the PDF property parameter.
@publishedAll

*/
_LIT(KVersitParamPdf,"PDF");
/** Name of the PS property parameter.
@publishedAll

*/
_LIT(KVersitParamPs,"PS");
/** Name of the JPEG property parameter.
@publishedAll

*/
_LIT(KVersitParamJpeg,"JPEG");
/** Name of the MPEG property parameter.
@publishedAll

*/
_LIT(KVersitParamMpeg,"MPEG");
/** Name of the MPEG2 property parameter.
@publishedAll

*/
_LIT(KVersitParamMpeg2,"MPEG2");
/** Name of the AVI property parameter.
@publishedAll

*/
_LIT(KVersitParamAvi,"AVI");
/** Name of the QTIME property parameter.
@publishedAll

*/
_LIT(KVersitParamQtime,"QTIME");
/** Name of the X509 property parameter.
@publishedAll

*/
_LIT(KVersitParamX509,"X509");
/** Name of the PGP property parameter.
@publishedAll

*/
_LIT(KVersitParamPGP,"PGP");

/** 8 bit name of the TYPE property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Type,"TYPE");
/** 8 bit name of the WORK property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Work,"WORK");
/** 8 bit name of the HOME property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Home,"HOME");
/** 8 bit name of the MSG property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Msg,"MSG");
/** 8 bit name of the VOICE property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Voice,"VOICE");
/** 8 bit name of the FAX property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Fax,"FAX");
/** 8 bit name of the PREF property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Pref,"PREF");
/** 8 bit name of the CELL property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Cell,"CELL");
/** 8 bit name of the PAGER property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Pager,"PAGER");
/** 8 bit name of the BBS property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Bbs,"BBS");
/** 8 bit name of the MODEM property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Modem,"MODEM");
/** 8 bit name of the CAR property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Car,"CAR");
/** 8 bit name of the ISDN property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Isdn,"ISDN");
/** 8 bit name of the VIDEO property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Video,"VIDEO");
/** 8 bit name of the DOM property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Dom,"DOM");
/** 8 bit name of the GIF property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Gif,"GIF");
/** 8 bit name of the CGM property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Cgm,"CGM");
/** 8 bit name of the WMF property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Wmf,"WMF");
/** 8 bit name of the BMP property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Bmp,"BMP");
/** 8 bit name of the MET property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Met,"MET");
/** 8 bit name of the PMB property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Pmb,"PMB");
/** 8 bit name of the DIB property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Dib,"DIB");
/** 8 bit name of the PICT property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Pict,"PICT");
/** 8 bit name of the TIFF property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Tiff,"TIFF");
/** 8 bit name of the PDF property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Pdf,"PDF");
/** 8 bit name of the PS property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Ps,"PS");
/** 8 bit name of the JPEG property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Jpeg,"JPEG");
/** 8 bit name of the MPEG property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Mpeg,"MPEG");
/** 8 bit name of the MPEG2 property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Mpeg2,"MPEG2");
/** 8 bit name of the AVI property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Avi,"AVI");
/** 8 bit name of the QTIME property parameter.
@publishedAll

*/
_LIT8(KVersitParam8Qtime,"QTIME");
/** 8 bit name of the X509 property parameter.
@publishedAll

*/
_LIT8(KVersitParam8X509,"X509");
/** 8 bit name of the PGP property parameter.
@publishedAll

*/
_LIT8(KVersitParam8PGP,"PGP");

/**
8 bit name of the X-IRMC-N property parameter (family or given
name pronunciation).
@publishedAll

*/
_LIT8(KVersitParam8NamePrn,"X-IRMC-N");
/**
8 bit name of the X-IRMC-ORG property parameter (company
name pronunciation).
@publishedAll

*/
_LIT8(KVersitParam8CompanyPrn,"X-IRMC-ORG");
/**
8 bit name of the X-IRMC- property parameter (pronunciation field prefix).
@publishedAll

*/
_LIT8(KVersitParam8PronunciationPrefix,"X-IRMC-");



class CContactIdArray : public CBase
/** Array of contact item IDs (TContactItemIds).

Instances of this class are used in several contact database functions,
for instance CContactDatabase::DeleteContactsL().
@publishedAll

*/
	{
public:
	IMPORT_C static CContactIdArray* NewL();
	IMPORT_C static CContactIdArray* NewLC();
	IMPORT_C static CContactIdArray* NewL(const CContactIdArray* aArray);
	IMPORT_C static CContactIdArray* NewLC(const CContactIdArray* aArray);
	static CContactIdArray* NewLC(RReadStream& aStream);
	IMPORT_C ~CContactIdArray();
	inline const TContactItemId& operator[](TInt aIndex) const;
	inline TContactItemId& operator[](TInt aIndex);
	inline TInt Count() const;
	inline void Reset();
	IMPORT_C TInt Find(TContactItemId aId) const;
	IMPORT_C void AddL(TContactItemId aId);

	inline void Remove(TInt aIndex);
	inline void Remove(TInt aIndex,TInt aCount);
	inline void InsertL(TInt aIndex,TContactItemId aId);
	IMPORT_C void MoveL(TInt aOldIndex,TInt aNewIndex);
	IMPORT_C void ReverseOrder();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:  // intended for internal Contacts Model usage only
	void Sort();
private:
	CContactIdArray();
	void ConstructL();
	void CloneL(const CContactIdArray* aArray);
private:
	CArrayFixFlat<TContactItemId> *iIds;
	};
inline const TContactItemId& CContactIdArray::operator[](TInt aIndex) const
/** Gets the indexed TContactItemId.

@param aIndex The position of the contact ID within the array, relative to zero.
This must be non-negative and less than the number of objects in the array
otherwise the operator raises a panic.
@return A reference to a const element of the array. */
	{ return (*iIds)[aIndex]; }

inline TContactItemId& CContactIdArray::operator[](TInt aIndex)
/** Gets the indexed TContactItemId.

@param aIndex The position of the contact ID within the array, relative to zero.
This must be non-negative and less than the number of objects in the array
otherwise the operator raises a panic.
@return A reference to a non-const element of the array. */
	{ return (*iIds)[aIndex]; }

inline TInt CContactIdArray::Count() const
/** Gets the number of contact IDs in the array.

@return The number of contact IDs in the array. */
	{ return iIds->Count(); }

inline void CContactIdArray::Reset()
/** Removes all contact IDs from the array. */
	{ iIds->Reset(); }

inline void CContactIdArray::Remove(TInt aIndex)
/** Removes the indexed contact ID from the array.

The index value must not be negative and must not be greater than the number
of elements in the array, otherwise the function raises a panic.

@param aIndex The index of the contact ID to remove. */
	{ iIds->Delete(aIndex); }

inline void CContactIdArray::Remove(TInt aIndex,TInt aCount)
/** Removes a block of contact IDs from the array.

This function raises a panic if any of the following are true:-

- aCount is negative

- aIndex is negative or is greater than the number of elements currently in
the array

- the sum of aIndex and aCount is greater than the number of elements currently
in the array

@param aIndex The index of the first contact ID to remove.
@param aCount The number of contiguous contact IDs to delete from the array.
If this is not specified, a value of one is assumed. */
	{ iIds->Delete(aIndex,aCount); }

inline void CContactIdArray::InsertL(TInt aIndex,TContactItemId aId)
/** Inserts a contact ID into the array.

The index must be valid or a panic occurs.

The function may attempt to expand the array buffer. If there is insufficient
memory available, the function leaves. The leave code is one of the system
error codes. If the function leaves, the array is left in the state it was
in before the call.

@param aIndex The index at which to insert the contact ID.
@param aId The contact ID to insert. */
	{ iIds->InsertL(aIndex,aId); }
	

/** Shows supported event action types that are used when deleting
a contact or an array of contacts
@internalTechnology

*/
enum TCntSendEventAction
	{
	EDeferEvent              = 0,
	ESendEvent               = 1,
	ESendUnknownChangesEvent = 2,
	};

#endif
