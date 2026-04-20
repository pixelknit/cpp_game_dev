// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "MyPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RWAY_CPP_DEV_API AMyPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
public:
	AMyPlayerCameraManager();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetTargetCamera(float InArmLength, float InFOV, float InInterpSpeed = 5.f);
	
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ResetTargetCamera();

	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultArmLength = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseFOV = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultInterpSpeed = 5.f;

private:
	float TargetArmLength;
	float CurrentArmLength;
	float TargetFOV;
	float CurrentFOV;
	float InterpSpeed;
};
