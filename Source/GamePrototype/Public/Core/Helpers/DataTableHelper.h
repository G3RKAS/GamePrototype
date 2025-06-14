// (c) G3RKA. Game Prototype

#pragma once

#include "CoreMinimal.h"

class GAMEPROTOTYPE_API FDataTableHelper
{
public:
	template <typename T>
	static T* FindRow(const UDataTable* InDataTable, const FName& InRowName)
	{
		check(InDataTable);
		return InDataTable->FindRow<T>(InRowName, ContextString, true);
	}

private:
	static const FString ContextString;
};