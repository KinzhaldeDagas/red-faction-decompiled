// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FF10 rf_string_assign_from_object
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Thiscall destination, source object. Exact object self-assignment does nothing. Equal stored extents: if nonzero, copies source buffer through terminating NUL into existing destination; if zero, no write. Unequal extents: releases destination then assigns source C string, recomputing strlen. Returns destination. Does not validate buffer pointers/capacity or detect distinct objects sharing storage; equal stale extents are not recomputed.
_DWORD *__thiscall rf_string_assign_from_object(_DWORD *this, int a2)
{
  char v2; // cl
  _BYTE *v4; // [esp+8h] [ebp-Ch]
  char *v5; // [esp+Ch] [ebp-8h]

  if ( (_DWORD *)a2 != this )
  {
    if ( *(_DWORD *)a2 == *this )
    {
      if ( *this )
      {
        v5 = *(char **)(a2 + 4);
        v4 = (_BYTE *)*(this + 1);
        do
        {
          v2 = *v5;
          *v4++ = *v5++;
        }
        while ( v2 );
      }
    }
    else
    {
      rf_string_release_buffer_keep_extent(this);
      rf_string_assign_cstr_bounded((int)this, *(char **)(a2 + 4), -1);
    }
  }
  return this;
}

