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
    
//    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
    // Create a rotator
    FRotator NewRotation = FRotator(0.0f,OpenAngle,0.0f);
    
    Owner->SetActorRotation(NewRotation);

}

void UOpenDoor::CloseDoor()
{
    // Create a rotator
    FRotator NewRotation = FRotator(0.0f,0.0f,0.0f);
    
    Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!PressurePlate) {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate component"), *(GetOwner()->GetName()))
        return;
    }
    // if the ActorThatOpens is in the Volume
//    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    // Poll the Trigger Volume
    if (GetTotalMassOfActorsOnPlate() > 30.f) // TODO Make into a parameter
    {
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay){
        CloseDoor();
    }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    
    float TotalMass = 0.f;
    
    // Find all the overlapping actors
    TArray<AActor*> OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    // Iterate through them adding their masses
    for (const auto* Actor: OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
//        UE_LOG(LogTemp, Warning, TEXT("Overlapping actor name: %s"), *(Actor->GetName()))
    }
    
    return TotalMass;
}
