// Copyright Vinipi 2025. All Rights Reserved.


#include "WorldTimerFunctionLibrary.h"

#include "WorldTimer.h"
#include "Kismet/GameplayStatics.h"

AWorldTimer* UWorldTimerFunctionLibrary::GetWorldTimer(const UObject* WorldContextObject)
{
	AWorldTimer* Timer = Cast<AWorldTimer>(UGameplayStatics::GetActorOfClass(WorldContextObject, AWorldTimer::StaticClass()));
	if (IsValid(Timer))
		return Timer;

	UKismetSystemLibrary::PrintString(WorldContextObject, "World Timer not found, make sure you have added a timer to your level before trying to use it.", true, true, FLinearColor::Red);
	return nullptr;
}
