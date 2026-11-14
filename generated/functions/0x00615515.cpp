// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00615515 @_EH4_TransferToHandler@8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Control-transfer fastcall ECX handler entry,EDX frame. SetEBP=frame,ESI=handler,EAX=handler;push1 andcall NLG_Notify,whoseRET4 reclaims code.
// ThenzeroEAX/EBX/ECX/EDX/EDI and TAIL JMP ESI; no ownRET/frame restoration. ESI/EBP intentionally carry target entry/frame, zeros are established register context rather than two
// pushed handler parameters. Corrected two-register ABI removes false object receiver/return promise; no validation/catch.
void __fastcall _EH4_TransferToHandler(void *handler, void *frame)
{
  _NLG_Notify((int)handler, (int)frame, 1);
  ((void (__fastcall *)(_DWORD, _DWORD))handler)(0, 0);
}

