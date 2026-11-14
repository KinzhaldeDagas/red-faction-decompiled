// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F4C0 ??_U@YAPAXI@Z
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Real scalar allocator forwarding implementation of operator new[]:cdecl32bit size, calls scalar operator new with same size and returns pointer. No array cookie, element constructors, zero initialization or length bookkeeping in this wrapper; allocation/throw behavior inherited from operator new.
void *__cdecl operator new[](size_t Size)
{
  return operator new(Size);
}

