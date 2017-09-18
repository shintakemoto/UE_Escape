// Fill out your copyright notice in the Description page of Project Settings.

#include "AbrirPorta.h"
#include "Gameframework/Actor.h"
#include "Gameframework/Pawn.h"
#include "Gameframework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/TriggerVolume.h"

// Sets default values for this component's properties
UAbrirPorta::UAbrirPorta()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbrirPorta::BeginPlay()
{
	Super::BeginPlay();
	Dono = GetOwner();
	Ator = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UAbrirPorta::AbrirPorta()
{
	Dono->SetActorRotation(FRotator(0.f, Angulo, 0.f));
}

void UAbrirPorta::FecharPorta()
{
	Dono->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UAbrirPorta::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AreaChave->IsOverlappingActor(Ator))
	{
		AbrirPorta();
		TempoPortaAberta = GetWorld()->GetTimeSeconds();
	}


	if (GetWorld()->GetTimeSeconds() - TempoPortaAberta > TempoFecharPorta)
	{
		FecharPorta();
	}
	
	
}

