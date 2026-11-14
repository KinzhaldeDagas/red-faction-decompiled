// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00531370 rf_callback_return_true_pop4_531370
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, collision cache/traversal,strict AABBs,face/corner ownership,signed area and reset-on-read pool peaks,original ECX/stack flow and PE bytes): Raw15-byte body saves unusedECX, sets AL1 and RET4. One stackDWORD unread, no object/global reads or writes and no calls. Returns true regardless of argument/receiver; EAX high bits unspecified. Inherited Concurrency::_ContextCallback operator== name was not evidence of object comparison or geometry equality.
char __stdcall rf_callback_return_true_pop4_531370(int a1)
{
  return 1;
}

