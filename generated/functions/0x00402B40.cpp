// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00402B40 rf_ai_choose_health_waypoint_goal
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one DWORD pointer argument ai. Pushes literal health at630F78 and ai to402950, removes8 bytes, then returns without defining a separate result.
// Fresh402950 scans waypoint-list records at700480, stride20C/count700478, admits case-insensitive name PREFIX matches of strlen(request), keeps at most32 indices, chooses rand
// modulo matches and calls4028C0 with selected index and flags0; only successful admission requests AI mode4 and ORs AI+530 flags800008. Fresh40AC80 multiplayer/split-screen prefix
// forwards its AI pointer here before standalone mode7 logic. This is a game AI health-goal adapter; inherited __fputchar label/Character integer are false. Wrapper itself does not
// find nearest pickup, validate ai, or add a return-status contract.
void __cdecl rf_ai_choose_health_waypoint_goal(void *ai)
{
  sub_402950((int *)ai, "health");
}

