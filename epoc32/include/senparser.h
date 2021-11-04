/*
* ==============================================================================
*  Name        : SenParser.h
*  Part of     : Web Services Fragment
*  Interface   : 
*  Description : This is an abstract interface enabling factory pattern
*  Version     : 
*
*  Copyright © 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef SEN_PARSER_H
#define SEN_PARSER_H

#include <Xml/ContentHandler.h>
#include <Xml/Parser.h>

using namespace Xml;

// FORWARD DECLARATIONS
class CSenContentHandler;
class CSenFragmentBase;

class CSenParser : public CBase
    {
    public: // Constructors and destructor

        /**
         *  Standard 2 phase constructor.
         *  
         */
        IMPORT_C static CSenParser* NewL();
        /**
         *  Standard 2 phase constructor.
         *  
         */       
        IMPORT_C static CSenParser* NewLC();

        /**
         *  Standard 2 phase constructor.
         *  @param aParser : where construction 
         *                  data will be copied from.         
         *  
         */
        IMPORT_C static CSenParser* NewL(CParser* aParser);
        /**
         *  Standard 2 phase constructor.
         *  @param aParser : where construction 
         *                  data will be copied from.         
         *  
         */        
        IMPORT_C static CSenParser* NewLC(CParser* aParser);

        /**
         *  Standard 2 phase constructor.
         *  @param aParserMimeType : where construction 
         *                  data will be copied from.         
         *  
         */
        IMPORT_C static CSenParser* NewL(const TDesC8& aParserMimeType);
        /**
         *  Standard 2 phase constructor.
         *  @param aParserMimeType : where construction 
         *                  data will be copied from.         
         *  
         */        
        IMPORT_C static CSenParser* NewLC(const TDesC8& aParserMimeType);

		/**
		 * Sets the ContentHandler
		 * @param aContentHandler
		 */	
        virtual void SetContentHandler(CSenFragmentBase& aContentHandler) = 0;

		/**
		 * Parsing Begins
		 */
        virtual void ParseBeginL() = 0;
        /**
         * Parsing Begins
         * @param aDocumentMimeType This contains the Mime Type
         */
        virtual void ParseBeginL(const TDesC8& aDocumentMimeType) = 0;

		/**
		 * Parsing
		 * @param aFragment
		 * @param aContentHandler
		 */
        virtual void ParseL(const TDesC8& aFragment,
                                CSenFragmentBase& aContentHandler) = 0;
		/**
		 * Parsing
		 * @param aFs
		 * @param aFilename
		 * @param aContentHandler
		 */                                
        virtual void ParseL(RFs& aFs, const TDesC& aFilename,
                                 CSenFragmentBase& aContentHandler) = 0;
		/**
		 * Parsing
		 * @param aFs
		 * @param aContentHandler
		 */                                                                 
        virtual void ParseL(RFile& aFile, CSenFragmentBase& aContentHandler) = 0;
        
        /**
         * Parsing Ends
         */
        virtual void ParseEndL() = 0;

		/**
		 * Sets the Processor Chain
		 */
        virtual void SetProcessorChainL(const RContentProcessorUids& aPlugins) = 0;

		/**
		 * Enables the Parsing Feature 
		 */
        virtual TInt EnableFeature(TInt aParserFeature) = 0;
   		/**
		 * Disables the Parsing Feature 
		 */
        virtual TInt DisableFeature(TInt aParserFeature) = 0;
        /**
         * @param aParserFeature
         * @return True if parser feature is enabled
         *		   False if parser feature is disabled
         */
        virtual TBool IsFeatureEnabled(TInt aParserFeature) const = 0;
		/**
		 * 
		 */
        virtual void AddPreloadedDictionaryL(const TDesC8& aPublicId) = 0;

		/**
		 * 
		 */
        virtual RStringPool& StringPool() = 0;
        /**
         * 
         */
        virtual RStringDictionaryCollection& StringDictionaryCollection() = 0;
        
    protected:
        CSenParser();
    };


//SEN_PARSER_H
#endif

// End of File
