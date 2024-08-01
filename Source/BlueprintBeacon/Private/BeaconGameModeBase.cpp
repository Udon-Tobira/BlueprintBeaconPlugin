// Fill out your copyright notice in the Description page of Project Settings.

#include "BeaconGameModeBase.h"

#include "LogBeaconGameModeBase.h"

ABeaconGameModeBase::ABeaconGameModeBase(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) {
	// set default OnlineBeaconHostObjectClass
	OnlineBeaconHostObjectClass = AOnlineBeaconHostObject::StaticClass();

	// set default OnlineBeaconHostClass
	OnlineBeaconHostClass = AOnlineBeaconHost::StaticClass();
}

AOnlineBeaconHostObject*
    ABeaconGameModeBase::GetOnlineBeaconHostObject() const {
	return OnlineBeaconHostObject;
}

AOnlineBeaconHost* ABeaconGameModeBase::GetOnlineBeaconHost() const {
	return OnlineBeaconHost;
}

void ABeaconGameModeBase::PreInitializeComponents() {
	Super::PreInitializeComponents();

	// if OnlineBeaconHostObjectClass or OnlineBeaconObjectClass is not set
	if (nullptr == OnlineBeaconHostObjectClass ||
	    nullptr == OnlineBeaconHostClass) {
		// log as Warning
		UE_LOG(LogBeaconGameModeBase, Warning,
		       TEXT("The game mode is set to use BeaconGameModeBase, but either "
		            "the OnlineBeaconHostObject class or the OnlineBeaconHost "
		            "class is not specified."));

		// finish
		return;
	}

	// get World
	UWorld* World = GetWorld();

	// check World
	check(World != nullptr);

	// create spawn parameter
	FActorSpawnParameters SpawnParam_Transient;
	SpawnParam_Transient.Instigator = GetInstigator();
	SpawnParam_Transient.ObjectFlags |= RF_Transient; // We never want to save

	// spawn OnlineBeaconHostObject
	OnlineBeaconHostObject = World->SpawnActor<AOnlineBeaconHostObject>(
	    OnlineBeaconHostObjectClass, SpawnParam_Transient);

	// check OnlineBeaconHostObject
	check(OnlineBeaconHostObject != nullptr);

	// spawn OnlineBeaconHost
	OnlineBeaconHost = World->SpawnActor<AOnlineBeaconHost>(OnlineBeaconHostClass,
	                                                        SpawnParam_Transient);

	// check OnlineBeaconHost
	check(OnlineBeaconHost != nullptr);

	// initialize OnlineBeaconHost
	const auto& SuccessInitOnlineBeaconHost = OnlineBeaconHost->InitHost();

	// if failed to initialize OnlineBeaconHost
	if (!SuccessInitOnlineBeaconHost) {
		// log as Error
		UE_LOG(LogBeaconGameModeBase, Error,
		       TEXT("failed to initialize OnlineBeaconHost class: %s"),
		       *OnlineBeaconHostClass->GetName());

		// finish
		return;
	}

	// register host object of OnlineBeaconHost
	OnlineBeaconHost->RegisterHost(OnlineBeaconHostObject);

	// start beacon host
	OnlineBeaconHost->PauseBeaconRequests(false);
}
