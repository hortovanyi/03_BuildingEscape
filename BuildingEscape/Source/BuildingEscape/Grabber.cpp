// Copyright Nick Hortovanyi 2017

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UWorld *world = GetWorld();

	// Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    world->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );
    
//    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Positions: %s"),
//           *PlayerViewPointLocation.ToString(),
//           *PlayerViewPointRotation.ToString()
//           )
    
    

    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    
    // Draw a red trace in the world to visualsie
    DrawDebugLine(
        world,
        PlayerViewPointLocation,
        LineTraceEnd,
        FColor(255,0,0),
        false,
        -1,
        0,
        10.f
    );
    
    // Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")),false, GetOwner());
    
    // Line-trace (AKA Ray-cast) out to reach distance
    FHitResult Hit;
    world->LineTraceSingleByObjectType
    (
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    
    // See what we hit
    AActor * HitActor = Hit.GetActor();
    if (HitActor) {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(HitActor->GetName()))
    }
}

