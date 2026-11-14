// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CD9D0 rf_scene_definition_initialize_visibility_control_flags
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Marks every292-byte model definition flag+276 mask0x400 and every220-byte emitter definition flag+172 mask0x80. Then scans144-byte named-reference lists; case-sensitive prefix strncmp(name,$vis,4)==0 causes each8-byte reference (type,pointer) to clear corresponding flag for type0 model/type1 emitter. Other reference types ignored. Not a visibility-time evaluator; no name/index/reference validity checks. EAX incidental loop value.
int __thiscall rf_scene_definition_initialize_visibility_control_flags(_DWORD *this)
{
  int result; // eax
  char *Str1; // [esp+4h] [ebp-Ch]
  int k; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]
  int j; // [esp+Ch] [ebp-4h]
  int m; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < *(this + 19); ++i )
  {
    *(_DWORD *)(*(this + 18) + 292 * i + 276) |= 0x400u;
    result = i + 1;
  }
  for ( j = 0; j < *(this + 23); ++j )
  {
    *(_DWORD *)(*(this + 22) + 220 * j + 172) |= 0x80u;
    result = j + 1;
  }
  for ( k = 0; k < *(this + 31); ++k )
  {
    Str1 = (char *)(*(this + 30) + 144 * k);
    if ( !strncmp(Str1, "$vis", 4u) )
    {
      for ( m = 0; m < *((_DWORD *)Str1 + 34); ++m )
      {
        if ( *(_DWORD *)(*((_DWORD *)Str1 + 35) + 8 * m) )
        {
          if ( *(_DWORD *)(*((_DWORD *)Str1 + 35) + 8 * m) == 1 )
            *(_DWORD *)(*(_DWORD *)(*((_DWORD *)Str1 + 35) + 8 * m + 4) + 172) &= ~0x80u;
        }
        else
        {
          *(_DWORD *)(*(_DWORD *)(*((_DWORD *)Str1 + 35) + 8 * m + 4) + 276) &= ~0x400u;
        }
      }
    }
    result = k + 1;
  }
  return result;
}

