// SqlRowSetUtil.h
//
// Copyright (c) 2006 Symbian Software Ltd. All rights reserved.
//
#ifndef __SQLROWSETUTIL_H__
#define __SQLROWSETUTIL_H__

#include <sqldb.h>

/**
TSqlRowSetUtil provides exported functions, used by the DBMS emulation library.

@internalTechnology
*/
class TSqlRowSetUtil
	{
public:		
	//Database
	IMPORT_C static TInt CreateDb(RSqlDatabase& aDb, const TDesC& aDbName, const TDesC8* aConfig = NULL);
	IMPORT_C static TInt OpenDb(RSqlDatabase& aDb, const TDesC& aDbName, const TDesC8* aConfig = NULL);
	IMPORT_C static TInt Exec(RSqlDatabase& aDb, const TDesC& aSqlStmt, TInt64& aLastInsertedRowId);
	//ROWIDs statement
	IMPORT_C static TInt EvaluateAll(RSqlStatement& aStmt, RArray<TInt64>& aRowIds);
	//SQL Statements
	IMPORT_C static HBufC* GetDeclColumnTypesL(RSqlStatement& aStmt);
	IMPORT_C static const TDesC8& ColumnNamesL(RSqlStatement& aStmt);
	IMPORT_C static const TDesC8& ColumnValuesL(RSqlStatement& aStmt, TInt64 aRowId);
	IMPORT_C static const TDesC8& ColumnValues(RSqlStatement& aStmt);
	IMPORT_C static TInt GetColumnValue(RSqlStatement& aStmt, TInt aColumnIndex, TDes8& aDest);
	IMPORT_C static MStreamBuf* ColumnSourceL(const RSqlStatement& aStmt, TInt aColumnIndex);
	IMPORT_C static TInt BindText8(RSqlStatement& aStmt, TInt aColumnIndex, const TDesC8& aText8);
	IMPORT_C static TInt Insert(RSqlStatement& aStmt, TInt64& aLastInsertedRowId);
	IMPORT_C static TInt Update(RSqlStatement& aStmt);

private:
	static TInt DoNewDb(RSqlDatabase& aDb, const TDesC& aDbName, const TDesC8* aConfig, TBool aCreate);
	
	};

#endif//__SQLROWSETUTIL_H__
