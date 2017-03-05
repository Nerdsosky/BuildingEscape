// Copyright Joey Wysosky 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll trigger volume every frame to detect when something overlaps
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}		
}

//Opens the door if it is not already open
void UOpenDoor::OpenDoor()
{
	if (!bIsOpen)
	{
		AActor* Owner = GetOwner();
		FRotator OwnersRotation = Owner->GetActorRotation();
		OwnersRotation.Yaw = OwnersRotation.Yaw + AmountToOpen;
		Owner->SetActorRotation(OwnersRotation, ETeleportType::None);
		bIsOpen = true;
	}
}