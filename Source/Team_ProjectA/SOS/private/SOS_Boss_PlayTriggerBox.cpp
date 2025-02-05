#include "Team_ProjectA/SOS/public/SOS_Boss_PlayTriggerBox.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AIController.h"
#include "JHS_C_Player.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Team_ProjectA/SOS/public/SOS_BOSS_Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

    // Player 컨트롤을 제한
    DisablePlayerControl();
    // Actor 자체를 삭제하려면 아래 코드 사용
    // this->Destroy();
}

void ASOS_Boss_PlayTriggerBox::EnablePlayerControl()
{
    // 플레이어 캐릭터 가져오기
    AJHS_C_Player* PlayerCharacter = Cast<AJHS_C_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        // 플레이어 컨트롤러 가져오기
        APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
        if (PlayerController)
        {
            PlayerController->EnableInput(PlayerController);
            PlayerController->SetIgnoreMoveInput(false); // 이동 입력 다시 활성화
            PlayerCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking); // 이동 다시 활성화
            UE_LOG(LogTemp, Warning, TEXT("Player Input & Movement Enabled!"));
        }
    }
}



void ASOS_Boss_PlayTriggerBox::DisablePlayerControl()
{
    // 플레이어 캐릭터 가져오기
    AJHS_C_Player* PlayerCharacter = Cast<AJHS_C_Player>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter)
    {
        // 플레이어 컨트롤러 가져오기
        APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->GetController());
        if (PlayerController)
        {
            PlayerController->DisableInput(PlayerController);
            PlayerController->SetIgnoreMoveInput(true); // 이동 입력 무시
            PlayerCharacter->GetCharacterMovement()->DisableMovement(); // 이동 자체를 막음
            UE_LOG(LogTemp, Warning, TEXT("Player Input & Movement Disabled!"));
        }
    }
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

    // 재활성
    EnablePlayerControl();
    
    
    // TriggerBox 파괴
    Destroy();
}




