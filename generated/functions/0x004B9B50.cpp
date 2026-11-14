// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B9B50 rf_object_clear_rendered_and_physics_skip_flags
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): No arguments. Traverses common live list from7D0C90 until sentinel7D0C80, following object+16. For every record clears common DWORD+124 bit0x10 and
// then bit0x800000 in separate stores; all other flags are preserved. No type, room, runtime or authority filtering and no helper callbacks. EAX on return is incidental traversal
// state, not an object count.
int rf_object_clear_rendered_and_physics_skip_flags()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = unk_7D0C90;
  for ( i = unk_7D0C90; (_UNKNOWN *)i != &unk_7D0C80; i = *(_DWORD *)(i + 16) )
  {
    *(_DWORD *)(i + 124) &= ~0x10u;
    result = i;
    *(_DWORD *)(i + 124) &= ~0x800000u;
  }
  return result;
}

