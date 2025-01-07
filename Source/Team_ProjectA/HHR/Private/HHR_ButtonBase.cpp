// Fill out your copyright notice in the Description page of Project Settings.


#include "Team_ProjectA/HHR/Public/HHR_ButtonBase.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UHHR_ButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	// 상위 wbp에서 수정한 값 할당
	BtnText->SetText(Text);
	// Font는 구조체이고 size 변수가 const여서 Font를 다시 생성해줘야 함 ->  Font도 따로 가져와줘야 해서 -> BP에서 처리
}

void UHHR_ButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼에 델리게이트 바인딩
	HitBox->OnClicked.AddDynamic(this, &UHHR_ButtonBase::OnClicked);
	HitBox->OnHovered.AddDynamic(this, &UHHR_ButtonBase::OnHovered);
	HitBox->OnUnhovered.AddDynamic(this, &UHHR_ButtonBase::OnUnhoverd);
	
	// 처음 버튼 모양으로 초기화
	if(Hover)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Hover->GetEndTime());
		PlayAnimation(Hover, Hover->GetEndTime(), 1, EUMGSequencePlayMode::Reverse, 1, false);
	}
	

}

void UHHR_ButtonBase::OnClicked()
{
	// click animation 재생
	if(Click)
	{
		PlayAnimationForward(Click);
	}
}

void UHHR_ButtonBase::OnHovered()
{
	// Hover anim 실행
	if(Hover)
	{
		PlayAnimationForward(Hover);
	}
}

void UHHR_ButtonBase::OnUnhoverd()
{
	// Hover anim 역실행
	if(Hover)                       
	{                               
		PlayAnimationReverse(Hover);
	}
}
