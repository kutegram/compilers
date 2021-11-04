// CRuleMarkedStack.inl
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//


// note: MergeToMark is not atomic - a leave means that data has been removed
template <TBool StackOwnsEntry>
inline void CRuleMarkedStack<StackOwnsEntry>::MergeToMarkL(TInt aMarkType)
	{
	const TInt lastMark=this->RemoveMark(aMarkType);
	if (this->Count()>lastMark)
		{
		CBNFNode* currentRule=this->Pop();
		if (StackOwnsEntry)
			CleanupStack::PushL(currentRule);
			
		while (this->Count()>lastMark)
			{
			CBNFNode* nextRule=this->Pop();
			if (StackOwnsEntry)
				CleanupStack::PushL(nextRule);
			currentRule->ReparentL(nextRule);
			if (StackOwnsEntry)
				{
				CleanupStack::Pop(2); // nextRule, currentRule
				CleanupStack::PushL(nextRule); // nextRule
				}
			
			currentRule=nextRule;
			}

		if (StackOwnsEntry)
			CleanupStack::Pop(); // currentRule
		this->PushL(currentRule);
		}
	}
