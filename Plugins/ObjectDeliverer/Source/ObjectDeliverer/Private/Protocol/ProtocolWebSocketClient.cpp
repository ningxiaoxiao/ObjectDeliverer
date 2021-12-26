// Copyright 2019 ayumax. All Rights Reserved.
#include "Protocol/ProtocolWebSocketClient.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"

UProtocolWebSocketClient::UProtocolWebSocketClient()
{

}

UProtocolWebSocketClient::~UProtocolWebSocketClient()
{

}

void UProtocolWebSocketClient::Initialize(const FString& Url/* = TEXT("ws://localhost")*/, bool Retry/* = false*/, bool _AutoConnectAfterDisconnect/* = false*/)
{
	ServerUrl = Url;
	RetryConnect = Retry;
	AutoConnectAfterDisconnect = _AutoConnectAfterDisconnect;
}

UProtocolWebSocketClient* UProtocolWebSocketClient::WithReceiveBufferSize(int32 SizeInBytes)
{

	return this;
}

void UProtocolWebSocketClient::Start()
{
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(ServerUrl, TEXT("ws"));

	WebSocket->OnConnected().AddLambda([this]() {
		UE_LOG(LogTemp, Log, TEXT("Connected to websocket server."));
		WebSocket->Send("{\"event\": \"test\", \"data\": \"test message data\"}");
		});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error) {
		UE_LOG(LogTemp, Log, TEXT("Failed to connect to websocket server with error: \"%s\"."), *Error);
		});

	WebSocket->OnMessage().AddLambda([](const FString& Message) {
		UE_LOG(LogTemp, Log, TEXT("Received message from websocket server: \"%s\"."), *Message);
		});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {
		UE_LOG(LogTemp, Log, TEXT("Connection to websocket server has been closed with status code: \"%d\" and reason: \"%s\"."), StatusCode, *Reason);
		});

	WebSocket->Connect();

}

bool UProtocolWebSocketClient::TryConnect()
{
	//if (InnerSocket->Connect(ConnectEndPoint.ToInternetAddr().Get()))
	//{
	//	DispatchConnected(this);

	//	OnConnected(InnerSocket);
	//}
	//else if (RetryConnect)
	//{
	//	return true;
	//}

	return false;
}

void UProtocolWebSocketClient::Close()
{
	Super::Close();

	//if (!ConnectThread) return;
	//ConnectThread->Kill(true);

	//delete ConnectThread;
	//ConnectThread = nullptr;

	//if (!ConnectInnerThread) return;
	//delete ConnectInnerThread;
	//ConnectInnerThread = nullptr;
}


void UProtocolWebSocketClient::DispatchDisconnected(const UObjectDelivererProtocol* DisconnectedObject)
{
	Super::DispatchDisconnected(DisconnectedObject);

	//if (AutoConnectAfterDisconnect)
	//{
	//	Start();
	//}
}

void UProtocolWebSocketClient::Send(const TArray<uint8>& DataBuffer) const
{

}