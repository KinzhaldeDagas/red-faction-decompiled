// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004683C0 rf_controls_accept_binding_input
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, options/control-binding/preset call chains, original key/selector/geometry/float data, native x87 predicates
// and callback ABI): Cdecl full keyDWORD;does NOT check capture flag itself. key>0:if key>=256,error sound2;else unbounded copy keyNames662020[key] to32-byte stack local,full
// strlen;reject empty and EXACT1,183,69,198,41,184,56 with sound2;otherwise assign(key,-1)468650. EVERY positive-key path ends capture468020,including rejection. key<=0:read relative
// deltas/wheel;scan indices0..4 in ascending order;0..2 use press-count>0,3 wheel>0,4 wheel<0. First event:double-dereference localized mouse label table6F69BC[i],unbounded copy
// into32-byte stack local/full strlen. Empty label ->sound2 and return WITHOUT ending capture/trying later inputs. Nonempty ->assign(-1,i),end capture,return. No event keeps capture
// active. No table-pointer/string/selected-player validation;unbounded label copies precede emptiness admission. Keyboard handler masks raw key low12 before this call;direct positive
// input not normalized here.
int *__cdecl rf_controls_accept_binding_input(int a1)
{
  int *result; // eax
  char v2; // [esp+1Bh] [ebp-89h]
  char *v3; // [esp+20h] [ebp-84h]
  char *v4; // [esp+24h] [ebp-80h]
  char v5; // [esp+3Fh] [ebp-65h]
  char *v6; // [esp+44h] [ebp-60h]
  char *v7; // [esp+48h] [ebp-5Ch]
  char v8; // [esp+4Ch] [ebp-58h] BYREF
  _BYTE v9[3]; // [esp+4Dh] [ebp-57h] BYREF
  char v10[4]; // [esp+6Ch] [ebp-38h] BYREF
  char v11[4]; // [esp+70h] [ebp-34h] BYREF
  int v12; // [esp+74h] [ebp-30h] BYREF
  int v13; // [esp+78h] [ebp-2Ch]
  int i; // [esp+7Ch] [ebp-28h]
  char v15; // [esp+80h] [ebp-24h] BYREF
  _BYTE v16[3]; // [esp+81h] [ebp-23h] BYREF

  if ( a1 <= 0 )
  {
    result = (int *)rf_mouse_get_relative_deltas(v11, v10, &v12);
    for ( i = 0; i < 5; ++i )
    {
      v13 = 0;
      if ( i == 3 )
      {
        v13 = v12 > 0;
      }
      else if ( i == 4 )
      {
        v13 = v12 < 0;
      }
      else
      {
        result = (int *)rf_mouse_get_button_press_count(i);
        v13 = (int)result;
      }
      if ( v13 > 0 )
      {
        v4 = *(char **)dword_6F69BC[i];
        v3 = &v8;
        do
        {
          v2 = *v4;
          *v3++ = *v4++;
        }
        while ( v2 );
        if ( &v9[strlen(&v8)] == v9 )
          return (int *)rf_gamesound_play_event(2, 0, 0.0, 1.0);
        rf_controls_assign_binding_and_remove_duplicates(-1, i);
        return rf_controls_binding_capture_end();
      }
    }
  }
  else
  {
    if ( a1 >= 256 )
    {
      rf_gamesound_play_event(2, 0, 0.0, 1.0);
    }
    else
    {
      v7 = (char *)*(&off_662020 + a1);
      v6 = &v15;
      do
      {
        v5 = *v7;
        *v6++ = *v7++;
      }
      while ( v5 );
      if ( &v16[strlen(&v15)] == v16
        || a1 == 1
        || a1 == 183
        || a1 == 69
        || a1 == 198
        || a1 == 41
        || a1 == 184
        || a1 == 56 )
      {
        rf_gamesound_play_event(2, 0, 0.0, 1.0);
      }
      else
      {
        rf_controls_assign_binding_and_remove_duplicates(a1, -1);
      }
    }
    return rf_controls_binding_capture_end();
  }
  return result;
}

