// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F370 __CallSettingFrame@12
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Stdcall(catchCodePC,parentRegistration*,notificationCode),RET12; raw EAX continuation result preserved. Save own frame and EBX/ECX. Compute parent frame EBP=registration+12. First
// NLG_Notify1 receives live EAX=catchCodePC,ECX=notificationCode,EBP=parentFrame plus one compatibility stack slot; verified helper preserves registers/RET4. Push ESI/EDI, indirect
// CALL EAX with parent EBP and NO explicit callback arguments; restore EDI/ESI,save resulting EBP in EBX,restore own EBP. Reload original code intoECX; switch EBP to saved callback
// frame, map code100h to2 otherwise unchanged, push own saved EBP/code and call NLG_Notify1 again. Restore own frame/ECX/EBX,RET12. Notify helper preserves callback EAX through
// second notification, so return raw callback result, not void/status synthesis. Callback expected native catch funclet frame convention, not arbitrary C callback ABI. No
// target/cookie/registration check, fs-chain manipulation or finally; abnormal transfer bypasses second notify. ESI/EDI protected around callback, EBX/ECX restored from own stack.
void *__stdcall _CallSettingFrame(void *a1, struct EHRegistrationNode *a2, unsigned int a3)
{
  void (*v3)(void); // eax
  unsigned int v4; // ecx
  void *result; // eax

  _NLG_Notify1(a3);
  v3();
  v4 = a3;
  if ( a3 == 256 )
    v4 = 2;
  _NLG_Notify1(v4);
  return result;
}

