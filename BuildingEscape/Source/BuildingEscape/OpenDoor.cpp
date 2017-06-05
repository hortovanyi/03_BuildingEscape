// Copyright Nick Hortovanyi 2017

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
    // Find the owning Actor
    AActor * Owner = GetOwner();
    
    // Create a rotator
    FRotator NewRotation = FRotator(0.0f,OpenAngle,0.0f);
    
    Owner->SetActorRotation(NewRotation);

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
    // if the ActorThatOpns is in the Volume
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
    }
}

