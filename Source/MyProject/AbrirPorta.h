// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "AbrirPorta.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAbrirPorta : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbrirPorta();

	virtual void BeginPlay() override;

	void AbrirPorta();
	void FecharPorta();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts

private:
	UPROPERTY(VisibleAnywhere)
	float Angulo = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* AreaChave;

	UPROPERTY(EditAnywhere)
	float TempoFecharPorta = 1.f;

	float TempoPortaAberta;

	UPROPERTY(EditAnywhere)
	AActor* Ator;

	AActor* Dono;
	
};
