// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00518140 rf_byte_array_reallocate_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, byte arrays,navigation scratch/search/path costs,solid ownership and bounding sphere,vertex reuse,original ECX/stack/x87 flow and PE bytes): Thiscall header,new capacity in bytes,RET4. Saves old backing,stores new capacity BEFORE allocating exactly that many bytes,stores new backing,then copies signed i=0..(int)count-1 byte-by-byte and scalar-deletes old backing if nonNULL. Count unchanged. No capacity>=count enforcement:shrink below count still copies count bytes;count>=2^31 skips signed copy loop. No growth policy,allocation check,zero-fill,pointer alias guard or failure rollback. Caller518090 supplies doubling/min16 policy.
void __thiscall rf_byte_array_reallocate_unchecked(size_t *this, size_t a2)
{
  signed int i; // [esp+Ch] [ebp-8h]
  _BYTE *v4; // [esp+10h] [ebp-4h]

  v4 = (_BYTE *)*(this + 2);
  *(this + 1) = a2;
  *(this + 2) = (size_t)operator new(*(this + 1));
  for ( i = 0; i < (int)*this; ++i )
    *(_BYTE *)(*(this + 2) + i) = v4[i];
  if ( v4 )
    operator delete(v4);
}

