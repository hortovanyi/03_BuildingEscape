// Copyright Nick Hortovanyi 2017

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    // How far ahead of the player can we reach in CMs
    float Reach = 100.f;
    
    UPhysicsHandleComponent* PhysicsHandle = nullptr;
    
    UInputComponent* InputComponent = nullptr;
    
    // ray-cast and grab whats in reach
    void Grab();
    
    void Release();
    
    // Find attached physics handle
    void FindPyhsicsHandleComponent();
    
    // Setup (assumed) attached input component
    void SetupInputComponent();
    
    // Return hit for first physics body in reach
    const FHitResult GetFirstPhyiscsBodyInReach();
    
    const FVector GetPlayerReachEnd();
    const FVector GetPlayerReachStart();
    
};
