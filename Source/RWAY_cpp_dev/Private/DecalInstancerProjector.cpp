// Fill out your copyright notice in the Description page of Project Settings.


#include "DecalInstancerProjector.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "Engine/OverlapResult.h"

// Sets default values
ADecalInstancerProjector::ADecalInstancerProjector()
{
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	
	ProjectorBox = CreateDefaultSubobject<UBoxComponent>("ProjectorBox");
	ProjectorBox->SetupAttachment(RootComponent);
	ProjectorBox->SetBoxExtent(FVector(200.0f, 200.0f, 200.0f));
	ProjectorBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectorBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectorBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	ProjectorBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectorBox->SetGenerateOverlapEvents(true);
	
	SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void ADecalInstancerProjector::BeginPlay()
{
	Super::BeginPlay();
	
}

#if WITH_EDITOR
void ADecalInstancerProjector::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	FName PropertyName = PropertyChangedEvent.Property->GetFName();
	
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, ActorToSpawn) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, SpawnDensity) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, ScaleRange) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, RotationRange) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, SurfaceOffset) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, IntersectionBias) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(ADecalInstancerProjector, MinSpawnDistance)
		)
	{
		ClearSpawnedActors();
		SpawnActors();
	}
	
}

void ADecalInstancerProjector::PostEditMove(bool bFinished)
{
	Super::PostEditMove(bFinished);
	if (bFinished && bAutoUpdateOnEditor)
	{
		ClearSpawnedActors();
		SpawnActors();
	}
}
#endif

void ADecalInstancerProjector::SpawnActors()
{
	if (!ActorToSpawn)
    {
        UE_LOG(LogTemp, Warning, TEXT("DecalInstanceProjector: No ActorToSpawn or StaticMeshToSpawn set!"));
        return;
    }
    
    ClearSpawnedActors();
    
    TArray<FOverlapResult> OverlapResults;
    FCollisionShape BoxShape = FCollisionShape::MakeBox(ProjectorBox->GetScaledBoxExtent());
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    
    GetWorld()->OverlapMultiByChannel(
        OverlapResults,
        ProjectorBox->GetComponentLocation(),
        ProjectorBox->GetComponentQuat(),
        ECC_WorldStatic,
        BoxShape,
        QueryParams
    );
    
    TArray<AActor*> OverlappingActors;
    for (const FOverlapResult& Result : OverlapResults)
    {
        if (Result.GetActor() && !OverlappingActors.Contains(Result.GetActor()))
        {
            OverlappingActors.Add(Result.GetActor());
        }
    }
    
    if (OverlappingActors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("DecalInstanceProjector: No overlapping actors found! Make sure your cubes have collision enabled."));
        return;
    }
    
    UE_LOG(LogTemp, Log, TEXT("DecalInstanceProjector: Found %d overlapping actors"), OverlappingActors.Num());
    
    FVector BoxExtent = ProjectorBox->GetScaledBoxExtent();
    FVector BoxCenter = ProjectorBox->GetComponentLocation();
    FRotator BoxRotation = ProjectorBox->GetComponentRotation();
    
    for (int32 i = 0; i < SpawnDensity; i++)
    {
        FVector LocalPos = FVector(
            FMath::RandRange(-BoxExtent.X, BoxExtent.X),
            FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
            FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
        );
        
        FVector WorldPos = BoxCenter + BoxRotation.RotateVector(LocalPos);
        float Complexity = CalculateGeometryComplexity(WorldPos, OverlappingActors);
        
        float SpawnChance = FMath::Lerp(1.0f, Complexity, IntersectionBias);
        if (FMath::FRand() > SpawnChance)
        {
            continue;
        }
        
        FHitResult Hit;
        FVector StartTrace = WorldPos + FVector(0, 0, BoxExtent.Z);
        FVector EndTrace = WorldPos - FVector(0, 0, BoxExtent.Z * 2);
        
        FCollisionQueryParams QueryParamsIn;
        QueryParamsIn.AddIgnoredActor(this);
        for (AActor* SpawnedActor : SpawnedActors)
        {
            QueryParamsIn.AddIgnoredActor(SpawnedActor);
        }
        
        if (GetWorld()->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, ECC_Visibility, QueryParamsIn))
        {
            FVector SpawnLocation = Hit.Location + Hit.Normal * SurfaceOffset;
            
            if (!IsValidSpawnLocation(SpawnLocation))
            {
                continue;
            }
            
            FRotator SpawnRotation = FRotator(
                FMath::RandRange(-RotationRange.X, RotationRange.X),
                FMath::RandRange(-RotationRange.Y, RotationRange.Y),
                FMath::RandRange(-RotationRange.Z, RotationRange.Z)
            );
            
            FRotator SurfaceRotation = Hit.Normal.Rotation();
            SpawnRotation = FRotator(SurfaceRotation.Pitch, SpawnRotation.Yaw, SpawnRotation.Roll);
            
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
            
            AActor* SpawnedActor = nullptr;
            
            if (ActorToSpawn)
            {
                SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
            }
            
            if (SpawnedActor)
            {
                float RandomScale = FMath::RandRange(ScaleRange.X, ScaleRange.Y);
                SpawnedActor->SetActorScale3D(FVector(RandomScale));
                
                SpawnedActors.Add(SpawnedActor);
            }
        }
    }
    
    UE_LOG(LogTemp, Log, TEXT("DecalInstanceProjector: Spawned %d actors"), SpawnedActors.Num());
	
}

void ADecalInstancerProjector::ClearSpawnedActors()
{
	for (AActor* SpawnedActor : SpawnedActors)
	{
		if (SpawnedActor && IsValid(SpawnedActor))
		{
			SpawnedActor->Destroy();
		}
	}
	SpawnedActors.Empty();
}

float ADecalInstancerProjector::CalculateGeometryComplexity(const FVector& Location, const TArray<AActor*>& OverlappingActors)
{
	const int32 NumRays = 16;
	int32 HitCount = 0;
	float TotalDistance = 0.0f;
	const float TraceDistance = 200.0f;
	
	for (int32 i=0; i<NumRays; i++)
	{
		float Angle = (360.0f / NumRays) * i;
		FVector Direction = FRotator(0, Angle, 0).Vector();
		
		FHitResult Hit;
		FVector Start = Location;
		FVector End = Location + Direction * TraceDistance;
		
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		
		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParams))
		{
			HitCount++;
			TotalDistance += Hit.Distance;
		}
	}
	
	if (HitCount == 0) return 0.0f;
	
	float AverageDistance = TotalDistance / HitCount;
	float Complexity = (float)HitCount * NumRays;
	float DistanceFactor = 1.0f - FMath::Clamp(AverageDistance / TraceDistance, 0.0f, 1.0f);
	
	return (Complexity + DistanceFactor) * 0.5f;
}

bool ADecalInstancerProjector::IsValidSpawnLocation(const FVector& Location)
{
	for (const AActor* SpawnedActor : SpawnedActors)
	{
		if (SpawnedActor && IsValid(SpawnedActor))
		{
			float Distance = FVector::Distance(Location, SpawnedActor->GetActorLocation());
			if (Distance < MinSpawnDistance)
			{
				return false;
			}
		}
	}
	return true;
}

