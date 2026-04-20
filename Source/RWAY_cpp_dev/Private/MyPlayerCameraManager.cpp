// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"
#include "GameFramework/PlayerController.h"

AMyPlayerCameraManager::AMyPlayerCameraManager()
{
	CurrentArmLength = DefaultArmLength;
	TargetArmLength = DefaultArmLength;

	CurrentFOV = DefaultFOV;
	TargetFOV = DefaultFOV;

	InterpSpeed = DefaultInterpSpeed;
}

void AMyPlayerCameraManager::SetTargetCamera(float InArmLength, float InFOV, float InInterpSpeed)
{
	TargetArmLength = InArmLength;
	TargetFOV = InFOV;
	if (InInterpSpeed > 0.f) InterpSpeed = InInterpSpeed;
}

void AMyPlayerCameraManager::ResetTargetCamera()
{
	TargetArmLength = DefaultArmLength;
	TargetFOV = DefaultFOV;
	InterpSpeed = DefaultInterpSpeed;
}

void AMyPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);

	CurrentArmLength = FMath::FInterpTo(CurrentArmLength, TargetArmLength, DeltaTime, InterpSpeed);
	CurrentFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, InterpSpeed);

	float DeltaLength = CurrentArmLength - DefaultArmLength;
	FVector Forward = OutVT.POV.Rotation.Vector();

	OutVT.POV.Location -= Forward * DeltaLength;
	OutVT.POV.FOV = CurrentFOV;
}
