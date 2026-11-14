// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004494E0 rf_difficulty_set_valid_choice_copy_configured_and_load_ui
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): One cdecl raw32-bit requested difficulty, full EAX from46B640. Unsigned request<=3 dispatches verified four-entry jump
// table449540 and stores EXACT matching value0/1/2/3 to activeDWORD6612A4. All other bit patterns, including signed-negative inputs, leave active difficulty unchanged. EVERY path
// then copies CURRENT active6612A4 into configuredDWORD6612A8 and calls46B640, which loads active into UI selection6F7F54 and returns it. Invalid input therefore still synchronizes
// configured/UI fields from old active; it is not a no-op/error return. No clamp, persistence save, gameplay reinitialization, runtime gate or rollback.
// UNREALRED VERIFIED [original-ai-difficulty-owner-20261112]: Nativeconsole choice0..3 writes ACTIVE6612A4; any other integer leaves active unchanged. Then ALWAYS copies ACTIVE to CONFIGURED6612A8 before refreshing UI selection. Both PE DWORD initializers are1. This differs from gameplay child callback46B5C0 which writes configured first and updates active only when multiplayer runtime BYTE is exactly0.
int __cdecl rf_difficulty_set_valid_choice_copy_configured_and_load_ui(int a1)
{
  switch ( a1 )
  {
    case 0:
      dword_6612A4 = 0;
      break;
    case 1:
      dword_6612A4 = 1;
      break;
    case 2:
      dword_6612A4 = 2;
      break;
    case 3:
      dword_6612A4 = 3;
      break;
    default:
      break;
  }
  dword_6612A8 = dword_6612A4;
  return rf_gameplay_difficulty_choice_load_active();
}

