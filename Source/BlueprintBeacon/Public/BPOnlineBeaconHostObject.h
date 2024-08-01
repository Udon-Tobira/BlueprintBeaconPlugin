// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconHostObject.h"

#include "BPOnlineBeaconHostObject.generated.h"

/**
 * ABPOnlineBeaconHostObject class available from blueprint.
 * It should exist only on the server side.
 * Spawn OnlineBeaconClients and manage them.
 */
UCLASS(BlueprintType, Blueprintable, transient, config = Engine, notplaceable)
class BLUEPRINTBEACON_API ABPOnlineBeaconHostObject
    : public AOnlineBeaconHostObject {
	GENERATED_BODY()

public:
	//~=============================================================================
	// Accessors for classes spawned by beacon host object

	// The class of OnlineBeaconClient
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AOnlineBeaconClient> OnlineBeaconClientClass;

	//~=============================================================================
	// Accessors for beacon host object and beacon host.

	UFUNCTION(BlueprintCallable)
	TArray<AOnlineBeaconClient*> GetClientActors() const;

public:
	//~ Begin AActor Interface
	virtual void OnConstruction(const FTransform& Transform) override;
	//~ End AActor Interface

public:
	ABPOnlineBeaconHostObject(const FObjectInitializer& ObjectInitializer);
};
