// Copyright Vinipi 2025. All Rights Reserved.

#include "WorldTimer.h"

#include "Components/BillboardComponent.h"
#include "Net/UnrealNetwork.h"

AWorldTimer::AWorldTimer()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetupAttachment(GetRootComponent());
}

void AWorldTimer::BeginPlay()
{
	Super::BeginPlay();

	InitializeTimer();
}

#pragma region Timer

void AWorldTimer::InitializeTimer()
{
	if (GetLocalRole() < ROLE_Authority) // Only run on server
		return;

	TimeRemaining = TotalTime;
	OnRep_TimeRemaining();
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	
	TimerManager.SetTimer(TimerHandle, this, &ThisClass::RefreshTimer, 1.f, true);
	SetTimerPaused(!bStartWithTimerActive);
}

void AWorldTimer::RefreshTimer()
{
	TimeRemaining--;

	if (TimeRemaining <= 0)
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.PauseTimer(TimerHandle);
	}

	OnRep_TimeRemaining();
}

void AWorldTimer::SetTimerPaused(const bool bInPaused)
{
	if (GetLocalRole() < ROLE_Authority)
		return;
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (bInPaused)
		TimerManager.PauseTimer(TimerHandle);
	else
		TimerManager.UnPauseTimer(TimerHandle);

	bIsPaused = bInPaused;
	OnRep_IsPaused();
}

void AWorldTimer::SetTotalTime(const float InTime, const bool bResetTimer, const bool bStartAutomaticallyOnReset)
{
	if (GetLocalRole() < ROLE_Authority) // Only run on server
		return;

	TotalTime = InTime;
	OnRep_TotalTime();

	if (bResetTimer)
		ResetTimer(bStartAutomaticallyOnReset);
}

void AWorldTimer::ResetTimer(const bool bStartAutomatically)
{
	if (GetLocalRole() < ROLE_Authority) // Only run on server
		return;
	
	TimeRemaining = TotalTime;
	OnRep_TimeRemaining();
	SetTimerPaused(!bStartAutomatically);

	bResetHandler = !bResetHandler;
	OnRep_ResetHandler();
}

#pragma endregion Timer

#pragma region Replication

void AWorldTimer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ThisClass, TotalTime, COND_None)
	DOREPLIFETIME_CONDITION(ThisClass, TimeRemaining, COND_None)
	DOREPLIFETIME_CONDITION(ThisClass, bIsPaused, COND_None)
	DOREPLIFETIME_CONDITION(ThisClass, bResetHandler, COND_None)
}

void AWorldTimer::OnRep_TotalTime() const
{
	OnTimerUpdated.Broadcast(TotalTime - TimeRemaining, TimeRemaining);
}

void AWorldTimer::OnRep_TimeRemaining() const
{
	OnTimerUpdated.Broadcast(TotalTime - TimeRemaining, TimeRemaining);

	if (TimeRemaining <= 0)
	{
		OnTimerEnded.Broadcast();
	}
}

void AWorldTimer::OnRep_IsPaused() const
{
	OnTimerPaused.Broadcast(bIsPaused);
}

void AWorldTimer::OnRep_ResetHandler() const
{
	OnTimerReset.Broadcast();
}

#pragma endregion Replication