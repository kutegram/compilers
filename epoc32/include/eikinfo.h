// EIKINFO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKINFO_H__)
#define __EIKINFO_H__

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

#include <aknnotedialog.h>

/**
 * Eikon info dialog, contains a title, message and Yes/No buttons.
 */
class CEikInfoDialog : public CAknNoteDialog, public MEikInfoDialog
	{
	
public:
	/**
	 * Left here for backwards compatibility.
	 * Not used anymore.
     * 
    */
	enum TExitKeys
		{
		EAllowEnter,
		EIgnoreEnter
		};
public:
    /**
    * Constructor.
    */
	IMPORT_C CEikInfoDialog(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys=EAllowEnter);
	
	/**
    * Constructor.
    */
	CEikInfoDialog(TExitKeys aExitKeys=EAllowEnter);
	
	/**
     * Sets title and message and calls ExecuteLD for the dialog.
    */
	IMPORT_C static TBool RunDlgLD(const TDesC& aTitle,const TDesC& aMsg,TExitKeys aExitKeys=EAllowEnter);
          
    /**
     * Handles pointer events.
    */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
    
private: // from MEikInfoDialog
	TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg);
	
private:
	void PreLayoutDynInitL();
	
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
    
private:
	IMPORT_C virtual void CEikDialog_Reserved_1();
	IMPORT_C virtual void CEikDialog_Reserved_2();
	
private:
	const TDesC* iTitle;
	const TDesC* iMessage;
	};

#endif
