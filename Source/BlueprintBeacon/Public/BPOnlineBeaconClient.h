// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"

#include "BPOnlineBeaconClient.generated.h"

UENUM(BlueprintType)
enum class EBPOnlineBeaconClientConnectToResult : uint8 {
	// successfully log in
	Success,
	// failed to log in
	Failure
};

/**
 * OnlineBeaconClient class available from blueprint.
 * By generating it on the client side and connecting it with ConnectTo, it is
 * also generated on the server side, which allows communication between each
 * other's OnlineBeaconClient.
 */
UCLASS(BlueprintType, Blueprintable, transient, config = Engine, notplaceable)
class BLUEPRINTBEACON_API ABPOnlineBeaconClient: public AOnlineBeaconClient {
	GENERATED_BODY()

public:
	/**
	 * Connect this beacon to the destination specified by the URL argument.
	 * @param ConnectInfo   Connection information string.
	 *                      It should be a string that can be interpreted by
	 *                      BeaconNetDriver as an appropriate connection
	 *                      destination. For example, for IpNetDriver, it should
	 *                      be in the form of IPAddress:PortNumber, such as
	 *                      127.0.0.1:15000. For NetDriverEOS,
	 *                      EOS:DestinationUserID:GameNetDriver:ChannelNumber,
	 *                      etc.
	 * @param Result   Execution Results.
	 *                 In case of success, the connection is established.
	 *                 If the result is failure, connecting is failed.
	 */
	UFUNCTION(BlueprintCallable, meta = (ExpandEnumAsExecs = "Result"))
	void ConnectTo(const FString&                        ConnectInfo,
	               EBPOnlineBeaconClientConnectToResult& Result);
};
