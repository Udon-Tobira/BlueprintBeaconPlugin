// Fill out your copyright notice in the Description page of Project Settings.

#include "BPOnlineBeaconClient.h"

#include "LogBPOnlineBeaconClient.h"

void ABPOnlineBeaconClient::ConnectTo(
    const FString& ConnectInfo, EBPOnlineBeaconClientConnectToResult& Result) {
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

	// start receiving request
	PauseBeaconRequests(false);
}
