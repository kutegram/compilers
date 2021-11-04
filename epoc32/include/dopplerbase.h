/*
* ==============================================================================
*  Name        : DopplerBase.h
*  Part of     : Effects Framework
*  Description : This is the definition of the doppler effect class.
*
*  Version     : 1
*
*  Copyright © 2004 Nokia Corporation.
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

#ifndef CDOPPLER_H
#define CDOPPLER_H

// INCLUDES

#include <e32base.h>
#include <AudioEffectBase.h>
#include <DopplerData.h>
#include <MCustomInterface.h>

// CLASS DECLARATION

/**
*  This is the Doppler effect class for managing doppler settings.
*
*  @lib DopplerEffect.lib
*  @since 3.0
*/

class CDoppler : public CAudioEffect
	{

	protected:		// Constructor and Destructors

		/**
        *
        * Destructor
        */
		IMPORT_C virtual ~CDoppler();

		/**
		* Private C++ constructor for this class.
		*/
		IMPORT_C CDoppler();


    public: // New functions

		/**
        * Get the velocity's cartesian settings
        * @since 3.0
        * @param aX Velocity in X direction (mm/s)
        * @param aY Velocity in Y direction (mm/s)
        * @param aZ Velocity in Z direction (mm/s)
        */
		IMPORT_C void CartesianVelocity( TInt32& aX, TInt32& aY, TInt32& aZ );

		/**
        * Get the current multiplier factor
        * @since 3.0
        * @return multiplier factor
        */
		IMPORT_C TUint32 Factor() const;

		/**
        * Get the maximum multiplier factor
        * @since 3.0
        * @return multiplier factor
        */
		IMPORT_C TUint32 FactorMax() const;

		/**
        * Sets the velocity in Cartesian coordinates of the sound source with respect to the listener.
        * @since 3.0
        * @param aX Velocity in X direction (mm/s)
        * @param aY Velocity in Y direction (mm/s)
        * @param aZ Velocity in Z direction (mm/s)
        * @return -
        */
		IMPORT_C void SetCartesianVelocityL( TInt32 aX, TInt32 aY, TInt32 aZ );

		/**
        * Sets the multiplier factor.
        * @since 3.0
        * @param aFactor Factor value in hundredths that ranges from 0 to FactorMax(),
        *                where 100 corresponds to 1.00, 200 corresponds to 2.00, etc.
        * @return -
        */
		IMPORT_C void SetFactorL( TUint32 aFactor );

		/**
        * Sets the velocity in spherical coordinates of the sound source with respect to the listener.
        * @since 3.0
        * @param aAzimuth the Azimuth (thousandths of radians)
        * @param aElevation the elevation (thousandths of radians)
        * @param aRadius the radius (thousandths of radians)
        * @return -
        */
		IMPORT_C void SetSphericalVelocityL( TInt32 aAzimuth, TInt32 aElevation, TInt32 aRadius );

		/**
        * Gets the velocity's spherical coordinates settings.
        * @since 3.0
        * @param aAzimuth the Azimuth (thousandths of radians)
        * @param aElevation the elevation (thousandths of radians)
        * @param aRadius the radius (thousandths of radians)
        * @return -
        */
		IMPORT_C void SphericalVelocity( TInt32& aAzimuth, TInt32& aElevation, TInt32& aRadius );

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

		// Doppler data structure
		TEfDoppler iDopplerData;
		// Data package sent to server
		TEfDopplerDataPckg iDataPckgTo;
		// Data package received from server
		TEfDopplerDataPckg iDataPckgFrom;

	};

#endif	// of CDOPPLER_H

// End of File
