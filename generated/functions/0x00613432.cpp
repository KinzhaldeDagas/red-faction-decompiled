// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613432 crt_address_of_00665a80
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed args. MOV EAX,OFFSET00665A80; RET. Return address of global storage, not its contents and not allocated copy. No dereference, errno handling,
// initialization or synchronization; exposes storage directly. In particular MOV OFFSET remains address-of even when decompiler off_ array notation suggests an indirection.
int *crt_address_of_00665a80()
{
  return &dword_665A80;
}

