// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorAnimation.h"
#include "MyGameInstance.h"

UDoorAnimation::UDoorAnimation()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UDoorAnimation::OpenDoor()
{
	if (bIsOpen) return;

	TargetPositions.Empty();
	for (int32 i = 0; i < DoorMeshes.Num(); ++i)
	{
		const FDoorMeshConfig& Config = DoorMeshes[i];
		if (Config.MeshComponent && OriginalPositions.IsValidIndex(i))
		{
			FVector WorldOffset = GetDirectionVector(Config) * Config.MoveDistance;
			FVector LocalOffset = GetOwner()->GetActorTransform().InverseTransformVector(WorldOffset);
			TargetPositions.Add(OriginalPositions[i] + LocalOffset);
		}

		else
		{
			TargetPositions.Add(FVector::ZeroVector);
		}
	}
	bIsOpen = true;
	bIsMoving = true;
	SetComponentTickEnabled(true);
}

void UDoorAnimation::CloseDoor()
{
	if (!bIsOpen) return;

	TargetPositions.Empty();

	for (int32 i = 0; i < DoorMeshes.Num(); ++i)
	{
		TargetPositions.Add(OriginalPositions.IsValidIndex(i) ? OriginalPositions[i] : FVector::ZeroVector);
	}

	bIsOpen = false;
	bIsMoving = true;
	SetComponentTickEnabled(true);
}

void UDoorAnimation::ToggleDoor()
{
	bIsOpen ? CloseDoor() : OpenDoor();
}

void UDoorAnimation::UnlockDoor()
{
	bIsLocked = false;
}

void UDoorAnimation::BeginPlay()
{
	Super::BeginPlay();
	CacheOriginalPositions();

	if (TriggerBox)
	{ 
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UDoorAnimation::OnTriggerBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &UDoorAnimation::OnTriggerEndOverlap);
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DoorAnimation: No Trigger Box Assigned"));
	}

	
}


void UDoorAnimation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!bIsMoving) return;

	bool bStillMoving = false;
	for (int32 i = 0; i < DoorMeshes.Num(); ++i)
	{
		const FDoorMeshConfig& Config = DoorMeshes[i];
		if (!Config.MeshComponent || !TargetPositions.IsValidIndex(i)) continue;

		FVector Current = Config.MeshComponent->GetRelativeLocation();
		FVector Target = TargetPositions[i];

		if (!Current.Equals(Target, 0.5f))
		{
			Config.MeshComponent->SetRelativeLocation(FMath::VInterpConstantTo(Current, Target, DeltaTime, Config.MoveSpeed));
			bStillMoving = true;
		}
		else
		{
			Config.MeshComponent->SetRelativeLocation(Target);
		}

	}

	if (!bStillMoving)
	{
		bIsMoving = false;
		SetComponentTickEnabled(false);
		OnDoorMoveComplete.Broadcast(bIsOpen);
	}
}

void UDoorAnimation::CacheOriginalPositions()
{
	OriginalPositions.Empty();
	for (const FDoorMeshConfig& Config : DoorMeshes)
	{
		if (Config.MeshComponent)
			OriginalPositions.Add(Config.MeshComponent->GetRelativeLocation());
		else
			OriginalPositions.Add(FVector::ZeroVector);
	}
}

FVector UDoorAnimation::GetDirectionVector(const FDoorMeshConfig& Config) const
{
	AActor* Owner = GetOwner();
	if (!Owner) return FVector::ZeroVector;

	switch (Config.MoveDirection)
	{
	case EDoorMoveDirection::Right:		return Owner->GetActorRightVector();
	case EDoorMoveDirection::Left:		return -Owner->GetActorRightVector();
	case EDoorMoveDirection::Up:		return Owner->GetActorUpVector();
	case EDoorMoveDirection::Down:		return -Owner->GetActorUpVector();
	case EDoorMoveDirection::Forward:	return Owner->GetActorForwardVector();
	case EDoorMoveDirection::Backward:	return -Owner->GetActorForwardVector();
	default:							return FVector::ZeroVector;
	}
}

void UDoorAnimation::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		//UE_LOG(LogTemp, Warning, TEXT("The door should be opening!"));
		UMyGameInstance* GI = Cast<UMyGameInstance>(
			GetWorld()->GetGameInstance()
		);

		if (GI && GI->bHasKey)
		{
			OpenDoor();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("You need the main gate key!"));
		}
	}
}

void UDoorAnimation::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		CloseDoor();
	}
}

