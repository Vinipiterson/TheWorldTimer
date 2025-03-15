// Copyright Vinipi 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "WorldTimerFunctionLibrary.generated.h"

class AWorldTimer;
/**
 * Helpfull functions when using the timer
 */
UCLASS()
class THEWORLDTIMER_API UWorldTimerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (WorldContext="WorldContextObject", CallableWithoutWorldContext, Category = "World Timer"))
	static AWorldTimer* GetWorldTimer(const UObject* WorldContextObject);
};
