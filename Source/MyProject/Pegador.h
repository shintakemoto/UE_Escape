// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Pegador.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPegador : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPegador();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	float Alcance = 100.f;
	
	UPhysicsHandleComponent* Fisica = nullptr;

	UInputComponent* InputComponent = nullptr;

	void Pegar();

	void Soltar();

	void AcharPhysicsHandleComponent();

	void SetupInputComponent();

	const FHitResult PegarObjetoProximo();
};
