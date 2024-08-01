// Fill out your copyright notice in the Description page of Project Settings.

#include "BPOnlineBeaconHostObject.h"

#include "OnlineBeaconClient.h"

TArray<AOnlineBeaconClient*>
    ABPOnlineBeaconHostObject::GetClientActors() const {
	return ClientActors;
}

void ABPOnlineBeaconHostObject::OnConstruction(const FTransform& Transform) {
	Super::OnConstruction(Transform);

	// set ClientBeaconActorClass
	ClientBeaconActorClass = OnlineBeaconClientClass;

	// set BeaconTypeName
	BeaconTypeName = OnlineBeaconClientClass->GetName();
}

ABPOnlineBeaconHostObject::ABPOnlineBeaconHostObject(
    const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer) {
	// set default OnlineBeaconClientClass
	OnlineBeaconClientClass = AOnlineBeaconClient::StaticClass();
}
