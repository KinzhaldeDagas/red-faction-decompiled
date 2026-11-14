// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A1E0 rf_solid_face_next_link
// UNREALRED VERIFIED [level-lifecycle-20261028]: Returns dword at caller face+84. No null guard or sentinel adjustment. Reads face from first stack argument and uses retn4 (callee pops4 bytes); saved ECX is unused. No type change applied.
int __stdcall rf_solid_face_next_link(int a1)
{
  return *(_DWORD *)(a1 + 84);
}

