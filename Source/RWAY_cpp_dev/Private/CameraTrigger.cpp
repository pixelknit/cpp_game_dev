// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerCameraManager.h"

// Sets default values
ACameraTrigger::ACameraTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn && Pawn->IsPlayerControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("The player is in the bounds of the camera trigger"));
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());

		if (PC && PC->PlayerCameraManager)
		{
			AMyPlayerCameraManager* CamMgr = Cast<AMyPlayerCameraManager>(PC->PlayerCameraManager);
			if (CamMgr)
			{
				UE_LOG(LogTemp, Warning, TEXT("A camera manger exists"));
				CamMgr->SetTargetCamera(TargetArmLength, TargetFOV, InterpSpeed);

			}
		}

	}
}

void ACameraTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn && Pawn->IsPlayerControlled())
	{
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		if (PC && PC->PlayerCameraManager)
		{
			AMyPlayerCameraManager* CamMgr = Cast<AMyPlayerCameraManager>(PC->PlayerCameraManager);
			if (CamMgr)
			{
				CamMgr->ResetTargetCamera();

			}
		}

	}


}


