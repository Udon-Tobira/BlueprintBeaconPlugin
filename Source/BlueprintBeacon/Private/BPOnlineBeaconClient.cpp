// Fill out your copyright notice in the Description page of Project Settings.

#include "BPOnlineBeaconClient.h"

#include "LogBPOnlineBeaconClient.h"

void ABPOnlineBeaconClient::ConnectTo(
    const FString& ConnectInfo, EBPOnlineBeaconClientConnectToResult& Result) {
	// log
	UE_LOG(LogBPOnlineBeaconClient, Log, TEXT("trying to connect to: %s"),
	       *ConnectInfo);

	// create URL
	FURL ConnectURL(nullptr, *ConnectInfo, TRAVEL_Absolute);

	// initialize
	const auto& InitSuccess = InitClient(ConnectURL);

	// if failed to initialize
	if (!InitSuccess) {
		// log
		UE_LOG(LogBPOnlineBeaconClient, Error, TEXT("failed to connect to: %s"),
		       *ConnectInfo);

		// set as failure
		Result = EBPOnlineBeaconClientConnectToResult::Failure;

		// finish
		return;
	}

	// set as success
	Result = EBPOnlineBeaconClientConnectToResult::Success;

	// log
	UE_LOG(LogBPOnlineBeaconClient, Log,
	       TEXT("Online beacon client successfully connected to online beacon "
	            "host."));

	// start receiving request
	PauseBeaconRequests(false);
}
