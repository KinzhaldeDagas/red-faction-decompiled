// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058AE00 rf_input_process_key_state_change
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): CORRECTION to older nonduplicate-press wording: repeats may enqueue. Remaps scan first; exact remapped197 with NumLock-policy==1 forces NumLock keyboard byte0 BEFORE initialized guard. When initialized, locks and backdates engine milliseconds by supplied message lag, truncates scan to low8. Down stores last scan193A0F4 and timestamp193B660. First down sets held/start and increments press count; repeated down is suppressed when repeat flag663F58==0, or for scan1 even when repeats enabled. Scan170 is the suppression sentinel and never enqueues. Event bits: Shift scans42/54=>0x1000, Alt56/184=>0x2000, Ctrl29/157=>0x4000, scan41 held plus flag193B683=>0x0800. Nonzero event enqueues keycode/timestamp only if next write index!=read (16-slot ring, capacity15). Up always
// clears held, increments release count even without prior down, stores last-up193B664, and accumulates now-start if timestamp ordered else clears accumulated time. Up does not enqueue. Unlocks on all initialized paths.
void __cdecl rf_input_process_key_state_change(int a1, int a2, int a3)
{
  int v3; // [esp+0h] [ebp-10h]
  int v4; // [esp+4h] [ebp-Ch]
  unsigned int v5; // [esp+8h] [ebp-8h]
  __int16 v6; // [esp+Ch] [ebp-4h]
  int v7; // [esp+18h] [ebp+8h]

  v7 = rf_input_remap_scan_code(a1);
  if ( v7 == 197 && unk_193B682 == 1 )
    rf_input_set_numlock_keyboard_byte_zero();
  if ( byte_193B680 )
  {
    EnterCriticalSection(&unk_193B668);
    v5 = rf_performance_clock_elapsed_scaled(1000) - a3;
    v4 = (unsigned __int8)v7;
    if ( a2 )
    {
      unk_193A0F4 = (unsigned __int8)v7;
      unk_193B660 = v5;
      if ( byte_193B560[(unsigned __int8)v7] )
      {
        if ( byte_663F58 )
        {
          if ( (unsigned __int8)v7 == 1 )
            v4 = 170;
        }
        else
        {
          v4 = 170;
        }
      }
      else
      {
        dword_193A158[(unsigned __int8)v7] = v5;
        byte_193B560[(unsigned __int8)v7] = 1;
        ++dword_193AD58[(unsigned __int8)v7];
      }
      if ( v4 != 170 )
      {
        v6 = v4;
        if ( byte_193B58A || byte_193B596 )
          v6 = v4 | 0x1000;
        if ( byte_193B598 || byte_193B618 )
          v6 |= 0x2000u;
        if ( byte_193B57D || byte_193B5FD )
          v6 |= 0x4000u;
        if ( byte_193B589 && byte_193B683 )
          v6 |= 0x800u;
        if ( v6 )
        {
          v3 = dword_193B55C + 1;
          if ( (unsigned int)(dword_193B55C + 1) >= 0x10 )
            v3 = 0;
          if ( v3 != unk_193B558 )
          {
            word_193A0F8[dword_193B55C] = v6;
            unk_193A118[dword_193B55C] = unk_193B660;
            dword_193B55C = v3;
          }
        }
      }
    }
    else
    {
      unk_193B664 = (unsigned __int8)v7;
      byte_193B560[(unsigned __int8)v7] = 0;
      ++dword_193B158[(unsigned __int8)v7];
      if ( v5 >= dword_193A158[(unsigned __int8)v7] )
        dword_193A558[(unsigned __int8)v7] += v5 - dword_193A158[(unsigned __int8)v7];
      else
        dword_193A558[(unsigned __int8)v7] = 0;
    }
    LeaveCriticalSection(&unk_193B668);
  }
}

