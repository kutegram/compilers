/*
* ============================================================================
*  Name     : AknQueryData.h
*  Part of  : Avkon
*
*  Description:
*   Implementation of Query data classes for query dialogs
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef AKNQUERYDATA_H
#define AKNQUERYDATA_H

#include <e32std.h>
#include <aknquerycontrol.h>
#include <in_sock.h>
#include <lbsposition.h>

class CAknQueryDialog;
class TInetAddr;


IMPORT_C TInt GetMaxTextLength(const CAknQueryControl* aControl, const TDes& aDataText, TInt aApiValue);

class MAknQueryData
    {
    public:
        virtual void SetL(CAknQueryControl* aControl, TInt aMaxLength) = 0;
        virtual void Get(CAknQueryControl* aControl) = 0;
    };

template<class T>
class TAknQueryData : public MAknQueryData
    {
    public:
        TAknQueryData(T& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl, TInt aMaxLength);
        void Get(CAknQueryControl* aControl);

    public:
        T& iData;
    };

template<>
class TAknQueryData<TDes> : public MAknQueryData
    {
    public:
        TAknQueryData(TDes& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl,TInt aMaxLength)
            { aControl->SetTextL(iData); 
              aControl->SetTextEntryLength(
                  GetMaxTextLength(aControl,iData,aMaxLength)); }
        void Get(CAknQueryControl* aControl) 
            { aControl->GetText(iData); }
    public:
        TDes& iData;
    };

template<>
class TAknQueryData<TInt> : public MAknQueryData
    {
    public:
        TAknQueryData(TInt& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
            { aControl->SetNumberL(iData); }
        void Get(CAknQueryControl* aControl) 
            { iData=aControl->GetNumber(); }
    public:
        TInt& iData;
    };

template<>
class TAknQueryData<TTime> : public MAknQueryData
    {
    public:
        TAknQueryData(TTime& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
            { aControl->SetTime(iData); }
        void Get(CAknQueryControl* aControl) 
            { iData=aControl->GetTime(); }
    public:
        TTime& iData;
    };

template<>
class TAknQueryData<TTimeIntervalSeconds> : public MAknQueryData
    {
    public:
        TAknQueryData(TTimeIntervalSeconds& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
            { aControl->SetDuration(iData); }
        void Get(CAknQueryControl* aControl) 
            { iData=aControl->GetDuration(); }
    public:
        TTimeIntervalSeconds& iData;
    };

template<>
class TAknQueryData<TReal> : public MAknQueryData
    {
    public:
        TAknQueryData(TReal& aData) : iData(aData) {}

        void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
            { aControl->SetFloatingPointNumberL(&iData); }
        void Get(CAknQueryControl* aControl) 
            { iData=aControl->GetFloatingPointNumberL(); }
    public:
        TReal& iData;
    };


template<>  
class TAknQueryData<TInetAddr> : public MAknQueryData
    {
    public:
        TAknQueryData(TInetAddr& aData) : iData(aData) {}
        void SetL(CAknQueryControl* aControl,TInt /*aMaxLength*/)
            {
                CAknExtQueryControl* control = STATIC_CAST(CAknExtQueryControl*,aControl);
                control->SetInetAddress(iData);
            }
        void Get(CAknQueryControl* aControl) 
            {
                CAknExtQueryControl* control = STATIC_CAST(CAknExtQueryControl*,aControl);
                iData=control->GetInetAddress();
            }

    public:
        TInetAddr& iData;
    };
template<>    
class TAknQueryData<TPosition> : public MAknQueryData
	{
public:
	TAknQueryData(TPosition &aData) : iData(aData) {}
	void SetL(CAknQueryControl* aControl, TInt /*aMaxLength*/)
		{
		aControl->SetLocation(iData);
		}
	void Get(CAknQueryControl* aControl)
		{
		aControl->GetLocation(iData);
		}
private:
	TPosition& iData;
	};

#endif
