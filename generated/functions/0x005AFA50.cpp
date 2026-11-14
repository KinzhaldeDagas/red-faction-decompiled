// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AFA50 rf_ui_window_dispatch_callback
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall two stack values event/id,RET8. Replaces id=-99999 with window ID DWORD288; other IDs including-99998 forwarded unchanged. If callback DWORD580 nonNULL,calls cdecl callback(event,id) and pops8 bytes. No callback means EAX incidental (may contain receiver if replacement executed),not a defined success value. Does not supply window pointer,queue event or mutate callback.
int __thiscall rf_ui_window_dispatch_callback(int this, int a2, int a3)
{
  int result; // eax

  if ( a3 == -99999 )
  {
    result = this;
    a3 = *(_DWORD *)(this + 288);
  }
  if ( *(_DWORD *)(this + 580) )
    return (*(int (__cdecl **)(int, int))(this + 580))(a2, a3);
  return result;
}

