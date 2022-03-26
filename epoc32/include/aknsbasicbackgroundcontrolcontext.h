/*
* ==============================================================================
*  Name        : AknsBasicBackgroundControlContext.h
*  Part of     : Avkon Skins / Skin Library
*  Interface   : ?Interface_category, ?Interface_name
*  Description : Defines a public class CAknsBasicBackgroundControlContext.
*  Version     : ?Version
*
*  Copyright � 2002 Nokia Corporation.
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

#ifndef AKNSBASICBACKGROUNDCONTROLCONTEXT_H
#define AKNSBASICBACKGROUNDCONTROLCONTEXT_H

//  INCLUDES
#include <AknsControlContext.h>

// FORWARD DECLARATIONS
class TAknsBackground;

// CLASS DECLARATION

/**
*  Implementation of a control context that provides a layout background with
*  a background bitmap and its layout rectangle.
*
*  This is a public class with exported functions.
*  The class is not intended for derivation outside the library.
*
*  @lib AknSkins.lib
*
*  @since 2.0
*/
NONSHARABLE_CLASS(CAknsBasicBackgroundControlContext) : public CBase, 
    public MAknsControlContext
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        *
        * @since 2.0
        *
        * @param aImageID Item ID of the background bitmap.
        *
        * @param aRect Rectangle where the bitmap should be laid out.
        *
        * @param aParentAbsolute ETrue if parent absolute layout should be
        *   used, EFalse otherwise. If a parent absolute layout is used,
        *   the parent position must be set and updated using SetParentPos.
        *
        * @return Newly constructed object.
        */
        IMPORT_C static CAknsBasicBackgroundControlContext* NewL(
            const TAknsItemID& aImageID, const TRect& aRect, 
            TBool aParentAbsolute );
        
        /**
        * Destructor.
        */
        virtual ~CAknsBasicBackgroundControlContext();

    public: // New functions
        
        /**
        * Sets the item ID of the background bitmap.
        *
        * @since 2.0
        *
        * @param aID Item ID of the bitmap.
        */
        IMPORT_C void SetBitmap( const TAknsItemID& aID );

        /**
        * Sets the layout rectangle of the bitmap.
        *
        * @since 2.0
        *
        * @param aRect Rectangle where the bitmap should be laid out.
        */
        IMPORT_C void SetRect( const TRect& aRect );

        /**
        * Sets the parent position for the layout. This is only
        * used if parent absolute layout was enabled during construction.
        *
        * @since 2.0
        *
        * @param aPos Parent position in screen relative coordinates.
        */
        IMPORT_C void SetParentPos( const TPoint& aPos );

        /**
        * Sets the parent context (drawn beneath the context itself).
        * No ownership is claimed. The parent context object must be
        * valid as long as it is set as parent context.
        *
        * @since 2.6
        *
        * @param aParentContext Pointer to the parent context, or
        *   @c NULL (default value) if none used.
        */
        IMPORT_C void SetParentContext( MAknsControlContext* aParentContext );

    public: // Functions from MAknsControlContext
        
        /**
        * @copydoc MAknsControlContext::SupplySkinParameter
        */
        TInt SupplySkinParameter( TAknsCCParameter aParam );

        /**
        * @copydoc MAknsControlContext::SupplySkinObject
        */
        TAny* SupplySkinObject( TAknsCCObject aObject );

        /**
        * @copydoc MAknsControlContext::IsCompatibleWithType
        */
        TBool IsCompatibleWithType( const TAknsControlContextType aType ) const;
        
    protected:

        /**
        * C++ constructor.
        */
        CAknsBasicBackgroundControlContext();

        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL( const TRect& aRect, TBool aParentAbsolute,
            const TAknsItemID& aImageID );
    
    protected:  // Data
        
        TAknsBackground* iLayout; //<! Background layout structure.
        MAknsControlContext* iParentContext; //<! Parent context (not owned).

    };

#endif      // AKNSBASICBACKGROUNDCONTROLCONTEXT_H
            
// End of File
