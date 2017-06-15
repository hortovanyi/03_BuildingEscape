

#pragma once

#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
    void OpenDoor();
    void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
    UPROPERTY(EditAnywhere)
    float OpenAngle = 90.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 0.5f;
    
    float LastDoorOpenTime;
    
//    UPROPERTY(EditAnywhere)
//    AActor* ActorThatOpens; // Remember Pawn inherits from Actor
    AActor* Owner = nullptr; // The owning door
 
    // Returns total mass in KGs
    float GetTotalMassOfActorsOnPlate();
};
