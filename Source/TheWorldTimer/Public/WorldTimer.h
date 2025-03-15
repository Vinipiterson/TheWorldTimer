// Copyright Vinipi 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorldTimer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTimerUpdatedSignature, float, ElapsedTime, float, RemainingTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerPausedSignature, bool, InPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimerNoParamSignature);

/**
 * The timer class, feel free to subclass it and modify according to your needs
 */
UCLASS(Blueprintable, BlueprintType)
class THEWORLDTIMER_API AWorldTimer : public AActor
{
	GENERATED_BODY()

	AWorldTimer();

protected:
	virtual void BeginPlay() override;

private:
#pragma region Billboard
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timer")
	TObjectPtr<UBillboardComponent> Billboard;

#pragma endregion Billboard

#pragma region Timer
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Timer")
	bool bStartWithTimerActive = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, ReplicatedUsing = "OnRep_TotalTime", Category = "Timer")
	float TotalTime = 30.f;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_TimeRemaining", Category = "Timer")
	float TimeRemaining = TotalTime;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = "OnRep_IsPaused", Category = "Timer")
	bool bIsPaused = bStartWithTimerActive;
	UPROPERTY(ReplicatedUsing = "OnRep_ResetHandler")
	bool bResetHandler = false; // Toggled when the timer gets reset

	UPROPERTY()
	FTimerHandle TimerHandle;
	
private:
	void InitializeTimer();

	void RefreshTimer();

public:	
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void SetTimerPaused(const bool bInPaused);
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void SetTotalTime(const float InTime, const bool bResetTimer, const bool bStartAutomaticallyOnReset);
	UFUNCTION(BlueprintCallable, Category = "Timer")
	void ResetTimer(const bool bStartAutomatically);
	
#pragma endregion Timer

#pragma region Delegates

public:	
	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FOnTimerUpdatedSignature OnTimerUpdated;
	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FOnTimerPausedSignature OnTimerPaused;
	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FTimerNoParamSignature OnTimerEnded;
	UPROPERTY(BlueprintAssignable, Category = "Timer")
	FTimerNoParamSignature OnTimerReset;
	
#pragma endregion Delegates

#pragma region Replication
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Rep notifies
	UFUNCTION()
	void OnRep_TotalTime() const;
	UFUNCTION()
	void OnRep_TimeRemaining() const;
	UFUNCTION()
	void OnRep_IsPaused() const;
	UFUNCTION()
	void OnRep_ResetHandler() const;
	
#pragma endregion Replication
};
