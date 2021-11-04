/*
* ==============================================================================
*  Name        : AknsLayeredBackgroundControlContext.h
*  Part of     : Avkon Skins / Skin Library
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Defines a concrete public class 
*                CAknsLayeredBackgroundControlContext.
*  Version     : ?Version
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef AKNSLAYEREDBACKGROUNDCONTROLCONTEXT_H
#define AKNSLAYEREDBACKGROUNDCONTROLCONTEXT_H

//  INCLUDES
#include <AknsBasicBackgroundControlContext.h>

// CLASS DECLARATION

/**
*  Implementation of a control context that provides one or more layered
*  backgrounds with their layout rectangles.
*
*  This is a public class with exported functions.
*  The class is not intended for derivation outside the library.
*
*  @lib AknSkins.lib
*
*  @since 2.0
*/
NONSHARABLE_CLASS(CAknsLayeredBackgroundControlContext) : 
    public CAknsBasicBackgroundControlContext
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        *
        * @since 2.0
        *
        * @param aImageID Item ID of the first background bitmap.
        *
        * @param aRect Rectangle where the first bitmap should be laid out.
        *
        * @param aParentAbsolute ETrue if parent absolute layout should be
        *   used, EFalse otherwise. If a parent absolute layout is used,
        *   the parent position must be set and updated using SetParentPos.
        *
        * @param aNumberOfLayers Total number of layers as an integer.
        *   This must be 1 or more.
        *
        * @return Newly constructed object.
        */
        IMPORT_C static CAknsLayeredBackgroundControlContext* NewL(
            const TAknsItemID& aImageID, const TRect& aRect, 
            const TBool aParentAbsolute, const TInt aNumberOfLayers );
        
        /**
        * Destructor.
        */
        virtual ~CAknsLayeredBackgroundControlContext();

    public: // New functions
        
        /**
        * Sets the item ID of the specified layer.
        *
        * @since 2.0
        *
        * @param aLayer Index of the layer, where 0 is the first one.
        *   The index must be less than aNumberOfLayers given to @c NewL().
        *
        * @param aID Item ID of the image.
        */
        IMPORT_C void SetLayerImage( const TInt aLayer, 
            const TAknsItemID& aID );

        /**
        * Sets the layout rectangle of the specified layer.
        *
        * @since 2.0
        *
        * @param aLayer Index of the layer, where 0 is the first one.
        *   The index must be less than aNumberOfLayers given to @c NewL().
        *
        * @param aRect Rectangle where the image should be laid out.
        */
        IMPORT_C void SetLayerRect( const TInt aLayer, 
            const TRect& aRect );

    public: // From MAknsControlContext

        /**
        * @copydoc MAknsControlContext::IsCompatibleWithType
        */
        TBool IsCompatibleWithType( const TAknsControlContextType aType ) const;

    protected:

        /**
        * C++ constructor.
        */
        CAknsLayeredBackgroundControlContext();

        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL( const TRect& aRect, const TBool aParentAbsolute,
            const TAknsItemID& aImageID, const TInt aNumberOfLayers );
    
    protected:  // Data
        
        /**
        * Array of layered layouts.
        */
        TAknsBackground* iLayoutArray;

        /**
        * Size of the layer array.
        */
        TInt iLayoutArraySize;

    };

#endif      // AKNSLAYEREDBACKGROUNDCONTROLCONTEXT_H
            
// End of File
