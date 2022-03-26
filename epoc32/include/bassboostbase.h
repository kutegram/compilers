/*
* ==============================================================================
*  Name        : BassBoostBase.h
*  Part of     : Effects Framework
*  Description : This is the definition of the Bass Boost effect class.
*  Version     : %version: 6 %
*
*  Copyright � 2006 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef BASSBOOSTBASE_H
#define BASSBOOSTBASE_H

// INCLUDES

#include <e32base.h>
#include <AudioEffectBase.h>
#include <BassBoostData.h>
#include <MCustomInterface.h>

const TUid KUidBassBoostEffect = {0x10203827};

// FORWARD DELCARATION
class CMdaAudioConvertUtility;
class CMdaAudioPlayerUtility;
class CMdaAudioRecorderUtility;
class CMdaAudioInputStream;
class CMdaAudioOutputStream;
class CMdaAudioToneUtility;
class CCustomCommandUtility;
class CCustomInterfaceUtility;
class CMMFDevSound;
class CMidiClientUtility;
class CDrmPlayerUtility;
class CVideoPlayerUtility;

// CLASS DECLARATION

/**
*  This is the bass boost effect class for managing audio bass boost settings.
*
*  @lib BassBoostUtility.lib
*  @since 3.0
*/

class CBassBoost : public CAudioEffect
	{

	public:		//New Functions

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aDevSound A reference to a DevSound instance
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMMFDevSound& aDevSound, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio convert utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioConvertUtility& aUtility, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio input stream utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioInputStream& aUtility, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio output stream utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioOutputStream& aUtility, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio player utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioPlayerUtility& aUtility, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio record utility
        * @param aRecordStream ETrue if the effect is to be applied to the recording,
        *                      EFalse if the effect is to be applied only to the playback
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioRecorderUtility& aUtility, TBool aRecordStream, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to an audio tone utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMdaAudioToneUtility& aUtility, TBool aEnable = EFalse );

	    /**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to a custom command utility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
        * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CCustomCommandUtility* aUtility, TBool aEnable = EFalse );

		/**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aCustomInterface A reference to a custom interface
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
         * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( MCustomInterface& aCustomInterface, TBool aEnable = EFalse );

		/**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param aUtility A reference to a CMidiClientUtility
        * @param aEnable Indicate whether the effect will be automatically enabled after creation.
         * @return pointer to CBassBoost object
        */
		IMPORT_C static CBassBoost* NewL( CMidiClientUtility& aUtility, TBool aEnable = EFalse );

		/**
        * Factory function for creating the bass boost object.
        * @since 3.0
        * @param CDrmPlayerUtility A reference to a CDrmPlayerUtility object
        * @return pointer to CBassBoost object
        */		
		IMPORT_C static CBassBoost* NewL( CDrmPlayerUtility& aUtility, TBool aEnable = EFalse );

		/**
        * Factory function for creating the bass boost object.
        * @since 3.2
        * @param CVideoPlayerUtility A reference to a CVideoPlayerUtility object
        * @return pointer to CBassBoost object
        */		
		IMPORT_C static CBassBoost* NewL( CVideoPlayerUtility& aUtility, TBool aEnable = EFalse );

		/**
        *
        * Destructor
        */
		IMPORT_C virtual ~CBassBoost();

	public: // functions from base class

		/*
		* From CAudioEffect
        * Get the unique identifier of the audio effect
        * @since 3.0
        * @return Unique identifier
        */
		IMPORT_C TUid Uid() const;

    protected:  // Functions from base classes

		/**
		* From CAudioEffect
		* Create a package of the effect data
        * @since 3.0
        * @return A descriptor containing the effect data.
        */
		IMPORT_C const TDesC8& DoEffectData();

		/**
		* From CAudioEffect
		* Internal function to unpack effect data
        * @since 3.0
        * @param aEffectDataBuffer Descriptor containing packed effect data
        * @return -
        */
        IMPORT_C void SetEffectData( const TDesC8& aEffectDataBuffer );

	protected:

		/**
		* Private C++ constructor for this class.
        * @since	3.0
        * @param	aEffectObserver	reference to event observer object
        * @return	-
        */
		IMPORT_C CBassBoost();

	protected:

		// BassBoost data structure
		TEfBassBoostData iBassBoostData;
		// Data package sent to server
		TEfBassBoostDataPckg iDataPckgTo;
		// Data package received from server
		TEfBassBoostDataPckg iDataPckgFrom;

    protected:    // Friend classes

		friend class CBassBoostMessageHandler;
	};

#endif	// of BASSBOOSTBASE_H

// End of File
