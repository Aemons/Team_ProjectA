#include "Team_ProjectA/SOS/public/SOS_Boss_PlayTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
ASOS_Boss_PlayTriggerBox::ASOS_Boss_PlayTriggerBox()
{
    PrimaryActorTick.bCanEverTick = false;

    // Trigger Box 생성 및 설정
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASOS_Boss_PlayTriggerBox::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ASOS_Boss_PlayTriggerBox::BeginPlay()
{
    Super::BeginPlay();
}



void ASOS_Boss_PlayTriggerBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!OtherActor) return;
    
    // 시퀀스 재생 및 완료 후 동작 설정
    if (SequenceToPlay)
    {
        ALevelSequenceActor* SequenceActor = Cast<ALevelSequenceActor>(UGameplayStatics::GetActorOfClass(this, ALevelSequenceActor::StaticClass()));
        if (SequenceActor)
        {
            ULevelSequencePlayer* SequencePlayer = SequenceActor->SequencePlayer;
            if (SequencePlayer)
            {
                // 시퀀스 재생
                SequencePlayer->Play();

                // OnFinished 델리게이트에 함수 바인딩
                SequencePlayer->OnFinished.AddDynamic(this, &ASOS_Boss_PlayTriggerBox::OnSequenceFinished);

                // UE_LOG(LogTemp, Warning, TEXT("Sequence Played and waiting for finish."));
            }
        }
    }

    
    // Actor 자체를 삭제하려면 아래 코드 사용
    // this->Destroy();
}

// Sequencer가 종료 된 후 발생 시킬 함수
// BlackBoardKey의 EnumState Attack으로 변경
void ASOS_Boss_PlayTriggerBox::OnSequenceFinished()
{
    // 사운드 큐 재생 (월드에 독립적으로 생성)
    if (SoundCue)
    {
        UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), SoundCue, SoundVolume);
        if (AudioComponent)
        {
            AudioComponent->Play();  // 재생
        }
    }

    // BossCharacter와 관련된 코드
    ACharacter* BossCharacter = Cast<ACharacter>(UGameplayStatics::GetActorOfClass(this, ASOS_BOSS_Character::StaticClass()));
    if (BossCharacter)
    {
        AAIController* BossAIController = Cast<AAIController>(BossCharacter->GetController());
        if (BossAIController && BossAIController->GetBlackboardComponent())
        {
            BossAIController->GetBlackboardComponent()->SetValueAsEnum(BlackboardKeyName, EnumValueToSet);

            UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BossAIController->GetBrainComponent());
            if (BehaviorTreeComponent)
            {
                BehaviorTreeComponent->RequestExecution(EBTNodeResult::Failed);
            }
        }
    }

    // TriggerBox 파괴
    Destroy();
}




