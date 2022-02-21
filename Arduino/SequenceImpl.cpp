#include "Sequence.hpp"

Mode::Mode(
    EnumStage stage,
    EnumTransition transition,
    unsigned long suppressTime = 0,
    TurnState turnState = TurnState::Default
) : stage {stage},
    transition {transition},
    suppressTime {suppressTime},
    turnState {turnState},
    nextMode {nullptr} {}

TaskSequence::TaskSequence(Injection &injection) : injection {injection}
{
    Mode* homeToRamp1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    Mode* ramp1 = 
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    homeToRamp1->nextMode = ramp1;

    Mode* rampToBlock1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    ramp1->nextMode = rampToBlock1;

    Mode* secureBlock1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            SECURE_BLOCK_MS
        );

    rampToBlock1->nextMode = secureBlock1;

    Mode* grabBlock1 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    secureBlock1->nextMode = grabBlock1;

    Mode* backBlock1 =
        new Mode(
            EnumStage::ReverseMotion,
            EnumTransition::Timed,
            BACK_ROBOT_FIRST_MS
        );

    grabBlock1->nextMode = backBlock1;

    Mode* uTurnAfterBlockPickup1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );

    backBlock1->nextMode = uTurnAfterBlockPickup1;

    Mode* backBeforeClassify1 =
        new Mode(
            EnumStage::ReverseMotion,
            EnumTransition::Timed,
            BACK_ROBOT_CLASSSIFY_MS
        );
    
    uTurnAfterBlockPickup1->nextMode = backBeforeClassify1;

    Mode* classifyBlock1 =
        new Mode(
            EnumStage::ClassifyBlock,
            EnumTransition::Timed,
            CLASSIFY_TIME_MS
        );

    backBeforeClassify1->nextMode = classifyBlock1;

    Mode* dropCrossAfterUTurn1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross
        );

    classifyBlock1->nextMode = dropCrossAfterUTurn1;

    Mode* travelForwardAfterDropCross1 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            FORWARD_AFTER_CROSS_MS
        );

    dropCrossAfterUTurn1->nextMode = travelForwardAfterDropCross1;

    Mode* grabBlockHome1 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    travelForwardAfterDropCross1->nextMode = grabBlockHome1;

    Mode* turnToDropBox1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::Timed,
            TURN_90DEG_MS,
            TurnState::OnBlockType
        );

    grabBlockHome1->nextMode = turnToDropBox1;

    Mode* releaseBlock1 =
        new Mode(
            EnumStage::ReleaseBlock,
            EnumTransition::Once
        );

    turnToDropBox1->nextMode = releaseBlock1;

    Mode* turnToHome1 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            REVERSE_TURN_MS,
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
            FORWARD_AFTER_CROSS_MS
        );

    homeCrossAfterDrop1->nextMode = goHomeForUTurn1;

    Mode* uTurnForBlock2 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );
    
    goHomeForUTurn1->nextMode = uTurnForBlock2;

    Mode* homeToRamp2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    uTurnForBlock2->nextMode = homeToRamp2;

    Mode* ramp2 = 
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    homeToRamp2->nextMode = ramp2;

    Mode* rampToBlock2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    ramp2->nextMode = rampToBlock2;

    Mode* secureBlock2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            SECURE_BLOCK_MS
        );

    rampToBlock2->nextMode = secureBlock2;

    Mode* grabBlock2 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    secureBlock2->nextMode = grabBlock2;

    Mode* forwardTillGridCross2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross
        );

    grabBlock2->nextMode = forwardTillGridCross2;

    Mode* uTurnAfterBlockPickup2 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );

    forwardTillGridCross2->nextMode = uTurnAfterBlockPickup2;

    Mode* classifyBlock2 =
        new Mode(
            EnumStage::ClassifyBlock,
            EnumTransition::Timed,
            CLASSIFY_TIME_MS
        );

    uTurnAfterBlockPickup2->nextMode = classifyBlock2;

    Mode* dropCrossAfterUTurn2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            CROSS_DETECT_SUPPRESS_MS
        );

    classifyBlock2->nextMode = dropCrossAfterUTurn2;

    Mode* travelForwardAfterDropCross2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            FORWARD_AFTER_CROSS_MS
        );

    dropCrossAfterUTurn2->nextMode = travelForwardAfterDropCross2;

    Mode* grabBlockHome2 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    travelForwardAfterDropCross2->nextMode = grabBlockHome2;

    Mode* turnToDropBox2 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::Timed,
            TURN_90DEG_MS,
            TurnState::OnBlockType
        );

    grabBlockHome2->nextMode = turnToDropBox2;

    Mode* releaseBlock2 =
        new Mode(
            EnumStage::ReleaseBlock,
            EnumTransition::Once
        );

    turnToDropBox2->nextMode = releaseBlock2;

    Mode* turnToHome2 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            REVERSE_TURN_MS,
            TurnState::ReverseOnBlockType
        );

    releaseBlock2->nextMode = turnToHome2;

    Mode* homeCrossAfterDrop2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            HOME_CROSS_DETECT_SUPPRESS_MS
        );

    turnToHome2->nextMode = homeCrossAfterDrop2;

    Mode* goHomeForUTurn2 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            FORWARD_AFTER_CROSS_MS
        );

    homeCrossAfterDrop2->nextMode = goHomeForUTurn2;

    Mode* uTurnForBlock3 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );
    
    goHomeForUTurn2->nextMode = uTurnForBlock3;

    Mode* homeToRamp3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    uTurnForBlock3->nextMode = homeToRamp3;

    Mode* ramp3 = 
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectObstruction,
            RAMP_DETECT_SUPPRESS_MS
        );

    homeToRamp3->nextMode = ramp3;

    Mode* rampToGrid3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            FINAL_GRID_CROSS_SUPPRESS_MS
        );

    ramp3->nextMode = rampToGrid3;

    Mode* sweepBlock3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            FINAL_SWEEP_MS
        );
    
    rampToGrid3->nextMode = sweepBlock3;

    Mode* grabBlock3 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    sweepBlock3->nextMode = grabBlock3;

    Mode* backBlock3 =
        new Mode(
            EnumStage::ReverseMotion,
            EnumTransition::Timed,
            BACK_ROBOT_LAST_MS
        );

    grabBlock3->nextMode = backBlock3;

    Mode* uTurnAfterBlockPickup3 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            TURN_SUPPRESS_LINE_MS
        );

    backBlock3->nextMode = uTurnAfterBlockPickup3;

    Mode* classifyBlock3 =
        new Mode(
            EnumStage::ClassifyBlock,
            EnumTransition::Timed,
            CLASSIFY_TIME_MS
        );

    uTurnAfterBlockPickup3->nextMode = classifyBlock3;

    Mode* dropCrossAfterUTurn3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            CROSS_DETECT_SUPPRESS_MS
        );

    classifyBlock3->nextMode = dropCrossAfterUTurn3;

    Mode* travelForwardAfterDropCross3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            FORWARD_AFTER_CROSS_MS
        );

    dropCrossAfterUTurn3->nextMode = travelForwardAfterDropCross3;

    Mode* grabBlockHome3 =
        new Mode(
            EnumStage::GrabBlock,
            EnumTransition::Once
        );

    travelForwardAfterDropCross3->nextMode = grabBlockHome3;

    Mode* turnToDropBox3 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::Timed,
            TURN_90DEG_MS,
            TurnState::OnBlockType
        );

    grabBlockHome3->nextMode = turnToDropBox3;

    Mode* releaseBlock3 =
        new Mode(
            EnumStage::ReleaseBlock,
            EnumTransition::Once
        );

    turnToDropBox3->nextMode = releaseBlock3;

    Mode* turnToHome3 =
        new Mode(
            EnumStage::Turning,
            EnumTransition::DetectLine,
            REVERSE_TURN_MS,
            TurnState::ReverseOnBlockType
        );

    releaseBlock3->nextMode = turnToHome3;

    Mode* homeCrossAfterDrop3 =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::DetectCross,
            HOME_CROSS_DETECT_SUPPRESS_MS
        );

    turnToHome3->nextMode = homeCrossAfterDrop3;

    Mode* goHomeToEnd =
        new Mode(
            EnumStage::ForwardLineTracing,
            EnumTransition::Timed,
            GO_HOME_MS
        );
    homeCrossAfterDrop3->nextMode = goHomeToEnd;

    setNextMode(homeToRamp1);
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
    if (nextMode == nullptr) {
        injection.logger.log("Reached end of sequence", LoggerLevel::Info);
        while(1){};
    }
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
