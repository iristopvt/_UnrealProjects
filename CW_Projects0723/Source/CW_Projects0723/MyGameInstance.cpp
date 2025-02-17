// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "MyUIManager.h"
#include "MyEffecManger.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable
	(TEXT("/Script/Engine.DataTable'/Game/Data/MyStatDataTable.MyStatDataTable'"));

	if (dataTable.Succeeded())
	{
		_statTable = dataTable.Object;
		UE_LOG(LogTemp, Error, TEXT("StatTable Load Complete"));
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	auto statData = GetStatDataMyLevel(2);

	UE_LOG(LogTemp, Warning, TEXT("Level : %d , MaxHp : %d , Attack : %d")
		,statData->level, statData->maxHp, statData->attack);

	FActorSpawnParameters params;
	params.Name = TEXT("UIManger");
	_uiManger = GetWorld()->SpawnActor< AMyUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	params.Name = TEXT("EffectManger");
	_effectManager = GetWorld()->SpawnActor< AMyEffecManger>(FVector::ZeroVector, FRotator::ZeroRotator, params);
}

FMystatData* UMyGameInstance::GetStatDataMyLevel(int level)
{
	auto statData = _statTable->FindRow<FMystatData>(*FString::FromInt(level), TEXT("")); // 데이터 테이블에서 행으로 어떻게 가져오나

	return statData;
}
