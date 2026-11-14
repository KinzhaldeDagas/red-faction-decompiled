// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CD3B0 rf_render_state_set_bits20_24
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall packed DWORD receiver, one stack argument (RET 4). Clears receiver bits20..24 with 0xFE0FFFFF, inserts (argument & 0x1F)<<20, stores and returns full resulting DWORD in
// EAX. Only low five argument bits matter; all other receiver bits are preserved. Particle billboard rendering passes 0 when particle flags +88 bit0x2000 requests the alternate
// depth-test state. No global renderer state submission occurs inside this setter.
int __thiscall rf_render_state_set_bits20_24(int *this, char a2)
{
  int result; // eax

  *this &= 0xFE0FFFFF;
  result = *this | ((a2 & 0x1F) << 20);
  *this = result;
  return result;
}

