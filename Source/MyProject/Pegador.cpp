// Fill out your copyright notice in the Description page of Project Settings.

#include "Pegador.h"
#include "Gameframework/Actor.h"
#include "Gameframework/Pawn.h"
#include "Gameframework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "CollisionQueryParams.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#define OUT

UPegador::UPegador()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPegador::BeginPlay()
{
	Super::BeginPlay();
	AcharPhysicsHandleComponent();
	SetupInputComponent();
}

void UPegador::AcharPhysicsHandleComponent()
{
	Fisica = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Fisica)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fisica OK"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s não foi encontrada"), *GetOwner()->GetName());
	}
}

void UPegador::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component OK"));
		InputComponent->BindAction("Pegar", IE_Pressed, this, &UPegador::Pegar);
		InputComponent->BindAction("Pegar", IE_Released, this, &UPegador::Soltar);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s não foi encontrada (Input)"), *GetOwner()->GetName());
	}
}

void UPegador::Pegar()
{
	UE_LOG(LogTemp, Warning, TEXT("Pegar"));
	auto HitResult = PegarObjetoProximo();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		Fisica->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

	
}

void UPegador::Soltar()
{
	UE_LOG(LogTemp, Warning, TEXT("Soltar"));
	Fisica->ReleaseComponent();
}

void UPegador::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	////////////////
	FVector LocalPontoDeVista;
	FRotator AnguloPontoDeVista;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT LocalPontoDeVista, OUT AnguloPontoDeVista);
	FVector LinhaFim = LocalPontoDeVista + (AnguloPontoDeVista.Vector() * Alcance);
	////////////////

	if (Fisica->GrabbedComponent)
	{
		Fisica->SetTargetLocation(LinhaFim);
	}
}

const FHitResult UPegador::PegarObjetoProximo()
{
	//define começo e fim da linha de visao
	FVector LocalPontoDeVista;
	FRotator AnguloPontoDeVista;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT LocalPontoDeVista, OUT AnguloPontoDeVista);
	// ...

	//UE_LOG(LogTemp, Warning, TEXT("Local: %s, Angulo: %s"), 
	//	*LocalPontoDeVista.ToString(), 
	//	*AnguloPontoDeVista.ToString());

	//posiçao do final da linha de visao
	FVector LinhaFim = LocalPontoDeVista + (AnguloPontoDeVista.Vector() * Alcance);

	//desenha a linha de visa, baseado nos pontos de começo e fim, cor, e no final a espessura
	DrawDebugLine(GetWorld(), LocalPontoDeVista, LinhaFim, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);

	//definindo o ray-cast
	FCollisionQueryParams TraceParam(FName(TEXT("")), false, GetOwner());
	FHitResult HitAlvo;
	GetWorld()->LineTraceSingleByObjectType(OUT HitAlvo, LocalPontoDeVista, LinhaFim,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParam);

	//mostrando o alvo no log
	AActor* ActorHit = HitAlvo.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Linha pegador pegou: %s"), *(ActorHit->GetName()));
	}
	return HitAlvo;
}

