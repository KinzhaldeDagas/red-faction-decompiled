// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004613B0 rf_browser_compare_server_row_indices
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Qsort cdecl(int*leftIndex,int*rightIndex),reads pointed RAW record indices,base6F52CC,stride108;no bounds/pointer/string validation. Mode661FE0 switch:0
// signbit of flagsDWORD104 set sorts BEFORE clear,then UNSIGNED IPv4DWORD84 descending;EQUAL IP returns+1,not0,port ignored. Mode1 server-name Cstring0,mode3 level-name
// Cstring32:nonempty beforeempty,both empty0,otherwise normalized inline CASE-SENSITIVE unsigned-byte strcmp(-1/0/+1). Mode4 playersBYTE92 descending,ties same IPv4 descending(+1
// equality). Mode5:nonempty mod/archive-basename Cstring64 chosen;else dereference localized mode-name pointer table6F3AE4[modeDWORD80] WITHOUT bounds or pointer-entry guard. Chosen
// NULL strings sort last;bothNULL0;otherwise same case-sensitive strcmp (empty fallback not separately placed last). Mode2 AND every other mode value (unsigned>5 included):signed
// pingWORD94 nonnegative first,ascending ping;both negative or equal nonnegative tie by descending IPv4,+1 on equalIP. String emptiness uses FULL unbounded NUL scans,not single-byte
// checks. Numeric modes0/4/default therefore return+1 even comparing an index with itself,violating comparator equality/reflexivity;do not infer stable/well-defined tie order. No
// port tie-break,sort-direction toggle or record mutation here;wrapper sorts an index array.
int __cdecl rf_browser_compare_server_row_indices(int *a1, int *a2)
{
  int result; // eax
  const char *v3; // [esp+C4h] [ebp-10h]
  const char *v4; // [esp+C8h] [ebp-Ch]
  int v5; // [esp+CCh] [ebp-8h]
  int v6; // [esp+D0h] [ebp-4h]

  v6 = *a1;
  v5 = *a2;
  switch ( dword_661FE0 )
  {
    case 0:
      if ( *((int *)dword_6F52CC + 27 * v6 + 26) >= 0 )
      {
        if ( *((int *)dword_6F52CC + 27 * v5 + 26) >= 0 )
        {
          if ( *((_DWORD *)dword_6F52CC + 27 * v6 + 21) <= *((_DWORD *)dword_6F52CC + 27 * v5 + 21) )
            result = 1;
          else
            result = -1;
        }
        else
        {
          result = 1;
        }
      }
      else if ( *((int *)dword_6F52CC + 27 * v5 + 26) >= 0 )
      {
        result = -1;
      }
      else if ( *((_DWORD *)dword_6F52CC + 27 * v6 + 21) <= *((_DWORD *)dword_6F52CC + 27 * v5 + 21) )
      {
        result = 1;
      }
      else
      {
        result = -1;
      }
      break;
    case 1:
      if ( (char *)dword_6F52CC + 108 * v6 + strlen((const char *)dword_6F52CC + 108 * v6) + 1 == (char *)dword_6F52CC
                                                                                                + 108 * v6
                                                                                                + 1 )
      {
        result = (char *)dword_6F52CC + 108 * v5 + strlen((const char *)dword_6F52CC + 108 * v5) + 1 != (char *)dword_6F52CC + 108 * v5 + 1;
      }
      else if ( (char *)dword_6F52CC + 108 * v5 + strlen((const char *)dword_6F52CC + 108 * v5) + 1 == (char *)dword_6F52CC + 108 * v5 + 1 )
      {
        result = -1;
      }
      else
      {
        result = strcmp((const char *)dword_6F52CC + 108 * v6, (const char *)dword_6F52CC + 108 * v5);
      }
      break;
    case 3:
      if ( (char *)dword_6F52CC + 108 * v6 + strlen((const char *)dword_6F52CC + 108 * v6 + 32) + 33 == (char *)dword_6F52CC + 108 * v6 + 33 )
      {
        result = (char *)dword_6F52CC + 108 * v5 + strlen((const char *)dword_6F52CC + 108 * v5 + 32) + 33 != (char *)dword_6F52CC + 108 * v5 + 33;
      }
      else if ( (char *)dword_6F52CC + 108 * v5 + strlen((const char *)dword_6F52CC + 108 * v5 + 32) + 33 == (char *)dword_6F52CC + 108 * v5 + 33 )
      {
        result = -1;
      }
      else
      {
        result = strcmp((const char *)dword_6F52CC + 108 * v6 + 32, (const char *)dword_6F52CC + 108 * v5 + 32);
      }
      break;
    case 4:
      if ( *((unsigned __int8 *)dword_6F52CC + 108 * v6 + 92) <= (int)*((unsigned __int8 *)dword_6F52CC + 108 * v5 + 92) )
      {
        if ( *((unsigned __int8 *)dword_6F52CC + 108 * v6 + 92) >= (int)*((unsigned __int8 *)dword_6F52CC + 108 * v5 + 92) )
        {
          if ( *((_DWORD *)dword_6F52CC + 27 * v6 + 21) <= *((_DWORD *)dword_6F52CC + 27 * v5 + 21) )
            result = 1;
          else
            result = -1;
        }
        else
        {
          result = 1;
        }
      }
      else
      {
        result = -1;
      }
      break;
    case 5:
      if ( (char *)dword_6F52CC + 108 * v6 + strlen((const char *)dword_6F52CC + 108 * v6 + 64) + 65 == (char *)dword_6F52CC + 108 * v6 + 65 )
        v3 = *(const char **)dword_6F3AE4[*((_DWORD *)dword_6F52CC + 27 * v6 + 20)];
      else
        v3 = (char *)dword_6F52CC + 108 * v6 + 64;
      if ( (char *)dword_6F52CC + 108 * v5 + strlen((const char *)dword_6F52CC + 108 * v5 + 64) + 65 == (char *)dword_6F52CC + 108 * v5 + 65 )
        v4 = *(const char **)dword_6F3AE4[*((_DWORD *)dword_6F52CC + 27 * v5 + 20)];
      else
        v4 = (char *)dword_6F52CC + 108 * v5 + 64;
      if ( v3 )
      {
        if ( v4 )
          result = strcmp(v3, v4);
        else
          result = -1;
      }
      else
      {
        result = v4 != nullptr;
      }
      break;
    default:
      if ( *((__int16 *)dword_6F52CC + 54 * v6 + 47) >= 0 )
      {
        if ( *((__int16 *)dword_6F52CC + 54 * v5 + 47) >= 0 )
        {
          if ( *((__int16 *)dword_6F52CC + 54 * v6 + 47) >= *((__int16 *)dword_6F52CC + 54 * v5 + 47) )
          {
            if ( *((__int16 *)dword_6F52CC + 54 * v6 + 47) <= *((__int16 *)dword_6F52CC + 54 * v5 + 47) )
            {
              if ( *((_DWORD *)dword_6F52CC + 27 * v6 + 21) <= *((_DWORD *)dword_6F52CC + 27 * v5 + 21) )
                result = 1;
              else
                result = -1;
            }
            else
            {
              result = 1;
            }
          }
          else
          {
            result = -1;
          }
        }
        else
        {
          result = -1;
        }
      }
      else if ( *((__int16 *)dword_6F52CC + 54 * v5 + 47) >= 0 )
      {
        result = 1;
      }
      else if ( *((_DWORD *)dword_6F52CC + 27 * v6 + 21) <= *((_DWORD *)dword_6F52CC + 27 * v5 + 21) )
      {
        result = 1;
      }
      else
      {
        result = -1;
      }
      break;
  }
  return result;
}

