#include "Sequence.hpp"

Mode::Mode(
    EnumStage stage,
    EnumTransition transition,
    unsigned long suppressTime = 0,
    TurnState turnState = TurnState::Default
) : stage {stage},
    transition {transition},
    suppressTime {suppressTime},
    turnState {turnState}{}

TaskSequence::TaskSequence(Injection &injection) : injection {injection}
{
    Mode* homeToBeforeRamp1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction
        );

    Mode* beforeRampToAfterRamp1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    homeToBeforeRamp1->nextMode = beforeRampToAfterRamp1;

    Mode* afterRampToBlock1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    beforeRampToAfterRamp1->nextMode = afterRampToBlock1;

    Mode* secureBlock1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            SECURE_BLOCK_MS
        );

    afterRampToBlock1->nextMode = secureBlock1;

    Mode* grabBlock1 =
        new Mode(
            EnumStage::GrabClassifyBlock,
            EnumTransition::Once
        );

    secureBlock1->nextMode = grabBlock1;

    Mode* backBlock1 =
        new Mode(
            EnumStage::ReverseMotion,
            EnumTransition::Timed,
            BACK_ROBOT_MS
        );

    grabBlock1->nextMode = backBlock1;

    Mode* uTurnAfterBlockPickup1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );

    backBlock1->nextMode = uTurnAfterBlockPickup1;

    Mode* dropCrossAfterUTurn1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            CROSS_DETECT_SUPPRESS_MS
        );

    uTurnAfterBlockPickup1->nextMode = dropCrossAfterUTurn1;

    Mode* travelForwardAfterDropCross1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            SECURE_BLOCK_MS
        );

    dropCrossAfterUTurn1->nextMode = travelForwardAfterDropCross1;

    Mode* turnToDropBox1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::Timed,
            TURN_90DEG_MS,
            TurnState::OnBlockType
        );

    travelForwardAfterDropCross1->nextMode = turnToDropBox1;

    Mode* releaseBlock1 =
        new Mode(
            EnumStage::ReleaseBlock,
            EnumTransition::Once
        );

    turnToDropBox1->nextMode = releaseBlock1;

    Mode* turnToHome1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::Timed,
            TURN_90DEG_MS,
            TurnState::ReverseOnBlockType
        );

    releaseBlock1->nextMode = turnToHome1;

    Mode* homeCrossAfterDrop1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            HOME_CROSS_DETECT_SUPPRESS_MS
        );

    turnToHome1->nextMode = homeCrossAfterDrop1;

    Mode* goHomeForUTurn1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            SECURE_BLOCK_MS
        );

    homeCrossAfterDrop1->nextMode = goHomeForUTurn1;

    Mode* uTurnForBlock2 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );
    
    goHomeForUTurn1->nextMode = uTurnForBlock2;
    uTurnForBlock2->nextMode = homeToBeforeRamp1;

    // Mode* goHomeToEnd =
    //     new Mode(
    //         EnumStage::ForwardLineTracing,
    //         EnumTransition::Timed,
    //         GO_HOME_MS
    //     );
    // homeCrossAfterDrop1->nextMode = goHomeToEnd;

    setNextMode(homeToBeforeRamp1);
}

void TaskSequence::loop()
{
    currentStage->loop();
    if (currentTransition->shouldStageEnd()) {
        delete currentStage;
        delete currentTransition;
        setNextMode(activeMode->nextMode);
    }
}

void TaskSequence::setNextMode(Mode *nextMode)
{
    if (nextMode == nullptr) return;
    activeMode = nextMode;
    EnumStage newStageEnum = activeMode->stage;
    EnumTransition newTransitionEnum = activeMode->transition;
    bool turnLeft = shouldTurnLeft(activeMode->turnState);
    currentStage = injection.getNewStage(newStageEnum, turnLeft);
    currentTransition = injection.getNewTransition(newTransitionEnum, activeMode->suppressTime);
    injection.stateMonitor.activeStage.updateState(newStageEnum);
    injection.stateMonitor.activeTransition.updateState(newTransitionEnum);
}

bool TaskSequence::shouldTurnLeft(TurnState turnState)
{
    bool turnLeft;
    BlockType block = injection.stateMonitor.blockType.getState();

    if (block == BlockType::CoarseBlock) turnLeft = false;
    else turnLeft = true;

    if (turnState == TurnState::ReverseOnBlockType) turnLeft = !turnLeft;
    return turnLeft;    
}
