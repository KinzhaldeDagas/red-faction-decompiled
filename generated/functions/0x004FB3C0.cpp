// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FB3C0 rf_mission_event_auto_forward_after_handler
// UNREALRED VERIFIED [mission-mover-activation-20261013] Policy also applies after a reverse local handler. Among currently admitted UnrealRed kinds, only Remove_Object(type2) and Switch(type32) suppress generic reverse forwarding. Delay(type48) propagates reverse after its deferred resume;0x4FB200 supplies mover suppression=1 to0x4F74A0, leaving direct mover targets untouched.
// UNREALRED VERIFIED [mission-mover-events-20261020] Specialized mover continuation: types66 Modify_Rotating_Mover and89 Reverse_Mover suppress generic forwarding after either local direction. Type72 Mover_Pause forwards after pause OR resume. Do not suppress its later direct-mover activation on the forward path.
// UNREALRED VERIFIED [mission-invert-20261020] Invert type3 suppresses generic forwarding in BOTH directions because its two local handlers explicitly route the opposite direction. Do not run an ordinary continuation after inversion.
// UNREALRED VERIFIED [combat-push-region-state-20261104]: Push_Region_State(type51) is not among the seven completion-suppressed types2,3,32,36,66,69,89. Both local directions are followed by generic target forwarding through0x4FB200 (ordinary event delay retains direction at0x4FB290). Do not suppress completion because a push-region target was found or missing.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Exact seven suppression types{2,3,32,36,66,69,89}; Alarm46 is absent and returns1. Both local directions from4FB290 and delayed continuation must preserve ordinary generic forwarding under current event/context lifetime.
char __cdecl rf_mission_event_auto_forward_after_handler(int a1)
{
  char result; // al

  switch ( a1 )
  {
    case 2:
    case 3:
    case 32:
    case 36:
    case 66:
    case 69:
    case 89:
      result = 0;
      break;
    default:
      result = 1;
      break;
  }
  return result;
}

