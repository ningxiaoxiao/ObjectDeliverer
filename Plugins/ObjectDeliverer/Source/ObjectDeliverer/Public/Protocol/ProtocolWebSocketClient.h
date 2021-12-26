// Copyright 2019 ayumax. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "ObjectDelivererProtocol.h"
#include "ProtocolWebSocketClient.generated.h"


UCLASS(BlueprintType, Blueprintable)
class OBJECTDELIVERER_API UProtocolWebSocketClient : public UObjectDelivererProtocol
{
	GENERATED_BODY()

public:
	UProtocolWebSocketClient();
	~UProtocolWebSocketClient();

	/**
	 * Initialize TCP/IP server.
	 * @param Url - The ip address of the connection destination.
	 * @param Port - The port number of the connection destination.
	 * @param Retry - If connection fails, try connection again
	 * @param AutoConnectAfterDisconnect - If disconnected, try connection again
	 */
	UFUNCTION(BlueprintCallable, Category = "ObjectDeliverer|Protocol")
		void Initialize(const FString& Url = TEXT("ws://localhost"), bool Retry = false, bool AutoConnectAfterDisconnect = false);

	UFUNCTION(BlueprintCallable, Category = "ObjectDeliverer|Protocol")
		UProtocolWebSocketClient* WithReceiveBufferSize(int32 SizeInBytes);

	virtual void Start() override;
	virtual void Close() override;
	virtual void Send(const TArray<uint8>& DataBuffer) const override;


private:
	bool TryConnect();

protected:
	virtual void DispatchDisconnected(const UObjectDelivererProtocol* DisconnectedObject) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "ObjectDeliverer|Protocol")
		FString ServerUrl = "ws://localhost";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "ObjectDeliverer|Protocol")
		bool RetryConnect = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = "ObjectDeliverer|Protocol")
		bool AutoConnectAfterDisconnect = false;

private:
	TSharedRef<IWebSocket> WebSocket;
};
