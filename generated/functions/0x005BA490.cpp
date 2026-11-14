// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA490 rf_animation_clip_pool_release_named_owned_buffers
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Walks800 clip records (base1D6DA28,stride124). Only if name[0] nonzero, raw pointer+120 nonNULL and ownership byte+108 nonzero: operator delete buffer, NULL+120, clear name[0]. Borrowed buffers, unnamed owned buffers and named entries without buffers remain untouched. Does not clear field+112/reference count+116 or all headers; returns final loop count800.
int rf_animation_clip_pool_release_named_owned_buffers()
{
  int result; // eax
  void **v1; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  v2 = 0;
  v1 = (void **)&unk_1D6DA28;
  while ( v2 < 800 )
  {
    if ( *(_BYTE *)v1 && v1[30] )
    {
      if ( *((_BYTE *)v1 + 108) )
      {
        operator delete(v1[30]);
        v1[30] = nullptr;
        *(_BYTE *)v1 = 0;
      }
    }
    result = ++v2;
    v1 += 31;
  }
  return result;
}

