// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OnlineBeaconHost.h"
#include "OnlineBeaconHostObject.h"

#include "BeaconGameModeBase.generated.h"

/**
 * A game mode base extension class that adds the ability to spawn beacon host
 * object and beacon host.
 */
UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable, Transient,
       hideCategories = (Info, Rendering, MovementReplication, Replication,
                         Actor),
       MinimalAPI)
class ABeaconGameModeBase: public AGameModeBase {
	GENERATED_UCLASS_BODY()

public:
	//~=============================================================================
	// Accessors for classes spawned by game

	// The class of OnlineBeaconHostObject spawned only in server.
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AOnlineBeaconHostObject> OnlineBeaconHostObjectClass;

	// The class of OnlineBeaconHost spawned only in server.
	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	TSubclassOf<AOnlineBeaconHost> OnlineBeaconHostClass;

	//~=============================================================================
	// Accessors for beacon host object and beacon host.

	// OnlineBeaconHostObject controls
	// OnlineBeaconHost and OnlineBeaconClient.
	UPROPERTY(Transient)
	TObjectPtr<AOnlineBeaconHostObject> OnlineBeaconHostObject;

	// OnlineBeaconHost listens on server and wait for connecting from
	// OnlineBeaconClient.
	UPROPERTY(Transient)
	TObjectPtr<AOnlineBeaconHost> OnlineBeaconHost;

	UFUNCTION(BlueprintCallable)
	AOnlineBeaconHostObject* GetOnlineBeaconHostObject() const;

	UFUNCTION(BlueprintCallable)
	AOnlineBeaconHost* GetOnlineBeaconHost() const;

public:
	// initialize this game mode object
	virtual void PreInitializeComponents() override;
};
