// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/HHR_UI/Public/HHR_PlayerHUD.h"

#include "JHS_C_Player.h"
#include "Components/ProgressBar.h"

#include "Components/TimelineComponent.h"
#include "Team_ProjectA/HHR/HHR_Interact/Public/HHR_InteractComponent.h"

void UHHR_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	// 캐릭터의 델리게이트에 바인딩
	AJHS_C_Player* player = Cast<AJHS_C_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player)
	{
		player->OnDecreaseHealthBar.AddDynamic(this, &UHHR_PlayerHUD::DecreaseHPBar);
	}

	// Timeline에 바인딩
	if(HealthCurveFloat)
	{
		DelayHealthTimeline = new FTimeline();

		FOnTimelineFloat TimelineUpdate;
		TimelineUpdate.BindUFunction(this, FName("OnTimelineUpdate"));
		DelayHealthTimeline->AddInterpFloat(HealthCurveFloat, TimelineUpdate);

		FOnTimelineEvent TimelineFinish;
		TimelineFinish.BindUFunction(this, FName("OnTimelineFinish"));
		DelayHealthTimeline->SetTimelineFinishedFunc(TimelineFinish);
		
		//  초기화
		DelayHealthTimeline->SetLooping(false);
	}
}

// TODO : ! HP Bar를 컴포넌트화 시켜도 될듯 
void UHHR_PlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	// Timeline 호출
	if(DelayHealthTimeline->IsPlaying())
	{
		// Timeline playing 되고 있으면 호출
		DelayHealthTimeline->TickTimeline(DeltaTime);
	}
}

void UHHR_PlayerHUD::DecreaseHPBar(float CurrentHealth)
{
	
	// 1) CachedHealth에 Damege 대입 -> HealthBar의 Percent에 적용
	CachedHelath = CurrentHealth;
	float percent = CachedHelath / 100.f;
	HPBar->SetPercent(percent);

	// 2) DelayHPBar에 Timeline 적용하는 함수 적용
	DelayHealthTimeline->Play();
	
}

// TO DO : 수정 필요 
float UHHR_PlayerHUD::GetStatminPercent() const
{
	// player character의 스테미나에 바인딩
	AJHS_C_Player* player = Cast<AJHS_C_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (player && player->GetStatmina() > 0)
	{
		return player->GetStatmina() / 100;
	}
	return 0;
}

void UHHR_PlayerHUD::OnTimelineUpdate(float Value)
{
	// prograssbar delay
	float dis = DelayCachedHelath - CachedHelath;
	if(dis > 0)
	{
		float percent = ((dis * Value) + CachedHelath) / 100.f;
		DelayHPBar->SetPercent(percent);
	}
	
}

void UHHR_PlayerHUD::OnTimelineFinish()
{
	// DelayCachedHealth 업뎃 & Timeline 초기화 
	DelayCachedHelath = CachedHelath;
	DelayHealthTimeline->SetPlaybackPosition(0.0f, false);
}


